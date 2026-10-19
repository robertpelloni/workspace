import mido
import logging
import os

logger = logging.getLogger(__name__)

class MidiAnalyzer:
    @staticmethod
    def analyze_file(midi_path):
        """
        Parses a MIDI file and attempts to extract its initial Tempo (BPM) and Time Signature.

        Args:
            midi_path (str): Path to the .mid file.

        Returns:
            dict: { "bpm": int or None, "time_signature": str or None }
        """
        if not os.path.exists(midi_path):
            logger.error(f"MIDI file not found for analysis: {midi_path}")
            return {"bpm": None, "time_signature": None}

        bpm = None
        time_signature = None

        try:
            mid = mido.MidiFile(midi_path)

            # Scan through all tracks and messages looking for tempo and time_signature meta messages
            for track in mid.tracks:
                for msg in track:
                    if msg.type == 'set_tempo' and bpm is None:
                        # Convert tempo (microseconds per beat) to BPM
                        bpm = round(mido.tempo2bpm(msg.tempo))

                    if msg.type == 'time_signature' and time_signature is None:
                        time_signature = f"{msg.numerator}/{msg.denominator}"

                    # Break early if we found both to save processing time
                    if bpm is not None and time_signature is not None:
                        break
                if bpm is not None and time_signature is not None:
                    break

            logger.info(f"Analyzed {os.path.basename(midi_path)}: BPM={bpm}, Time Signature={time_signature}")

        except Exception as e:
            logger.warning(f"Failed to analyze MIDI file {midi_path}: {e}")

        # Return found values, or None if the MIDI file didn't explicitly set them
        return {
            "bpm": bpm,
            "time_signature": time_signature
        }

    @staticmethod
    def extract_all_metadata(midi_path):
        """
        Parses a MIDI file to extract metadata (title, composer) and note-timed lyrics.

        Args:
            midi_path (str): Path to the .mid file.

        Returns:
            dict: Extracted metadata including title, composer, lyrics list, and raw lyrics.
        """
        if not os.path.exists(midi_path):
            return {}

        metadata = {
            "title": None,
            "composer": None,
            "lyrics": [],
            "raw_lyrics_text": ""
        }

        # Determine clean fallback title from filename
        filename = os.path.basename(midi_path)
        name_no_ext = os.path.splitext(filename)[0]
        metadata["title"] = name_no_ext.replace('_', ' ').replace('-', ' ').title()

        try:
            mid = mido.MidiFile(midi_path)
            ticks_per_beat = mid.ticks_per_beat

            # Step 1: Parse first track metadata
            for track in mid.tracks:
                for msg in track:
                    if msg.is_meta:
                        if msg.type == 'text':
                            text = msg.text.strip()
                            if text.lower().startswith("by "):
                                metadata["composer"] = text[3:].strip()
                        elif msg.type == 'track_name':
                            name = msg.name.strip()
                            if name and name.lower() not in ['staff', 'unnamed', 'track', 'melody', 'words']:
                                metadata["title"] = name

            # Enforce fallbacks for generic software/track names
            if metadata["title"] and metadata["title"].lower() in ["staff", "staff-1", "staff-2", "midi", "converted", "track 1", "track 2"]:
                metadata["title"] = name_no_ext.replace('_', ' ').replace('-', ' ').title()

            if metadata["composer"] and metadata["composer"].lower() in ["noteworthy composer", "traditional"]:
                metadata["composer"] = "Traditional"
            else:
                metadata["composer"] = metadata["composer"] or "Traditional"

            # Step 2: Extract timed lyrics
            lyrics_events = []
            for track in mid.tracks:
                current_time_sec = 0.0
                current_tempo = 500000 # Default 120 BPM

                for msg in track:
                    seconds = mido.tick2second(msg.time, ticks_per_beat, current_tempo)
                    current_time_sec += seconds

                    if msg.is_meta:
                        if msg.type == 'set_tempo':
                            current_tempo = msg.tempo
                        elif msg.type == 'lyrics':
                            lyrics_events.append({
                                'text': msg.text,
                                'time': current_time_sec
                            })

            # Sort lyric events by time to handle multi-track files correctly
            lyrics_events.sort(key=lambda x: x['time'])

            # Reconstruct words and phrases
            if lyrics_events:
                phrases = []
                current_phrase_words = []
                phrase_start = None
                last_time = None

                for ev in lyrics_events:
                    txt = ev['text']
                    t = ev['time']

                    # Skip empty/whitespace-only messages at the start/end if they are just placeholders
                    if txt.strip() == "" and not current_phrase_words:
                        continue

                    if phrase_start is None:
                        phrase_start = t

                    is_break = '\r' in txt or '\n' in txt
                    clean_txt = txt.replace('\r', '').replace('\n', '')

                    is_gap = False
                    if last_time is not None and (t - last_time) > 1.5:
                        is_gap = True

                    if is_gap or is_break:
                        if current_phrase_words:
                            phrases.append({
                                'text': "".join(current_phrase_words).strip(),
                                'start': phrase_start,
                                'end': last_time if last_time is not None else t
                            })
                            current_phrase_words = []
                            phrase_start = t

                    if clean_txt:
                        current_phrase_words.append(clean_txt)

                    last_time = t

                if current_phrase_words:
                    phrases.append({
                        'text': "".join(current_phrase_words).strip(),
                        'start': phrase_start,
                        'end': last_time
                    })

                metadata["lyrics"] = phrases
                metadata["raw_lyrics_text"] = " ".join([p['text'] for p in phrases])

            logger.info(f"Extracted MIDI metadata for {filename}: title='{metadata['title']}', composer='{metadata['composer']}', lyrics={len(metadata['lyrics'])} phrases")

        except Exception as e:
            logger.warning(f"Failed to extract lyrics/metadata from MIDI {midi_path}: {e}")

        return metadata

if __name__ == "__main__":
    import sys
    if len(sys.argv) > 1:
        import json
        print(json.dumps(MidiAnalyzer.extract_all_metadata(sys.argv[1]), indent=2))
    else:
        print("Usage: python midi_analyzer.py <file.mid>")
