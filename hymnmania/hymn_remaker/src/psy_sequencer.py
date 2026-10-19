import mido
import math
import random
import time
from mido import Message, MidiFile, MidiTrack, MetaMessage

class InternalMidiPort:
    """
    Wraps the C++ HymnPlayer engine to behave like a mido output port.
    """
    def __init__(self, player):
        self.player = player

    def send(self, msg):
        if msg.type == 'note_on':
            self.player.send_note_on(msg.channel, msg.note, msg.velocity)
        elif msg.type == 'note_off':
            self.player.send_note_off(msg.channel, msg.note)
        elif msg.type == 'control_change':
            self.player.send_cc(msg.channel, msg.control, msg.value)

class PsyGenerator:
    def __init__(self):
        self.ticks_per_beat = 480
        self.ticks_per_sixteenth = self.ticks_per_beat // 4
        self.style_presets = {
            "Full-On": {"euclideanDensity": 8, "gallopVariant": "triplet", "intensity": 1.2, "useMarkovLeads": True},
            "DarkPsy": {"euclideanDensity": 13, "gallopVariant": "rolling", "intensity": 1.5, "useMarkovLeads": True},
            "Progressive": {"euclideanDensity": 4, "gallopVariant": "classic", "intensity": 0.8, "useMarkovLeads": False},
            "Morning": {"euclideanDensity": 6, "gallopVariant": "triplet", "intensity": 1.0, "useMarkovLeads": True}
        }

    def generate(self, input_midi_path, output_midi_path, config):
        """
        Generates a 145 BPM Psytrance pattern or full arrangement based on input MIDI.
        """
        try:
            input_mid = MidiFile(input_midi_path)
        except Exception:
            input_mid = None

        output_mid = MidiFile(ticks_per_beat=self.ticks_per_beat)

        bpm = config.get("targetBpm", 145)
        tempo = mido.bpm2tempo(bpm)

        # Apply style preset if requested
        style_name = config.get("style_preset")
        if style_name and style_name in self.style_presets:
            preset = self.style_presets[style_name]
            # Use preset values if not explicitly overridden in config
            for k, v in preset.items():
                if k not in config:
                    config[k] = v

        # Extract melody and chords from input DNA
        melody_notes, root_notes = self._extract_dna(input_mid)

        mode = config.get("mode", "loop")

        if mode == "arrangement":
            sections = [
                {"name": "Intro", "bars": 8, "kick": True, "bass": True, "lead": False, "intensity": 0.5},
                {"name": "Verse", "bars": 16, "kick": True, "bass": True, "lead": True, "intensity": 0.7},
                {"name": "Build", "bars": 8, "kick": True, "bass": True, "lead": True, "intensity": 0.9, "sweep": True},
                {"name": "Drop", "bars": 16, "kick": True, "bass": True, "lead": True, "intensity": 1.2, "markov": True},
                {"name": "Outro", "bars": 8, "kick": True, "bass": True, "lead": False, "intensity": 0.4}
            ]
        else:
            # Single 8-bar loop
            sections = [{"name": "Loop", "bars": 8, "kick": True, "bass": True, "lead": True, "intensity": 1.0}]

        # Initialize Tracks
        kick_track = MidiTrack()
        kick_track.append(MetaMessage('set_tempo', tempo=tempo))
        kick_track.append(MetaMessage('track_name', name='Kick'))

        bass_track = MidiTrack()
        bass_track.append(MetaMessage('track_name', name='Bass'))

        lead_track = MidiTrack()
        lead_track.append(MetaMessage('track_name', name='Lead'))

        abs_bar = 0
        for sec in sections:
            num_bars = sec["bars"]
            for b in range(num_bars):
                # Calculate section-based intensity modifiers
                current_config = config.copy()
                current_config["euclideanDensity"] = int(config.get("euclideanDensity", 5) * sec.get("intensity", 1.0))
                if sec.get("markov"):
                    current_config["useMarkovLeads"] = True

                # 1. Generate Kick Bar
                if sec["kick"]:
                    self._add_kick_bar(kick_track, current_config)
                else:
                    self._add_silence_bar(kick_track)

                # 2. Generate Bass Bar
                if sec["bass"]:
                    root = self._get_root_for_bar(root_notes, abs_bar)
                    self._add_bass_bar(bass_track, root, current_config, abs_bar)
                else:
                    self._add_silence_bar(bass_track)

                # 3. Generate Lead Bar
                if sec["lead"]:
                    melody = self._get_melody_for_bar(melody_notes, abs_bar)
                    # Handle automation sweep in Build
                    if sec.get("sweep"):
                        # Sweep filter cutoff (CC 74) from 30 to 127 over the section
                        cutoff = int(30 + (b / num_bars) * 97)
                        lead_track.append(Message('control_change', channel=2, control=74, value=cutoff, time=0))

                    self._add_lead_bar(lead_track, melody, current_config)
                else:
                    self._add_silence_bar(lead_track)

                abs_bar += 1

        output_mid.tracks.extend([kick_track, bass_track, lead_track])
        output_mid.save(output_midi_path)
        return True

    def generate_bar_messages(self, bar_idx, config, dna):
        """
        Generates a list of (time_in_bar_ticks, mido.Message) for a single bar.
        dna is a tuple of (melody_notes, root_notes).
        """
        melody_notes, root_notes = dna

        # Temporary tracks to use existing methods
        k_track = MidiTrack()
        b_track = MidiTrack()
        l_track = MidiTrack()

        root = self._get_root_for_bar(root_notes, bar_idx)
        melody = self._get_melody_for_bar(melody_notes, bar_idx)

        self._add_kick_bar(k_track, config)
        self._add_bass_bar(b_track, root, config, bar_idx)
        self._add_lead_bar(l_track, melody, config)

        messages = []
        for track in [k_track, b_track, l_track]:
            abs_tick = 0
            for msg in track:
                abs_tick += msg.time
                if not msg.is_meta:
                    messages.append((abs_tick, msg))

        # Sort by tick
        messages.sort(key=lambda x: x[0])
        return messages

    def stream_to_port(self, port, input_midi_path, config, stop_event=None):
        """
        Streams generated MIDI directly to a mido output port.
        config can be a dict or a callable that returns the current config for live updates.
        """
        try:
            input_mid = MidiFile(input_midi_path)
        except Exception:
            input_mid = None

        dna = self._extract_dna(input_mid)

        bar_idx = 0
        while True:
            if stop_event and stop_event.is_set():
                break

            # Get current config (allows live parameter updates)
            current_config = config() if callable(config) else config

            bpm = current_config.get("targetBpm", 145)
            # 60.0 / (bpm * self.ticks_per_beat)
            tick_duration = 60.0 / (bpm * self.ticks_per_beat)

            # Regenerate messages for every bar to allow live parameter updates
            messages = self.generate_bar_messages(bar_idx, current_config, dna)

            start_time = time.time()
            for tick, msg in messages:
                if stop_event and stop_event.is_set():
                    break

                # Wait until it's time for this message
                current_tick_time = tick * tick_duration
                elapsed = time.time() - start_time
                wait_time = current_tick_time - elapsed
                if wait_time > 0:
                    time.sleep(wait_time)

                port.send(msg)

            bar_idx += 1
            if current_config.get("mode") == "loop" and bar_idx >= 8:
                bar_idx = 0

    def _get_root_for_bar(self, root_notes, bar_idx):
        if not root_notes: return 36
        # Map bar_idx to DNA index (DNA usually 1 note per bar)
        idx = bar_idx % len(root_notes)
        return (root_notes[idx][1] % 12) + 36

    def _get_melody_for_bar(self, melody_notes, bar_idx):
        if not melody_notes: return 60
        idx = bar_idx % len(melody_notes)
        return (melody_notes[idx][1] % 24) + 60

    def _add_silence_bar(self, track):
        track.append(Message('note_on', note=0, velocity=0, time=0))
        track.append(Message('note_off', note=0, velocity=0, time=self.ticks_per_beat * 4))

    def _add_kick_bar(self, track, config):
        vel = int(config.get("kickVelocity", 0.9) * 127)
        for _ in range(4): # 4 beats
            track.append(Message('note_on', note=36, velocity=vel, time=0))
            track.append(Message('note_off', note=36, velocity=0, time=self.ticks_per_sixteenth))
            track.append(Message('note_on', note=0, velocity=0, time=0))
            track.append(Message('note_off', note=0, velocity=0, time=self.ticks_per_sixteenth * 3))

    def _add_bass_bar(self, track, root, config, bar_idx):
        vel = int(config.get("bassVelocity", 0.7) * 127)
        variant = config.get("gallopVariant", "classic")
        octave_freq = config.get("octaveJumpBarFrequency", 2)

        for _ in range(4): # 4 beats
            # Slot 1: Silence (Kick)
            track.append(Message('note_on', note=0, velocity=0, time=0))
            track.append(Message('note_off', note=0, velocity=0, time=self.ticks_per_sixteenth))

            for slot in range(2, 5):
                note = root
                if slot == 4 and octave_freq > 0 and bar_idx % octave_freq == 0:
                    note += 12

                if variant == "triplet" and slot == 2:
                    track.append(Message('note_on', note=0, velocity=0, time=0))
                    track.append(Message('note_off', note=0, velocity=0, time=self.ticks_per_sixteenth))
                else:
                    track.append(Message('note_on', note=note, velocity=vel, time=0))
                    track.append(Message('note_off', note=note, velocity=0, time=self.ticks_per_sixteenth))

    def _add_lead_bar(self, track, anchor_note, config):
        vel = int(config.get("leadVelocity", 0.8) * 127)
        density = config.get("euclideanDensity", 5)
        use_markov = config.get("useMarkovLeads", True)

        pattern = [0] * 16
        if density > 0:
            for i in range(min(density, 16)):
                pattern[(i * 16 // density) % 16] = 1

        # State persistence for Markov could be added but here we just seed it with anchor
        last_note = anchor_note

        for slot in range(16):
            if pattern[slot]:
                note = last_note
                if use_markov:
                    r = random.random()
                    if r < 0.7:
                        note = last_note + random.choice([-1, 0, 1, 2])
                    elif r < 0.9:
                        note = last_note + random.choice([3, 7, 12, -12])
                    else:
                        note = anchor_note
                    note = max(48, min(84, note))
                else:
                    note = anchor_note

                track.append(Message('note_on', note=note, velocity=vel, time=0, channel=2))
                track.append(Message('note_off', note=note, velocity=0, time=self.ticks_per_sixteenth, channel=2))
                last_note = note
            else:
                track.append(Message('note_on', note=0, velocity=0, time=0, channel=2))
                track.append(Message('note_off', note=0, velocity=0, time=self.ticks_per_sixteenth, channel=2))

    def _extract_dna(self, mid):
        melody = [] # list of (start_tick, note, duration_tick)
        roots = []  # list of (start_tick, note)

        if not mid:
            return melody, roots

        all_notes = []
        for track in mid.tracks:
            abs_tick = 0
            active_notes = {}
            for msg in track:
                abs_tick += msg.time
                if msg.type == 'note_on' and msg.velocity > 0:
                    active_notes[msg.note] = abs_tick
                elif (msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity == 0)) and msg.note in active_notes:
                    start = active_notes.pop(msg.note)
                    all_notes.append({'note': msg.note, 'start': start, 'end': abs_tick})

        if not all_notes:
            return melody, roots

        all_notes.sort(key=lambda x: x['start'])

        total_ticks = max(n['end'] for n in all_notes)
        ticks_per_bar = self.ticks_per_beat * 4

        for bar_start in range(0, total_ticks, ticks_per_bar):
            bar_notes = [n for n in all_notes if bar_start <= n['start'] < bar_start + ticks_per_bar]
            if bar_notes:
                highest = max(bar_notes, key=lambda x: x['note'])
                lowest = min(bar_notes, key=lambda x: x['note'])
                melody.append((bar_start, highest['note'], ticks_per_bar))
                roots.append((bar_start, lowest['note']))

        return melody, roots
