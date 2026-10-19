import time
import json
import uuid
import random
import streamlit as st
import os
import sys
import subprocess
import concurrent.futures
import plotly.graph_objects as go
import numpy as np
from dotenv import load_dotenv

# Load .env file from project root
_env_path = os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), '.env')
if os.path.exists(_env_path):
    load_dotenv(_env_path)

from hymn_remaker import settings

# Load global version
VERSION = "1.37.0"
try:
    v_root = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "VERSION")
    if os.path.exists(v_root):
        with open(v_root, "r") as vf:
            VERSION = vf.read().strip()
except Exception:
    pass

st.set_page_config(page_title="Hymn Remaker UI", page_icon="🎵", layout="wide")
st.sidebar.markdown(f"**Version: {VERSION}**")
st.sidebar.markdown("---")

from hymn_remaker.src.midi_renderer import MidiRenderer
from hymn_remaker.src.remaker import MusicRemaker
from hymn_remaker.src.suno_remaker import SunoRemaker
from hymn_remaker.src.udio_remaker import UdioRemaker
from hymn_remaker.src.udio_oauth_remaker import UdioOAuthRemaker
from hymn_remaker.src.gemini_generator import GeminiContentGenerator
from hymn_remaker.src.video_uploader import VideoProducer
from hymn_remaker.src.tts_generator import TTSGenerator
from hymn_remaker.src.musicxml_parser import MusicXMLParser
from hymn_remaker.src.omr_processor import OMRProcessor
from hymn_remaker.src.stem_separator import StemSeparator
from hymn_remaker.src.local_remaker import LocalMusicRemaker
from hymn_remaker.src.quality_evaluator import QualityEvaluator
from hymn_remaker.src.psy_mono_bridge import PsyMonoBridge
from hymn_remaker.main import process_single_midi

st.title("🎵 Hymn Remaker Pipeline")
with st.expander("👋 Welcome Tester! (v1.37.0 Highlights)", expanded=True):
    st.markdown("""
    This version introduces the **Studio Reversal** suite:
    1. **Suno Experiment Matrix**: Generate 9 variations (3 speeds x 3 genres) for every hymn in one click using sidebar toggles.
    2. **Reverse Engineering**: Go to the **Library** tab and click **Reverse to Ableton** on any AI track to split it into stems, convert to MIDI, and push to your DAW.
    3. **Speed Controls**: Manually adjust Sonic Vacuum speed (0.5x, 1x, 2x) for custom dry renders.

    **Getting Started:** Upload a MIDI in Tab 1, or explore generated tracks in Tab 4.
    """)
    if st.button("🚀 Run Batch Demo (Mock Data)"):
        st.info("Simulating batch generation for library populating...")
        os.makedirs(output_dir, exist_ok=True)
        import scipy.io.wavfile as wavfile
        import numpy as np
        # Create a tiny 1-second silent valid wav file
        silent_audio = np.zeros(44100, dtype=np.int16)
        for demo in ["Emmanuel", "Amazing Grace", "Holy Holy Holy"]:
            wav_path = os.path.join(output_dir, f"{demo}_remake.wav")
            wavfile.write(wav_path, 44100, silent_audio)
            with open(os.path.join(output_dir, f"{demo}_metadata.json"), "w") as f: json.dump({"title": demo}, f)
        st.success("Demo items created! Check the Library.")
st.write("Convert MIDI files into modern music videos with AI!")

# Initialize objects
@st.cache_resource
def load_modules():
    try:
        renderer = MidiRenderer()
        remaker = MusicRemaker()
        suno_remaker = SunoRemaker()
        udio_remaker = UdioRemaker()
        content_gen = GeminiContentGenerator()
        video_producer = VideoProducer()
        tts_generator = TTSGenerator()
        mxl_parser = MusicXMLParser()
        omr_processor = OMRProcessor()
        stem_separator = StemSeparator()
        udio_oauth_remaker = UdioOAuthRemaker()
        local_remaker = LocalMusicRemaker()
        quality_eval = QualityEvaluator()
        psy_mono_bridge = PsyMonoBridge()
        return renderer, remaker, suno_remaker, udio_remaker, content_gen, video_producer, tts_generator, mxl_parser, omr_processor, stem_separator, udio_oauth_remaker, local_remaker, quality_eval, psy_mono_bridge
    except Exception as e:
        import traceback
        st.error(f"Failed to initialize modules: {e}")
        st.code(traceback.format_exc())
        return [None] * 14

modules = load_modules()
renderer, remaker, suno_remaker, udio_remaker, content_gen, video_producer, tts_generator, mxl_parser, omr_processor, stem_separator, udio_oauth_remaker, local_remaker, quality_eval, psy_mono_bridge = modules

st.sidebar.header("Environment & API")
missing_keys = []
if not os.environ.get("GEMINI_API_KEY") and not os.path.exists("client_secrets.json"):
    missing_keys.append("GEMINI_API_KEY / client_secrets.json")
if not os.environ.get("REPLICATE_API_TOKEN"):
    missing_keys.append("REPLICATE_API_TOKEN")
if missing_keys:
    st.sidebar.error(f"Missing Essential API Keys: {', '.join(missing_keys)}")
else:
    st.sidebar.success("Essential API Keys configured! ✅")

st.sidebar.header("Settings")
preset_styles = [
    settings.DEFAULT_STYLE,
    "Full-On Psytrance, 145 BPM, driving, psychedelic",
    "Sonic Vacuum: Dry staccato sine render",
    "Symbolic Norm: Velocity-flattened grid",
    "House Quantizer: 124 BPM 4/4 structural snap",
    "Lofi hip hop, chill, relaxing",
    "Synthwave, retro 80s",
    "Epic Orchestral",
    "Custom..."
]
selected_style = st.sidebar.selectbox("Musical Style Preset", preset_styles)
style = selected_style if selected_style != "Custom..." else st.sidebar.text_input("Custom Style", value="Your custom prompt here")

output_dir = st.sidebar.text_input("Output Directory", value=settings.OUTPUT_DIR)
max_workers = st.sidebar.slider("Concurrent Tasks", min_value=1, max_value=4, value=1)

st.sidebar.markdown("### Experimental Preprocessors")
with st.sidebar.expander("Udio/Suno Optimizers", expanded=False):
    speed = st.selectbox("Sonic Vacuum Speed", [0.5, 1.0, 2.0], index=1, help="Adjust playback speed for dry render.")
    sonic_vacuum = st.checkbox("Sonic Vacuum (Dry Render)", value=False, help="Render transient-only audio to prevent soundfont bleed.")
    symbolic_norm = st.checkbox("Symbolic Norm (Velocity 100)", value=False, help="Strip performance baggage and flatten velocity.")
    house_quantizer = st.checkbox("House Structural Quantizer", value=False, help="Force snap to 124 BPM electronic grid.")
    mix_hiphop_vocals = st.text_input("Hip-Hop Vocal Remix (Path/URL)", help="Provide a local path or YouTube URL to an acapella or hip-hop track to remix into the psytrance track.")
    suno_matrix = st.checkbox("Suno 9-Way Matrix (v1.37.0)", value=False, help="Execute 3 speeds x 3 genres matrix generation.")

st.sidebar.markdown("### Pipeline Options")
video_format = st.sidebar.selectbox("Video Format", ["Standard 16:9", "Vertical 9:16"])
enable_visualizer = st.sidebar.checkbox("Audio-Reactive Visualizer", value=False)
visualizer_mode = "cline"
if enable_visualizer:
    visualizer_mode = st.sidebar.selectbox("Visualizer Mode", ["kaleidoscope", "cline", "line", "p2p", "avectorscope"], index=0)
generate_vocals = st.sidebar.checkbox("Generate Vocals (ElevenLabs)", value=False)
remake_priority = st.sidebar.selectbox("AI Remake Service", ["suno", "udio-oauth", "udio", "replicate", "local"], index=0)
udio_variance = st.sidebar.slider("Udio Remix Variance", 0.1, 1.0, 0.25)
local_guidance = st.sidebar.slider("Local Guidance Scale", 1.0, 10.0, 3.0)
local_temperature = st.sidebar.slider("Local Temperature", 0.1, 2.0, 1.0)

upload = st.sidebar.checkbox("Upload to YouTube", value=False)

skip_render = st.sidebar.checkbox("Skip Render if exists", value=False, help="If the intermediate base WAV file already exists, don't re-render it from MIDI.")
skip_remake = st.sidebar.checkbox("Skip Remake if exists", value=False, help="If the remade audio already exists, don't call the MusicGen API again.")

interactive_mode = st.sidebar.checkbox("Interactive Review Mode", value=False, help="Pause the pipeline after metadata/lyrics generation to manually edit the lyrics, title, and art prompt before rendering the final audio and video.")

st.sidebar.markdown("---")
if st.sidebar.button("🗑️ Clear Workspace", help="Delete all files in the input and output directories."):
    import shutil
    try:
        if os.path.exists(settings.INPUT_DIR):
            shutil.rmtree(settings.INPUT_DIR)
            os.makedirs(settings.INPUT_DIR)
        if os.path.exists(output_dir):
            shutil.rmtree(output_dir)
            os.makedirs(output_dir)
        st.sidebar.success("Workspace cleared successfully.")
    except Exception as e:
        st.sidebar.error(f"Failed to clear workspace: {e}")

tab1, tab2, tab3, tab4, tab5 = st.tabs(["🚀 Automated Pipeline", "🎹 Hymn Editor (Beta)", "🌀 Live Psy-Mono Studio", "📚 Library", "🔬 Optimization & Analytics"])

with tab1:
    uploaded_files = st.file_uploader("Upload MIDI/MusicXML", type=["mid", "midi", "mxl", "xml"], accept_multiple_files=True)
    if st.button("🔍 Preview Preprocessing (Local Render)"):
        if not uploaded_files:
            st.warning("Please upload a MIDI file first.")
        else:
            with st.status("Generating Preview...") as status:
                for uf in uploaded_files:
                    temp_in = os.path.join(settings.INPUT_DIR, f"preview_{uf.name}")
                    with open(temp_in, "wb") as f: f.write(uf.getbuffer())

                    temp_mid = temp_in
                    if symbolic_norm:
                         from pipeline.processing.symbolic_norm import SymbolicNormalizer
                         norm_out = temp_in.replace(".mid", "_norm.mid")
                         SymbolicNormalizer(temp_in).normalize(norm_out)
                         temp_mid = norm_out
                    if house_quantizer:
                         from pipeline.processing.house_quantizer import HouseStructuralQuantizer
                         quant_out = temp_mid.replace(".mid", "_quant.mid")
                         HouseStructuralQuantizer(temp_mid).quantize(quant_out)
                         temp_mid = quant_out

                    out_wav = os.path.join(settings.OUTPUT_DIR, "preprocessing_preview.wav")
                    if sonic_vacuum:
                        from pipeline.processing.sonic_vacuum import SonicVacuumProcessor
                        vacuum = SonicVacuumProcessor(temp_mid)
                        audio_arr, sr = vacuum.render_dry_piano(None, return_audio=True)
                        if speed == 0.5:
                            indices = np.arange(0, len(audio_arr), 0.5)
                            indices = np.clip(indices, 0, len(audio_arr) - 1).astype(np.int64)
                            audio_arr = audio_arr[indices]
                        elif speed == 2.0:
                            audio_arr = audio_arr[::2]
                        import scipy.io.wavfile as wavfile
                        wavfile.write(out_wav, sr, (audio_arr * 32767).astype(np.int16))
                    else:
                        renderer.render(temp_mid, out_wav)

                    st.write(f"Preview for **{uf.name}**")
                    st.audio(out_wav)
                status.update(label="Preview Ready!", state="complete")
    if st.button("Start Processing", type="primary"):
        st.session_state["is_processing"] = True
        st.session_state["uploaded_files_data"] = []
        if uploaded_files:
            for uf in uploaded_files:
                st.session_state["uploaded_files_data"].append({
                    "name": uf.name, "data": uf.getbuffer().tobytes()
                })

    if st.session_state.get("is_processing", False):
        if not st.session_state.get("uploaded_files_data"):
            st.warning("Please upload files.")
            st.session_state["is_processing"] = False
        else:
            os.makedirs(settings.INPUT_DIR, exist_ok=True)
            os.makedirs(output_dir, exist_ok=True)

            saved_files = []
            for uf_data in st.session_state["uploaded_files_data"]:
                file_path = os.path.join(settings.INPUT_DIR, uf_data["name"])
                with open(file_path, "wb") as f:
                    f.write(uf_data["data"])
                saved_files.append(file_path)

            for file_path in saved_files:
                filename = os.path.basename(file_path)
                with st.status(f"Processing {filename}...") as status:
                    progress_bar = st.progress(0, text="Initializing...")
                    def streamlit_status(msg, progress):
                        status.write(msg)
                        progress_bar.progress(progress, text=msg)

                    try:
                        process_single_midi(
                            midi_path=file_path,
                            status_callback=streamlit_status,
                            output_dir=output_dir,
                            style=style,
                            skip_render=skip_render,
                            skip_remake=skip_remake,
                            upload=upload,
                            renderer=renderer,
                            remaker=remaker,
                            suno_remaker=suno_remaker,
                            udio_remaker=udio_remaker,
                            remake_priority=remake_priority,
                            udio_oauth_remaker=udio_oauth_remaker,
                            local_remaker=local_remaker,
                            content_gen=content_gen,
                            video_producer=video_producer,
                            mxl_parser=mxl_parser,
                            omr_processor=omr_processor,
                            tts_generator=tts_generator,
                            stem_separator=stem_separator,
                            generate_vocals=generate_vocals,
                            video_format=video_format,
                            enable_visualizer=enable_visualizer,
                            udio_variance=udio_variance,
                            local_guidance=local_guidance,
                            local_temperature=local_temperature,
                            speed=speed,
                            sonic_vacuum=sonic_vacuum,
                            symbolic_norm=symbolic_norm,
                            house_quantizer=house_quantizer,
                            hiphop_vocal_path=mix_hiphop_vocals if mix_hiphop_vocals else None,
                            suno_matrix=suno_matrix,
                            quality_evaluator=quality_eval
                        )
                        status.update(label=f"Finished {filename}!", state="complete")
                    except Exception as e:
                        st.error(f"Error processing {filename}: {e}")
            st.balloons()
            st.session_state["is_processing"] = False

with tab2:
    st.header("Hymn Editor Toolbar")
    editor_file = st.file_uploader("Load MIDI/MusicXML", type=["mid", "midi", "mxl", "xml"], key="editor_up")
    if editor_file:
        file_path = os.path.join(settings.INPUT_DIR, f"edit_{editor_file.name}")
        with open(file_path, "wb") as f:
            f.write(editor_file.getbuffer())

        if st.button("Render Preview 🔊"):
            out_audio = os.path.join(settings.OUTPUT_DIR, "edit_preview.wav")
            renderer.render(file_path, out_audio)
            st.audio(out_audio)

with tab3:
    st.header("🌀 Live Psy-Mono Studio V5: Live Jam Edition")
    from streamlit_mic_recorder import mic_recorder
    from hymn_remaker.src.audio_to_midi import transcribe_audio_to_midi
    from hymn_remaker.src.psy_sequencer import PsyGenerator, InternalMidiPort
    from hymn_remaker.src.audio_streamer import AudioStreamer
    import mido
    import threading

    if "psy_player" not in st.session_state:
        try:
            import hymn_player_ext
            st.session_state.psy_player = hymn_player_ext.HymnPlayer(settings.DEFAULT_SOUNDFONT_PATHS[0])
            st.session_state.psy_gen = PsyGenerator()
            st.session_state.internal_midi_port = InternalMidiPort(st.session_state.psy_player)
            st.session_state.audio_streamer = AudioStreamer(st.session_state.psy_player)
        except ImportError:
            st.session_state.psy_player = None
            st.session_state.psy_gen = None
            st.session_state.internal_midi_port = None
            st.session_state.audio_streamer = None

    if "event_log" not in st.session_state:
        st.session_state.event_log = []

    perf_mode = st.toggle("🚀 PERFORMANCE MODE", value=False, help="Hides non-essential sliders for a cleaner live jamming interface.")

    col1, col2 = st.columns([1, 2])
    with col1:
        if not perf_mode:
            st.subheader("1. Input & Mode")
        source_mode = st.radio("Input Source", ["Hymn MIDI", "Mic Input"], key="psy_source")
        gen_mode = st.radio("Generation Mode", ["Loop (8 bars)", "Arrangement (56 bars)"], key="psy_mode")

        if perf_mode:
             st.info(f"Mode: {gen_mode} | Gain: {st.session_state.get('psy_gain', 1.0)}")

        input_midi_path = None
        if source_mode == "Hymn MIDI":
            live_midi = st.file_uploader("Upload MIDI", type=["mid", "midi"], key="live_up")
            if live_midi:
                input_midi_path = os.path.join(settings.INPUT_DIR, "live_input.mid")
                with open(input_midi_path, "wb") as f:
                    f.write(live_midi.getbuffer())
        else:
            audio_rec = mic_recorder(start_prompt="⏺️ Record", stop_prompt="⏹️ Stop", key="mic_psy")
            if audio_rec:
                temp_audio = os.path.join(settings.INPUT_DIR, "live_mic.wav")
                input_midi_path = os.path.join(settings.INPUT_DIR, "live_mic.mid")
                with open(temp_audio, "wb") as f:
                    f.write(audio_rec['bytes'])
                transcribe_audio_to_midi(temp_audio, input_midi_path)

        if not perf_mode:
            st.subheader("2. Sequencer Config")
            bpm = st.slider("Target BPM", 120, 160, 145, key="psy_bpm")
            algo_style = st.selectbox("Algorithmic Style", ["None", "Full-On", "DarkPsy", "Progressive", "Morning"], key="psy_algo_style")
            density = st.slider("Euclidean Density", 1, 16, 5, key="psy_density")
            gallop = st.selectbox("Gallop Variant", ["classic", "triplet", "rolling"], key="psy_gallop")
            st.write("**Preprocessors**")
            live_sym_norm = st.checkbox("Symbolic Norm", key="psy_live_sym_norm")
            live_house_quant = st.checkbox("House Quantizer", key="psy_live_house_quant")
        else:
            bpm = st.session_state.get("psy_bpm", 145)
            algo_style = st.session_state.get("psy_algo_style", "None")
            density = st.session_state.get("psy_density", 5)
            gallop = st.session_state.get("psy_gallop", "classic")

        st.subheader("3. Live Performance Mixer")
        master_gain = st.slider("Global Gain", 0.0, 5.0, 1.0, key="psy_gain")
        if st.session_state.psy_player:
            st.session_state.psy_player.set_gain(master_gain)

        vol_k = st.slider("Kick (Ch 0)", 0.0, 1.0, 0.9, key="psy_vol_k")
        vol_b = st.slider("Bass (Ch 1)", 0.0, 1.0, 0.7, key="psy_vol_b")
        vol_l = st.slider("Lead (Ch 2)", 0.0, 1.0, 0.8, key="psy_vol_l")

        if st.session_state.psy_player:
            st.session_state.psy_player.set_channel_volume(0, vol_k)
            st.session_state.psy_player.set_channel_volume(1, vol_b)
            st.session_state.psy_player.set_channel_volume(2, vol_l)

        st.subheader("External MIDI Control")
        try:
            in_ports = mido.get_input_names()
            out_ports = mido.get_output_names()
        except Exception:
            in_ports = []
            out_ports = []

        midi_in_sel = st.selectbox("MIDI Input (Hardware/Controller)", ["None"] + in_ports)
        midi_out_sel = st.selectbox("MIDI Output (External VST/Synth)", ["None"] + out_ports)

        # Real-Time Jam Mode Feature: Full MIDI Passthrough and Jam Integration
        jam_mode = st.toggle("🎸 Real-Time Jam Mode", value=False, help="Route live MIDI input directly to the synth engine and sequencer.")

        if jam_mode and midi_in_sel != "None":
            st.info("Jam Mode Active: Play your MIDI controller to hear the synth engine in real-time.")
            if st.session_state.get("last_midi_in") != midi_in_sel:
                # Setup input callback for jam mode
                def jam_callback(message):
                    if st.session_state.psy_player:
                        if message.type == 'note_on':
                            st.session_state.psy_player.note_on(2, message.note, message.velocity)
                        elif message.type == 'note_off':
                            st.session_state.psy_player.note_off(2, message.note)
                        elif message.type == 'control_change':
                            # Map CC 1 (Mod wheel) to Energy
                            if message.control == 1:
                                 st.session_state.psy_energy_val = message.value / 127.0
                            # Map CC 74 (Brightness) to Cutoff
                            elif message.control == 74:
                                 st.session_state.psy_player.send_cc(2, 74, message.value)
                            # Passthrough other CCs to lead synth
                            else:
                                 st.session_state.psy_player.send_cc(2, message.control, message.value)
                        elif message.type == 'pitchwheel':
                            st.session_state.psy_player.send_pitch_bend(2, message.pitch)

                try:
                    if "midi_in_port" in st.session_state and hasattr(st.session_state.midi_in_port, 'close'):
                        st.session_state.midi_in_port.close()
                    st.session_state.midi_in_port = mido.open_input(midi_in_sel, callback=jam_callback)
                    st.session_state.last_midi_in = midi_in_sel
                    st.success(f"Connected to {midi_in_sel} for Jamming")
                except Exception as e:
                    st.error(f"MIDI In Error: {e}")
        elif not jam_mode and midi_in_sel != "None" and st.session_state.get("last_midi_in") != midi_in_sel:
            # Setup input callback (Standard Controller Mapping)
            def midi_callback(message):
                if message.type == 'control_change':
                    # Map CC 1 (Mod wheel) to Energy
                    if message.control == 1:
                         # This won't update UI directly but can affect engine state
                         st.session_state.psy_energy_val = message.value / 127.0
                    # Map CC 74 (Brightness) to Cutoff
                    elif message.control == 74:
                         st.session_state.psy_player.send_cc(2, 74, message.value)

            try:
                if "midi_in_port" in st.session_state and hasattr(st.session_state.midi_in_port, 'close'):
                    st.session_state.midi_in_port.close()
                st.session_state.midi_in_port = mido.open_input(midi_in_sel, callback=midi_callback)
                st.session_state.last_midi_in = midi_in_sel
                st.success(f"Connected to {midi_in_sel}")
            except Exception as e:
                st.error(f"MIDI In Error: {e}")

        st.subheader("4. Real-time Automation")
        cutoff = st.slider("Filter Cutoff (CC 74)", 0, 127, 100)
        if st.session_state.psy_player:
            st.session_state.psy_player.send_cc(2, 74, cutoff) # Lead channel filter
        if cutoff != st.session_state.get('prev_cutoff'):
            st.session_state.event_log.append(f"[{time.strftime('%H:%M:%S')}] CC 74 (Cutoff): {cutoff}")
            st.session_state.prev_cutoff = cutoff

        res = st.slider("Resonance (CC 71)", 0, 127, 40)
        if st.session_state.psy_player:
            st.session_state.psy_player.send_cc(2, 71, res)
        if res != st.session_state.get('prev_res'):
            st.session_state.event_log.append(f"[{time.strftime('%H:%M:%S')}] CC 71 (Resonance): {res}")
            st.session_state.prev_res = res

        st.subheader("Psy-Energy Macro")
        psy_energy = st.slider("Global Energy", 0.0, 1.0, 0.5, help="Macro: Affects filter, resonance, and playback intensity.")
        # Map macro to actual params
        cutoff_macro = int(20 + (psy_energy * 100))
        res_macro = int(10 + (psy_energy * 90))
        if st.session_state.psy_player:
            st.session_state.psy_player.send_cc(2, 74, cutoff_macro)
            st.session_state.psy_player.send_cc(2, 71, res_macro)
            # Dynamically adjust gain based on energy
            st.session_state.psy_player.set_gain(master_gain * (0.8 + psy_energy * 0.4))

        st.subheader("Live Audio Stream")
        use_web_stream = st.toggle("🌐 Enable Web Stream (Browser Audio)", value=False)
        if use_web_stream:
            if st.session_state.audio_streamer:
                st.session_state.audio_streamer.start()
                st.markdown('<audio src="http://localhost:8000/stream.mp3" controls autoplay style="width: 100%;"></audio>', unsafe_allow_html=True)
                st.info("Streaming live MP3 to browser. Use System Audio if running locally.")
            else:
                st.error("Audio Streamer not available.")
        else:
            if st.session_state.audio_streamer:
                st.session_state.audio_streamer.stop()

    with col2:
        st.subheader("Performance Monitor & Event Log")
        metrics_cols = st.columns(3)
        metrics_cols[0].metric("BPM", f"{bpm}")
        metrics_cols[1].metric("Density", f"{density}")
        metrics_cols[2].metric("Preprocessors", f"{int(st.session_state.get('psy_live_sym_norm', False)) + int(st.session_state.get('psy_live_house_quant', False))}")

        log_container = st.container(height=150)
        with log_container:
            for event in reversed(st.session_state.event_log[-20:]):
                st.write(f"`{event}`")

        preview_placeholder = st.empty()

        st.subheader("Live Waveform Visualizer")
        # Pull real peaks from streamer
        if st.session_state.audio_streamer:
            peaks = st.session_state.audio_streamer.get_peaks()
        else:
            peaks = [0, 0]
        if "viz_buffer" not in st.session_state:
            st.session_state.viz_buffer = np.zeros(200)

        new_val = (peaks[0] + peaks[1]) / 2.0
        st.session_state.viz_buffer = np.roll(st.session_state.viz_buffer, -1)
        st.session_state.viz_buffer[-1] = new_val
        viz_data = st.session_state.viz_buffer

        fig_viz = go.Figure(go.Scattergl(y=viz_data, mode='lines', line=dict(color='cyan', width=2), fill='tozeroy', fillcolor='rgba(0, 255, 255, 0.2)'))
        fig_viz.update_layout(height=150, margin=dict(l=0,r=0,t=0,b=0), xaxis_visible=False, yaxis_visible=False, template="plotly_dark")
        st.plotly_chart(fig_viz, use_container_width=True)

        if gen_mode == "Arrangement (56 bars)":
            st.info("Arrangement Map: Intro -> Verse -> Build -> Drop -> Outro")
            # Draw a simple progress bar based on hypothetical playback (Streamlit doesn't track C++ playback time easily)
            # but we can show the static arrangement visual.
            fig_arr = go.Figure()
            fig_arr.add_trace(go.Bar(x=["Intro", "Verse", "Build", "Drop", "Outro"], y=[8, 16, 8, 16, 8], marker_color='indigo'))
            fig_arr.update_layout(title="Arrangement Timeline (Bars)", height=250)
            st.plotly_chart(fig_arr, use_container_width=True)

        c1, c2, c3 = st.columns(3)
        if c1.button("▶️ GENERATE & PLAY"):
            st.session_state.event_log.append(f"[{time.strftime('%H:%M:%S')}] Trigger: Generate & Play ({algo_style})")
            if input_midi_path:
                # Apply live preprocessors if selected
                live_proc_path = input_midi_path
                if st.session_state.get("psy_live_sym_norm"):
                    from pipeline.processing.symbolic_norm import SymbolicNormalizer
                    norm_out = os.path.join(settings.OUTPUT_DIR, "live_norm.mid")
                    SymbolicNormalizer(live_proc_path).normalize(norm_out)
                    live_proc_path = norm_out
                if st.session_state.get("psy_live_house_quant"):
                    from pipeline.processing.house_quantizer import HouseStructuralQuantizer
                    quant_out = os.path.join(settings.OUTPUT_DIR, "live_quant.mid")
                    HouseStructuralQuantizer(live_proc_path).quantize(quant_out)
                    live_proc_path = quant_out

                temp_output = os.path.join(output_dir, "studio_output.mid")
                mode_str = "arrangement" if gen_mode == "Arrangement (56 bars)" else "loop"

                # Define a live config getter
                def get_live_config():
                    c = {
                        "targetBpm": st.session_state.get("psy_bpm", 145),
                        "euclideanDensity": st.session_state.get("psy_density", 5),
                        "gallopVariant": st.session_state.get("psy_gallop", "classic"),
                        "mode": "arrangement" if st.session_state.get("psy_mode") == "Arrangement (56 bars)" else "loop",
                        "kickVelocity": st.session_state.get("psy_vol_k", 0.9),
                        "bassVelocity": st.session_state.get("psy_vol_b", 0.7),
                        "leadVelocity": st.session_state.get("psy_vol_l", 0.8)
                    }
                    astyle = st.session_state.get("psy_algo_style", "None")
                    if astyle != "None":
                        c["style_preset"] = astyle
                    return c

                # Clear previous threads
                if "midi_stop_event" in st.session_state:
                    st.session_state.midi_stop_event.set()
                if "midi_out_thread" in st.session_state and st.session_state.midi_out_thread.is_alive():
                    st.session_state.midi_out_thread.join()
                if "internal_midi_thread" in st.session_state and st.session_state.internal_midi_thread.is_alive():
                    st.session_state.internal_midi_thread.join()

                st.session_state.midi_stop_event = threading.Event()

                # Start Internal Streaming
                st.session_state.psy_player.start_realtime()
                st.session_state.internal_midi_thread = threading.Thread(
                    target=st.session_state.psy_gen.stream_to_port,
                    args=(st.session_state.internal_midi_port, live_proc_path, get_live_config, st.session_state.midi_stop_event)
                )
                st.session_state.internal_midi_thread.start()

                # Optional: Stream to external MIDI port
                if midi_out_sel != "None":
                    try:
                        out_port = mido.open_output(midi_out_sel)
                        st.session_state.midi_out_thread = threading.Thread(
                            target=st.session_state.psy_gen.stream_to_port,
                            args=(out_port, live_proc_path, get_live_config, st.session_state.midi_stop_event)
                        )
                        st.session_state.midi_out_thread.start()
                        st.info(f"Streaming to external MIDI port: {midi_out_sel}")
                    except Exception as e:
                        st.error(f"External MIDI Out Error: {e}")

                st.success(f"Live performance started in {mode_str} mode!")

                # Still generate the MIDI file for visual preview / download
                st.session_state.psy_gen.generate(live_proc_path, temp_output, get_live_config())
                mid = mido.MidiFile(temp_output)
                notes = []
                for track in mid.tracks:
                    time = 0
                    for msg in track:
                        time += msg.time
                        if msg.type == 'note_on' and msg.velocity > 0:
                            notes.append({'t': time, 'n': msg.note, 'track': track.name})
                if notes:
                    fig = go.Figure()
                    for t_name in ['Kick', 'Bass', 'Lead']:
                        # Show first 4 bars in preview
                        t_notes = [n for n in notes if n['track'] == t_name and n['t'] < 1920 * 4]
                        fig.add_trace(go.Scattergl(x=[n['t'] for n in t_notes], y=[n['n'] for n in t_notes], mode='markers', name=t_name))
                    fig.update_layout(height=350, margin=dict(l=0,r=0,t=0,b=0), title="Preview (First 4 Bars)")
                    preview_placeholder.plotly_chart(fig, use_container_width=True)

                st.session_state.psy_player.stop_realtime()
                st.session_state.psy_player.load(temp_output)
                st.session_state.psy_player.start_realtime()
                st.session_state.psy_player.play()
                st.success(f"Playing {mode_str} live!")

        if c2.button("⏹️ STOP"):
            st.session_state.psy_player.stop()
            st.session_state.psy_player.stop_realtime()
            if "midi_stop_event" in st.session_state:
                st.session_state.midi_stop_event.set()
            st.info("Performance stopped.")

        st.subheader("Manual FX & Jam Trigger")
        fc1, fc2, fc3 = st.columns(3)
        if fc1.button("💥 Crash Cymbal"):
             st.session_state.psy_player.send_note_on(9, 49, 120) # MIDI Ch 10 is usually percussion
             st.session_state.event_log.append(f"[{time.strftime('%H:%M:%S')}] Manual FX: Crash Cymbal")
        if fc2.button("🚀 Rising Sweep"):
            st.session_state.psy_player.send_note_on(3, 72, 100)
            st.session_state.event_log.append(f"[{time.strftime('%H:%M:%S')}] Manual FX: Rising Sweep")
        if fc3.button("🥁 Acid Fill"):
            st.session_state.event_log.append(f"[{time.strftime('%H:%M:%S')}] Manual FX: Acid Fill")
            # Trigger a rapid acid lead sequence on channel 2
            for i in range(4):
                st.session_state.psy_player.send_note_on(2, 60 + i*2, 110)
                time.sleep(0.05)
                st.session_state.psy_player.send_note_off(2, 60 + i*2)
            st.toast("Acid Fill triggered!")

        if st.button("🚨 PANIC (Stop All)", type="secondary"):
            if "midi_stop_event" in st.session_state:
                st.session_state.midi_stop_event.set()
            for ch in range(16):
                st.session_state.psy_player.send_cc(ch, 123, 0) # All Notes Off
            st.session_state.event_log.append(f"[{time.strftime('%H:%M:%S')}] Panic triggered.")

        st.subheader("5. Export & Render")
        er1, er2 = st.columns(2)
        if er1.button("🎬 Render Studio Jam to Video", help="Renders the current generated MIDI with audio-reactive visuals."):
            temp_mid = os.path.join(output_dir, "studio_output.mid")
            if os.path.exists(temp_mid):
                with st.spinner("Rendering audio and video..."):
                    out_audio = os.path.join(output_dir, f"studio_render_{uuid.uuid4().hex[:4]}.wav")
                    out_video = out_audio.replace(".wav", ".mp4")

                    # Render Audio
                    renderer.render(temp_mid, out_audio)

                    # Render Video with Visualizer
                    # Use a placeholder image or a solid color
                    video_producer.create_video(
                        out_audio, "black", out_video,
                        enable_visualizer=True,
                        visualizer_mode=visualizer_mode,
                        tempo_bpm=bpm
                    )
                    st.video(out_video)
                    st.success(f"Render complete: {out_video}")
                    st.balloons()
            else:
                st.error("No generated MIDI found. Press 'GENERATE & PLAY' first.")

        if er2.button("💾 Download Generated MIDI"):
            temp_mid = os.path.join(output_dir, "studio_output.mid")
            if os.path.exists(temp_mid):
                with open(temp_mid, "rb") as f:
                    st.download_button("Click to Download MIDI", f, file_name="psy_jam.mid")
            else:
                st.error("No generated MIDI found.")

    with st.expander("Model Refinement & Feedback"):
        feedback_rating = st.slider("Rate this Track (Stars)", 1, 5, 5, key="studio_stars")
        feedback_text = st.text_area("What could be improved?", key="studio_feedback_text")
        if st.button("Submit Feedback"):
            st.success("Thank you for your feedback! It will be used to refine our algorithmic rules.")
            # In a real app, we would write this to a DB
            with open("output/feedback_log.jsonl", "a") as f:
                f.write(json.dumps({
                    "timestamp": time.time(),
                    "rating": feedback_rating,
                    "text": feedback_text,
                    "config": {
                        "bpm": bpm, "density": density, "gallop": gallop, "algo_style": algo_style
                    }
                }) + "\n")

    with st.expander("Novel AI Generation (Local MusicGen)"):
        novel_prompt = st.text_input("Novel Prompt", value="Fast melodic psytrance, 145 BPM, psychedelic leads, high energy")
        novel_duration = st.slider("Duration (sec)", 5, 30, 10)
        if st.button("✨ Generate Novel Track"):
            with st.spinner("Generating novel track..."):
                out_path = os.path.join(output_dir, f"novel_{uuid.uuid4().hex[:8]}.wav")
                local_remaker.generate(novel_prompt, duration=novel_duration, output_path=out_path)
                st.audio(out_path)
                st.success(f"Novel track generated: {out_path}")

with tab4:
    st.header("📚 Output Library")

    demo_dir = os.path.join(output_dir, "demos")
    if os.path.exists(demo_dir):
        with st.expander("🌟 Official v1.37.0 Demos", expanded=True):
            demo_files = [f for f in os.listdir(demo_dir) if f.endswith(('.wav', '.mp3'))]
            for f in sorted(demo_files):
                f_path = os.path.join(demo_dir, f)
                c1, c2, c3 = st.columns([3, 1, 1])
                c1.write(f"**{f}**")
                c1.audio(f_path)
                score = quality_eval.evaluate(f_path)
                c2.metric("Quality", f"{score}")
                if c3.button("🔄 Reverse", key=f"demo_rev_{f}"):
                    with st.spinner("Reversing demo..."):
                        psy_mono_bridge.run_full_reversal(f_path, output_dir)
                st.divider()

    st.subheader("Your Generations")
    if os.path.exists(output_dir):
        files = [f for f in os.listdir(output_dir) if f.endswith(('.wav', '.mp3', '.mp4'))]
        if not files:
            st.info("No files found in output directory.")
        else:
            # Sort by modification time (newest first)
            files.sort(key=lambda x: os.path.getmtime(os.path.join(output_dir, x)), reverse=True)

            for f in files:
                f_path = os.path.join(output_dir, f)
                c1, c2, c3, c4 = st.columns([2, 1, 1, 1])
                c1.write(f"**{f}**")

                # Show score if audio
                if f.endswith(('.wav', '.mp3')):
                    score = quality_eval.evaluate(f_path)
                    c2.metric("Quality Score", f"{score}")

                    # Metadata enrichment
                    meta_path = f_path.rsplit(".", 1)[0] + "_metadata.json"
                    if os.path.exists(meta_path):
                        try:
                            with open(meta_path, "r") as mf:
                                meta_data = json.load(mf)
                                title = meta_data.get('title', 'Unknown')
                                style_used = meta_data.get('style', 'N/A')
                                composer = meta_data.get('composer', 'Traditional')
                                c1.markdown(f"### {title}")
                                c1.caption(f"**Style:** {style_used} | **Composer:** {composer}")
                                if meta_data.get('lyrics'):
                                    with c1.expander("📜 View Lyrics"):
                                        for line in meta_data['lyrics']:
                                            st.write(line['text'])
                        except: pass

                    with c1:
                        st.audio(f_path)
                        with st.expander("⭐ Rate & Feedback"):
                            f_rating = st.slider("Rating", 1, 5, 5, key=f"rate_{f}")
                            f_comment = st.text_area("Comments", key=f"text_{f}")
                            if st.button("Submit Feedback", key=f"btn_{f}"):
                                with open("output/feedback_log.jsonl", "a") as flog:
                                    flog.write(json.dumps({
                                        "timestamp": time.time(),
                                        "file": f,
                                        "rating": f_rating,
                                        "comment": f_comment
                                    }) + "\n")
                                st.success("Feedback saved! 🙏")

                    with c3:
                        if st.button("🎹 Load Studio", key=f"load_{f}"):
                            if f.endswith('.wav'):
                                st.session_state.psy_player.stop_realtime()
                                st.info(f"Loading {f} to studio player...")
                                name_base = f.replace(".wav", "")
                                possible_mid = os.path.join(output_dir, f"{name_base}.mid")
                                if os.path.exists(possible_mid):
                                    st.session_state.psy_player.load(possible_mid)
                                    st.session_state.psy_player.start_realtime()
                                    st.session_state.psy_player.play()
                                    st.success(f"Playing {name_base}.mid")

                        if st.button("🔄 Reverse to Ableton", key=f"rev_{f}"):
                            with st.spinner(f"Reverse engineering {f}..."):
                                try:
                                    success = psy_mono_bridge.run_full_reversal(f_path, output_dir)
                                    if success:
                                        st.success("Successfully pushed to Ableton!")
                                    else:
                                        st.error("Reverse engineering failed. Check logs.")
                                except Exception as re_err:
                                    st.error(f"Error: {re_err}")
                else:
                    with c1:
                        st.video(f_path)

                if c4.button("🗑️ Delete", key=f"del_{f}"):
                    os.remove(f_path)
                    st.rerun()
                st.divider()
    else:
        st.error(f"Output directory not found: {output_dir}")

with tab5:
    st.header("🔬 Optimization & Analytics Dashboard")
    st.write("Conduct A/B/C/D testing to validate generation quality and adjust parameters.")

    import pandas as pd

    # Section 0: System Health Audit (v1.37.0)
    st.subheader("🛠️ System Health Audit")
    if st.button("Run Health Audit"):
        with st.status("Auditing System Environment...") as status:
            from scripts.health_check import check_binary, check_python_module

            binaries = ["ffmpeg", "fluidsynth", "basic-pitch"]
            modules = ["mido", "librosa", "torch", "transformers", "diffusers", "requests_oauthlib", "live", "flask"]

            results = []

            st.write("**Binaries:**")
            for b in binaries:
                ok = check_binary(b)
                results.append(ok)
                st.write(f"{'✅' if ok else '❌'} `{b}`")

            st.write("**Python Modules:**")
            for m in modules:
                ok = check_python_module(m)
                results.append(ok)
                st.write(f"{'✅' if ok else '❌'} `{m}`")

            st.write("**Project Integrity:**")
            sub_ok = os.path.exists("submodules/ableton_psytrance_hymn_creator")
            results.append(sub_ok)
            st.write(f"{'✅' if sub_ok else '❌'} Submodule: `ableton_psytrance_hymn_creator`")

            if all(results):
                st.success("SYSTEM HEALTHY. Ready for production.")
                status.update(label="Audit Complete: Healthy", state="complete")
            else:
                st.error("SYSTEM UNHEALTHY. Check failures above.")
                status.update(label="Audit Complete: Issues Found", state="error")

    # Section 1: A/B/C/D Testing
    st.subheader("1. A/B/C/D Variant Testing")
    test_midi = st.file_uploader("Upload MIDI for A/B Test", type=["mid", "midi"], key="ab_midi")

    if test_midi:
        if st.button("🚀 Generate 4 Variants"):
            test_path = os.path.join(settings.INPUT_DIR, "ab_test_input.mid")
            with open(test_path, "wb") as f:
                f.write(test_midi.getbuffer())

            variants = []
            for i, label in enumerate(['A', 'B', 'C', 'D']):
                out_v = os.path.join(output_dir, f"test_variant_{label}.mid")
                out_audio = out_v.replace(".mid", ".wav")

                # Randomize params for test
                v_config = {
                    "targetBpm": 145,
                    "euclideanDensity": random.randint(3, 13),
                    "gallopVariant": random.choice(["classic", "triplet", "rolling"]),
                    "mode": "loop"
                }
                st.session_state.psy_gen.generate(test_path, out_v, v_config)
                renderer.render(out_v, out_audio)
                variants.append({"label": label, "audio": out_audio, "config": v_config})
            st.session_state["ab_variants"] = variants

    if "ab_variants" in st.session_state:
        cols = st.columns(4)
        for i, v in enumerate(st.session_state["ab_variants"]):
            with cols[i]:
                st.write(f"**Variant {v['label']}**")
                st.audio(v['audio'])
                if st.button(f"Vote {v['label']}", key=f"vote_{v['label']}"):
                    st.success(f"Voted for {v['label']}!")
                    # Log winning params
                    with open("output/parameter_optimization.jsonl", "a") as f:
                        f.write(json.dumps({
                            "timestamp": time.time(),
                            "winner": v['label'],
                            "config": v['config']
                        }) + "\n")

    # Section 2: Analytics
    st.subheader("2. Feedback Analytics")
    feedback_file = "output/feedback_log.jsonl"
    if os.path.exists(feedback_file):
        data = []
        with open(feedback_file, "r") as f:
            for line in f:
                data.append(json.loads(line))

        if data:
            df = pd.DataFrame(data)
            # Flatten config
            df_config = pd.json_normalize(df['config'])
            df = pd.concat([df.drop('config', axis=1), df_config], axis=1)

            st.write("### Rating vs. Euclidean Density")
            fig = go.Figure(data=go.Scattergl(
                x=df['density'],
                y=df['rating'],
                mode='markers',
                marker=dict(size=12, color=df['rating'], colorscale='Viridis', showscale=True)
            ))
            fig.update_layout(xaxis_title="Euclidean Density", yaxis_title="User Rating")
            st.plotly_chart(fig, use_container_width=True)

            st.write("### Style Preference Distribution")
            style_counts = df['algo_style'].value_counts()
            fig_pie = go.Figure(data=[go.Pie(labels=style_counts.index, values=style_counts.values)])
            st.plotly_chart(fig_pie, use_container_width=True)
        else:
            st.info("No feedback data yet.")
    else:
        st.info("Log file not found. Submit feedback in the Studio tab first.")
