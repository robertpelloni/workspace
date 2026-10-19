import os
import sys
import glob
import logging
import argparse
import json
import requests
import time
import numpy as np
from watchdog.observers import Observer
from watchdog.events import FileSystemEventHandler
from dotenv import load_dotenv
from hymn_remaker import settings

from hymn_remaker.src.midi_renderer import MidiRenderer
from hymn_remaker.src.remaker import MusicRemaker
from hymn_remaker.src.suno_remaker import SunoRemaker
from hymn_remaker.src.udio_remaker import UdioRemaker
from hymn_remaker.src.udio_oauth_remaker import UdioOAuthRemaker
from hymn_remaker.src.gemini_generator import GeminiContentGenerator
from hymn_remaker.src.ai_video import AIVideoGenerator
from hymn_remaker.src.video_uploader import VideoProducer
from hymn_remaker.src.musicxml_parser import MusicXMLParser
from hymn_remaker.src.omr_processor import OMRProcessor
from hymn_remaker.src.stem_separator import StemSeparator
from hymn_remaker.src.radio_streamer import RadioStreamer
from hymn_remaker.src.utils import process_audio
from hymn_remaker.src.midi_analyzer import MidiAnalyzer
from hymn_remaker.src.psy_sequencer import PsyGenerator
from hymn_remaker.src.vocal_remix import VocalRemixer
from hymn_remaker.src.local_remaker import LocalMusicRemaker
from hymn_remaker.src.quality_evaluator import QualityEvaluator

# Load environment variables
load_dotenv()

# Force root logger level and handler configuration to ensure all module logs print
root_logger = logging.getLogger()
root_logger.setLevel(logging.INFO)
for h in root_logger.handlers[:]:
    root_logger.removeHandler(h)
handler = logging.StreamHandler(sys.stdout)
handler.setFormatter(
    logging.Formatter("%(asctime)s - %(name)s - %(levelname)s - %(message)s")
)
root_logger.addHandler(handler)

logger = logging.getLogger("HymnRemaker")


def generate_fallback_gradient(output_path):
    """
    Generates a high-quality, premium dark abstract gradient image
    (deep purple, midnight blue, and warm magenta/cyan accent)
    to serve as a beautiful background fallback.
    """
    try:
        from PIL import Image, ImageDraw

        width, height = 1920, 1080
        image = Image.new("RGB", (width, height))
        draw = ImageDraw.Draw(image)

        # Base vertical gradient: dark violet to deep navy
        for y in range(height):
            factor = y / height
            r1, g1, b1 = 15, 10, 30  # Deep dark violet
            r2, g2, b2 = 5, 5, 20  # Midnight navy
            r = int(r1 + (r2 - r1) * factor)
            g = int(g1 + (g2 - g1) * factor)
            b = int(b1 + (b2 - b1) * factor)
            draw.line([(0, y), (width, y)], fill=(r, g, b))

        # Draw a beautiful soft radial glow in the center-right (warm magenta)
        glow_x, glow_y = int(width * 0.7), int(height * 0.3)
        glow_radius = 600
        glow_img = Image.new("RGBA", (width, height), (0, 0, 0, 0))
        glow_draw = ImageDraw.Draw(glow_img)

        for r in range(glow_radius, 0, -8):
            alpha = int(35 * (1.0 - (r / glow_radius) ** 1.5))
            if alpha <= 0:
                continue
            glow_draw.ellipse(
                [glow_x - r, glow_y - r, glow_x + r, glow_y + r],
                fill=(235, 75, 130, alpha),
            )

        # Draw a second soft cyan-blue glow in the bottom-left
        glow_x2, glow_y2 = int(width * 0.25), int(height * 0.75)
        glow_radius2 = 500
        for r in range(glow_radius2, 0, -8):
            alpha = int(25 * (1.0 - (r / glow_radius2) * 1.5))
            if alpha <= 0:
                continue
            glow_draw.ellipse(
                [glow_x2 - r, glow_y2 - r, glow_x2 + r, glow_y2 + r],
                fill=(50, 150, 240, alpha),
            )

        # Composite the glow on the base gradient
        final_image = Image.alpha_composite(image.convert("RGBA"), glow_img)
        final_image.convert("RGB").save(output_path, "PNG")
        logger.info(f"Generated beautiful fallback gradient at {output_path}")
        return output_path
    except Exception as e:
        logger.error(f"Failed to generate fallback gradient: {e}")
        return None


def main():
    parser = argparse.ArgumentParser(description="Hymn Remaker Pipeline")
    parser.add_argument(
        "--input-dir",
        default="hymn_remaker/input",
        help="Directory containing input MIDI files",
    )
    parser.add_argument(
        "--soundfont", help="Path to custom soundfont"
    )
    parser.add_argument(
        "--output-dir", default="hymn_remaker/output", help="Directory for output files"
    )
    parser.add_argument(
        "--style",
        default=settings.DEFAULT_STYLE,
        help="Musical style prompt for the remake",
    )
    parser.add_argument(
        "--upload", action="store_true", help="Upload to YouTube after generation"
    )
    parser.add_argument(
        "--skip-render", action="store_true", help="Skip MIDI rendering if WAV exists"
    )
    parser.add_argument(
        "--skip-remake",
        action="store_true",
        help="Skip music generation if output audio exists",
    )
    parser.add_argument(
        "--remake-priority",
        default=settings.REMAKE_PRIORITY,
        choices=["suno", "udio", "udio-oauth", "replicate", "local"],
        help="AI service priority for Step 2 remake (default: suno)",
    )
    parser.add_argument(
        "--local-guidance",
        type=float,
        default=3.0,
        help="Local MusicGen guidance scale",
    )
    parser.add_argument(
        "--local-temperature",
        type=float,
        default=1.0,
        help="Local MusicGen temperature",
    )
    parser.add_argument(
        "--suno-session",
        default=None,
        help="Suno AI session token (overrides SUNO_SESSION_TOKEN env var)",
    )
    parser.add_argument(
        "--udio-token",
        default=None,
        help="Udio AI auth token (overrides UDIO_AUTH_TOKEN env var)",
    )
    parser.add_argument(
        "--udio-cookie", default=None, help="Udio AI full cookie string (most reliable)"
    )
    parser.add_argument(
        "--udio-variance",
        type=float,
        default=0.25,
        help="Udio remix variance (0.1 to 1.0). Lower is stricter.",
    )
    parser.add_argument(
        "--udio-neg-prompt",
        default="organ, classical, baroque, church organ, cathedral",
        help="Styles to avoid in Udio remix",
    )
    parser.add_argument(
        "--sonic-vacuum",
        action="store_true",
        help="Use Sonic Vacuum preprocessor (dry render)",
    )
    parser.add_argument(
        "--symbolic-norm",
        action="store_true",
        help="Use Symbolic Normalizer (velocity flattening)",
    )
    parser.add_argument(
        "--house-quantizer",
        action="store_true",
        help="Use House Structural Quantizer (snap to 124 BPM grid)",
    )
    parser.add_argument(
        "--mix-vocals",
        help="Path to hip-hop audio track or YouTube URL to isolate and mix vocals from",
    )
    parser.add_argument(
        "--convert-mp3",
        action="store_true",
        help="Batch convert all base WAV files to MP3 and exit",
    )
    parser.add_argument(
        "--voice-id",
        default=settings.DEFAULT_ELEVENLABS_VOICE_ID,
        help="ElevenLabs Voice ID",
    )
    parser.add_argument(
        "--model", default=settings.DEFAULT_ELEVENLABS_MODEL, help="ElevenLabs Model"
    )
    parser.add_argument(
        "--video-format",
        default=settings.DEFAULT_VIDEO_FORMAT,
        choices=["Standard 16:9", "Vertical 9:16 (TikTok/Reels)"],
        help="Output video format",
    )
    parser.add_argument(
        "--daemon",
        action="store_true",
        help="Run in daemon mode, watching the input directory for new files continuously.",
    )
    parser.add_argument(
        "--create-shorts",
        action="store_true",
        help="Extract 15-second short clips from the final video.",
    )
    parser.add_argument(
        "--stream-rtmp", default=None, help="RTMP URL for live DJ radio streaming"
    )
    parser.add_argument(
        "--visualizer",
        action="store_true",
        help="Enable audio-reactive visualizer overlay",
    )
    parser.add_argument(
        "--visualizer-mode",
        default="cline",
        choices=["cline", "line", "p2p", "avectorscope"],
        help="Visualizer mode type",
    )
    parser.add_argument(
        "--transient",
        action="store_true",
        help="Enable Pure Transient rendering (Woodblock pulses) for better AI inspiration",
    )
    parser.add_argument(
        "--ai-video",
        action="store_true",
        help="Generate AI-powered dynamic video background",
    )
    parser.add_argument(
        "--use-quotes",
        action="store_true",
        help="Overlay soulful quotes timed to beats instead of lyrics",
    )
    parser.add_argument(
        "--local-video",
        action="store_true",
        help="Force local GPU video generation instead of Replicate cloud",
    )
    parser.add_argument(
        "--video-model",
        default="ltx-video",
        choices=["ltx-video", "wan"],
        help="Local video generation model type",
    )
    parser.add_argument(
        "--video-model-size",
        default="1.3b",
        choices=["1.3b", "14b"],
        help="Local video generation model size",
    )
    parser.add_argument(
        "--speed",
        type=float,
        default=1.0,
        choices=[0.5, 1.0, 2.0],
        help="Playback speed for Sonic Vacuum preprocessor",
    )
    parser.add_argument(
        "--suno-matrix",
        action="store_true",
        help="v1.37.0: Execute 9-way Suno Experiment Matrix (3 speeds x 3 genres)",
    )
    args = parser.parse_args()

    os.makedirs(args.output_dir, exist_ok=True)

    # Lazy-loaded component holders
    components = {
        "renderer": None,
        "remaker": None,
        "suno_remaker": None,
        "udio_remaker": None,
        "udio_oauth_remaker": None,
        "local_remaker": None,
        "content_gen": None,
        "ai_video_gen": None,
        "video_producer": None,
        "mxl_parser": None,
        "omr_processor": None,
        "stem_separator": None,
        "radio_streamer": None,
        "quality_eval": None,
    }

    def get_comp(name):
        if components[name]:
            return components[name]
        logger.info(f"Initializing {name}...")
        if name == "renderer":
            components[name] = MidiRenderer(soundfont_path=args.soundfont)
        elif name == "remaker":
            components[name] = MusicRemaker()
        elif name == "suno_remaker":
            components[name] = SunoRemaker(session_token=args.suno_session)
        elif name == "udio_remaker":
            components[name] = UdioRemaker(
                auth_token=args.udio_token, cookie_string=args.udio_cookie
            )
        elif name == "udio_oauth_remaker":
            components[name] = UdioOAuthRemaker()
        elif name == "local_remaker":
            components[name] = LocalMusicRemaker()
        elif name == "content_gen":
            components[name] = GeminiContentGenerator()
        elif name == "ai_video_gen":
            components[name] = AIVideoGenerator()
        elif name == "video_producer":
            components[name] = VideoProducer()
        elif name == "mxl_parser":
            components[name] = MusicXMLParser()
        elif name == "omr_processor":
            components[name] = OMRProcessor()
        elif name == "stem_separator":
            components[name] = StemSeparator()
        elif name == "quality_eval":
            components[name] = QualityEvaluator()
        elif name == "radio_streamer":
            components[name] = RadioStreamer()
        return components[name]

    import concurrent.futures

    def run_pipeline(midi_file_list):
        if not midi_file_list:
            return
        # Force single worker if using browser automation
        use_browser_automation = args.remake_priority in ["suno", "udio", "udio-oauth"]
        worker_count = 1 if use_browser_automation else min(4, len(midi_file_list))

        with concurrent.futures.ThreadPoolExecutor(
            max_workers=worker_count
        ) as executor:
            futures = {
                executor.submit(
                    process_single_midi,
                    midi_path,
                    args.output_dir,
                    args.style,
                    args.skip_render,
                    args.skip_remake,
                    args.upload,
                    get_comp("renderer"),
                    get_comp("remaker"),
                    suno_remaker=get_comp("suno_remaker"),
                    udio_remaker=get_comp("udio_remaker"),
                    udio_oauth_remaker=get_comp("udio_oauth_remaker"),
                    local_remaker=get_comp("local_remaker"),
                    remake_priority=args.remake_priority,
                    content_gen=get_comp("content_gen"),
                    video_producer=get_comp("video_producer"),
                    mxl_parser=get_comp("mxl_parser"),
                    omr_processor=get_comp("omr_processor"),
                    tts_generator=None,
                    stem_separator=get_comp("stem_separator"),
                    voice_id=args.voice_id,
                    model=args.model,
                    video_format=args.video_format,
                    create_shorts=args.create_shorts,
                    enable_visualizer=args.visualizer,
                    visualizer_mode=args.visualizer_mode,
                    ai_video_gen=get_comp("ai_video_gen") if args.ai_video else None,
                    use_quotes=args.use_quotes,
                    local_video=args.local_video,
                    video_model=args.video_model,
                    video_model_size=args.video_model_size,
                    udio_variance=args.udio_variance,
                    udio_neg_prompt=args.udio_neg_prompt,
                    local_guidance=args.local_guidance,
                    local_temperature=args.local_temperature,
                    transient=args.transient,
                    speed=args.speed,
                    sonic_vacuum=args.sonic_vacuum,
                    symbolic_norm=args.symbolic_norm,
                    house_quantizer=args.house_quantizer,
                    hiphop_vocal_path=args.mix_vocals,
                    quality_evaluator=get_comp("quality_eval"),
                    suno_matrix=args.suno_matrix,
                ): midi_path
                for midi_path in midi_file_list
            }
            for future in concurrent.futures.as_completed(futures):
                midi_path = futures[future]
                try:
                    future.result()
                except Exception as e:
                    logger.error(f"Error processing {midi_path} through executor: {e}")

    # Batch MP3 conversion mode
    if args.convert_mp3:
        logger.info("Batch converting base WAV files to MP3...")
        converted, failed = get_comp("suno_remaker").batch_wav_to_mp3(
            args.output_dir, bitrate=settings.DEFAULT_MP3_BITRATE
        )
        logger.info(f"MP3 conversion complete: {converted} converted, {failed} failed")
        sys.exit(0 if failed == 0 else 1)

    initial_midi_files = (
        glob.glob(os.path.join(args.input_dir, "*.mid"))
        + glob.glob(os.path.join(args.input_dir, "*.mxl"))
        + glob.glob(os.path.join(args.input_dir, "*.xml"))
    )
    if initial_midi_files:
        logger.info(f"Found {len(initial_midi_files)} initial MIDI files to process.")
        run_pipeline(initial_midi_files)
    else:
        logger.warning(f"No initial MIDI files found in {args.input_dir}")

    streamer = None
    if args.stream_rtmp:
        logger.info(f"Initializing Live DJ Radio Stream to {args.stream_rtmp}...")
        streamer = get_comp("radio_streamer")
        if streamer:
            streamer.rtmp_url = args.stream_rtmp
            streamer.input_dir = args.output_dir
            streamer.start()

    if args.daemon:
        logger.info(
            f"Starting Daemon Mode. Monitoring {args.input_dir} for new files..."
        )

        class MidiHandler(FileSystemEventHandler):
            def on_created(self, event):
                valid_exts = (".mid", ".mxl", ".xml", ".png", ".jpg", ".pdf")
                if not event.is_directory and any(
                    event.src_path.lower().endswith(ext) for ext in valid_exts
                ):
                    logger.info(f"Detected new Input file: {event.src_path}")
                    time.sleep(1)
                    run_pipeline([event.src_path])

            def on_moved(self, event):
                valid_exts = (".mid", ".mxl", ".xml", ".png", ".jpg", ".pdf")
                if not event.is_directory and any(
                    event.dest_path.lower().endswith(ext) for ext in valid_exts
                ):
                    logger.info(f"Detected moved file: {event.dest_path}")
                    time.sleep(1)
                    run_pipeline([event.dest_path])

        observer = Observer()
        observer.schedule(MidiHandler(), args.input_dir, recursive=False)
        observer.start()
        try:
            while True:
                time.sleep(1)
        except KeyboardInterrupt:
            logger.info("Stopping Daemon Mode...")
            observer.stop()
            if streamer:
                streamer.stop()
            observer.join()
    else:
        if not initial_midi_files:
            sys.exit(0)


def generate_beat_synced_quotes(
    audio_path, tempo_bpm, quotes_file="hymn_remaker/src/quotes.json", duration_sec=None
):
    """
    Generate subtitle lyrics timed to the beats using quotes from quotes_file.
    """
    import json
    import os
    import random

    if not duration_sec:
        try:
            import wave

            with wave.open(audio_path, "rb") as wav_file:
                frames = wav_file.getnframes()
                rate = wav_file.getframerate()
                duration_sec = frames / float(rate)
        except Exception:
            duration_sec = 30.0

    if not os.path.exists(quotes_file):
        logger.warning(f"Quotes file not found at {quotes_file}")
        return []

    try:
        with open(quotes_file, "r", encoding="utf-8") as f:
            quotes = json.load(f)
    except Exception as e:
        logger.error(f"Failed to load quotes: {e}")
        return []

    if not quotes:
        return []

    beat_interval = 60.0 / tempo_bpm
    # We change quotes every 16 beats (4 bars at 4/4)
    beats_per_quote = 16
    quote_interval = beat_interval * beats_per_quote

    num_quotes_needed = int(duration_sec / quote_interval) + 1

    lyrics = []

    # Deterministic choice of quotes based on file name or length so it remains stable on reruns
    random.seed(len(audio_path))
    selected_quotes = random.sample(quotes, min(len(quotes), num_quotes_needed))
    if len(selected_quotes) < num_quotes_needed:
        selected_quotes = (
            selected_quotes * (num_quotes_needed // len(selected_quotes) + 1)
        )[:num_quotes_needed]

    for i in range(num_quotes_needed):
        start_time = i * quote_interval
        end_time = min(start_time + quote_interval - 0.5, duration_sec)
        if start_time >= duration_sec:
            break
        lyrics.append(
            {"start": start_time, "end": end_time, "text": selected_quotes[i]}
        )

    return lyrics


def process_single_midi(
    midi_path,
    output_dir,
    style,
    skip_render,
    skip_remake,
    upload,
    renderer,
    remaker,
    quality_evaluator=None,
    suno_remaker=None,
    udio_remaker=None,
    udio_oauth_remaker=None,
    local_remaker=None,
    remake_priority="suno",
    content_gen=None,
    video_producer=None,
    mxl_parser=None,
    omr_processor=None,
    tts_generator=None,
    stem_separator=None,
    normalize_audio=True,
    fade_in_ms=0,
    fade_out_ms=0,
    generate_vocals=False,
    voice_id=settings.DEFAULT_ELEVENLABS_VOICE_ID,
    model=settings.DEFAULT_ELEVENLABS_MODEL,
    video_format=settings.DEFAULT_VIDEO_FORMAT,
    create_shorts=False,
    status_callback=None,
    sub_font_size=24,
    sub_primary_color="#FFFFFF",
    sub_outline_color="#000000",
    sub_back_color="#000000",
    sub_box=True,
    enable_visualizer=False,
    visualizer_mode="cline",
    interactive_callback=None,
    ai_video_gen=None,
    use_quotes=False,
    local_video=False,
    video_model="ltx-video",
    video_model_size="1.3b",
    udio_variance=0.25,
    speed=1.0,
    udio_neg_prompt="organ, classical, baroque, church organ, cathedral",
    local_guidance=3.0,
    local_temperature=1.0,
    transient=False,
    sonic_vacuum=False,
    symbolic_norm=False,
    house_quantizer=False,
    hiphop_vocal_path=None,
    suno_matrix=False,
):

    base_audio_path = remake_audio_path = metadata_path = vocal_track_path = None
    try:
        filename = os.path.basename(midi_path)
        name_no_ext = os.path.splitext(filename)[0]

        def update_status(msg, progress):
            logger.info(msg)
            if status_callback:
                status_callback(msg, progress)

        update_status(f"Processing {filename}...", 10)
        pre_extracted_metadata = {}
        target_midi_path = midi_path

        # -1. Check if input is an image/PDF (OMR)
        if filename.lower().endswith((".png", ".jpg", ".pdf")):
            update_status(f"Step 0/4: Running OMR on sheet music ({filename})...", 12)
            if omr_processor and omr_processor.is_available():
                target_mxl_path = omr_processor.process(midi_path, output_dir)
                filename = os.path.basename(target_mxl_path)
                midi_path = target_mxl_path
                name_no_ext = os.path.splitext(filename)[0]
            else:
                logger.error(
                    "OMR processor is not available or oemer is not installed."
                )
                raise RuntimeError(
                    "Cannot process image/PDF without an active OMR processor."
                )

        # 0. Check if input is MusicXML and extract/convert
        if filename.lower().endswith((".mxl", ".xml")):
            update_status(
                f"Step 0/4: Parsing MusicXML and converting to MIDI ({filename})...", 15
            )
            target_midi_path = os.path.join(output_dir, f"{name_no_ext}_converted.mid")
            if mxl_parser:
                pre_extracted_metadata = mxl_parser.process(midi_path, target_midi_path)
            else:
                logger.warning("MusicXML parser not available, skipping XML parsing.")
        elif filename.lower().endswith(".mid"):
            update_status(
                f"Step 0/4: Parsing MIDI metadata and lyrics ({filename})...", 15
            )
            pre_extracted_metadata = MidiAnalyzer.extract_all_metadata(midi_path)

        # Apply Experimental Preprocessors
        # Structural Validation Gate (v1.37.0)
        if target_midi_path.endswith(".mid"):
            try:
                import mido
                mid_check = mido.MidiFile(target_midi_path)
                if len(mid_check.tracks) < 1:
                    logger.warning(f"STRUCTURAL GATE: {filename} MIDI has no tracks!")
            except Exception as se:
                logger.error(f"STRUCTURAL GATE ERROR: {se}")
        if symbolic_norm:
            update_status("Experiment: Applying Symbolic Normalization...", 16)
            from pipeline.processing.symbolic_norm import SymbolicNormalizer

            norm_path = os.path.join(output_dir, f"{name_no_ext}_norm.mid")
            SymbolicNormalizer(target_midi_path).normalize(norm_path)
            target_midi_path = norm_path

        if house_quantizer:
            update_status("Experiment: Applying House Structural Quantization...", 17)
            from pipeline.processing.house_quantizer import HouseStructuralQuantizer

            hq_path = os.path.join(output_dir, f"{name_no_ext}_house.mid")
            HouseStructuralQuantizer(target_midi_path).quantize(hq_path)
            target_midi_path = hq_path

        # 1. Render MIDI to Audio (WAV)
        update_status(f"Step 1/4: Rendering MIDI ({filename})...", 20)
        base_audio_path = os.path.join(output_dir, f"{name_no_ext}_base.wav")

        # Experimental Pipeline modules
        is_sonic_vacuum = "sonic vacuum" in style.lower() or sonic_vacuum
        is_symbolic_norm = "symbolic norm" in style.lower() or symbolic_norm
        is_house_quantizer = "house quantizer" in style.lower() or house_quantizer
        is_psytrance = "psytrance" in style.lower()

        transient_only = False

        if is_sonic_vacuum or is_symbolic_norm or is_house_quantizer:
            update_status(f"Running Experimental Pipeline for {style}...", 21)
            try:
                # Ensure output directories exist for the manual script run
                os.makedirs(os.path.join(output_dir, "dry_render"), exist_ok=True)
                os.makedirs(os.path.join(output_dir, "symbolic_midi"), exist_ok=True)
                os.makedirs(os.path.join(output_dir, "house_skeletons"), exist_ok=True)

                if is_sonic_vacuum:
                    from pipeline.processing.sonic_vacuum import SonicVacuumProcessor

                    base_audio_path = os.path.join(
                        output_dir, "dry_render", f"{name_no_ext}_dry.wav"
                    )
                    vacuum = SonicVacuumProcessor(target_midi_path)
                    audio_arr, sr = vacuum.render_dry_piano(None, return_audio=True)
                    # Use speed variant logic
                    if speed == 0.5:
                        indices = np.arange(0, len(audio_arr), 0.5)
                        indices = np.clip(indices, 0, len(audio_arr) - 1).astype(np.int64)
                        audio_arr = audio_arr[indices]
                    elif speed == 2.0:
                        audio_arr = audio_arr[::2]
                    import scipy.io.wavfile as wavfile
                    wavfile.write(base_audio_path, sr, (audio_arr * 32767).astype(np.int16))

                if is_symbolic_norm:
                    from pipeline.processing.symbolic_norm import SymbolicNormalizer

                    target_midi_path_norm = os.path.join(
                        output_dir, "symbolic_midi", f"{name_no_ext}_norm.mid"
                    )
                    SymbolicNormalizer(target_midi_path).normalize(
                        target_midi_path_norm
                    )
                    target_midi_path = target_midi_path_norm

                if is_house_quantizer:
                    from pipeline.processing.house_quantizer import (
                        HouseStructuralQuantizer,
                    )

                    target_midi_path_house = os.path.join(
                        output_dir, "house_skeletons", f"{name_no_ext}_house.mid"
                    )
                    HouseStructuralQuantizer(target_midi_path).quantize(
                        target_midi_path_house
                    )
                    target_midi_path = target_midi_path_house

            except Exception as e:
                logger.error(f"Experimental pipeline failed: {e}")

        if is_psytrance:
            update_status(
                "Psy-Mono: Invoking Python Algorithmic Psytrance Sequencer...", 22
            )
            psy_midi_path = os.path.join(output_dir, f"{name_no_ext}_psy.mid")
            try:
                psy_gen = PsyGenerator()
                psy_gen.generate(
                    target_midi_path, psy_midi_path, config={"targetBpm": 145}
                )
                target_midi_path = psy_midi_path
                transient_only = True
            except Exception as e:
                logger.error(f"Psytrance sequencer failed: {e}")

        # Extract precise BPM to prevent AI tempo drift
        target_bpm = 120.0
        if os.path.exists(target_midi_path):
            if remake_priority in ["udio", "udio-oauth"]:
                stretched_midi_path = os.path.join(
                    output_dir, f"{name_no_ext}_stretched.mid"
                )
                update_status(
                    "Stretching MIDI to fit 28.0 seconds for Udio reference...", 24
                )
                stretch_success = renderer.stretch_midi(
                    target_midi_path, stretched_midi_path, target_duration=28.0
                )
                if stretch_success and os.path.exists(stretched_midi_path):
                    target_midi_path = stretched_midi_path

            target_bpm = renderer.get_midi_bpm(target_midi_path)
            update_status(f"Extracted dynamic tempo: {target_bpm:.1f} BPM", 25)

        if not skip_render or not os.path.exists(base_audio_path):
            renderer.render(
                target_midi_path,
                base_audio_path,
                transient=transient,
                transient_only=(transient_only or sonic_vacuum),
            )
        else:
            update_status(
                f"Skipping render for {filename}, {base_audio_path} exists.", 30
            )

        # 2. Generate Remake (Udio AI -> Suno AI -> Replicate MusicGen -> Base Audio Fallback)
        remake_audio_path = os.path.join(output_dir, f"{name_no_ext}_remake.wav")
        if not skip_remake or not os.path.exists(remake_audio_path):
            remake_success = False

            # --- Priority 0: Local MusicGen ---
            if remake_priority == "local" and local_remaker:
                update_status(
                    f"Step 2/4: Remaking Audio via Local MusicGen ({filename})...", 40
                )
                try:
                    local_remaker.generate(
                        style,
                        melody_path=base_audio_path,
                        duration=30,
                        output_path=remake_audio_path,
                        guidance_scale=local_guidance,
                        temperature=local_temperature,
                    )
                    update_status(f"Local MusicGen remake complete for {filename}", 55)
                    process_audio(
                        remake_audio_path,
                        remake_audio_path,
                        normalize=normalize_audio,
                        fade_in_ms=fade_in_ms,
                        fade_out_ms=fade_out_ms,
                    )
                    remake_success = True
                    logger.info(f"Local MusicGen remake succeeded for {filename}")
                except Exception as local_err:
                    logger.warning(f"Local MusicGen failed for {filename}: {local_err}")
                    update_status("Local MusicGen error, trying fallbacks...", 42)

            # --- v1.37.0: Suno Experiment Matrix ---
            if suno_matrix and suno_remaker and suno_remaker.is_available():
                update_status(f"Step 2/4: Executing Suno 9-way Experiment Matrix for {filename}...", 40)
                try:
                    lyrics_text = pre_extracted_metadata.get("raw_lyrics_text")
                    suno_remaker.browser_automation.run_experiment_matrix(
                        target_midi_path, output_dir, lyrics=lyrics_text
                    )
                    # We continue the normal pipeline with the primary remake
                except Exception as matrix_err:
                    logger.error(f"Suno Matrix failed: {matrix_err}")

            # --- Priority 1: Suno AI (audio influence -> Deep House) ---
            if (
                not remake_success
                and (
                    remake_priority == "suno"
                    or remake_priority == "udio"
                    or remake_priority == "udio-oauth"
                )
                and suno_remaker
                and suno_remaker.is_available()
            ):
                update_status(
                    f"Step 2/4: Remaking Audio via Suno AI ({filename})...", 40
                )
                try:
                    tempo_enforced_style = f"{style}, {target_bpm:.1f} BPM"
                    # Extract lyrics from metadata if available
                    lyrics = pre_extracted_metadata.get("raw_lyrics_text")
                    suno_result = suno_remaker.remake(
                        base_audio_path, tempo_enforced_style, lyrics=lyrics
                    )
                    if suno_result and os.path.exists(suno_result):
                        if suno_result != remake_audio_path:
                            import shutil

                            shutil.move(suno_result, remake_audio_path)
                        update_status(f"Suno AI remake complete for {filename}", 55)
                        process_audio(
                            remake_audio_path,
                            remake_audio_path,
                            normalize=normalize_audio,
                            fade_in_ms=fade_in_ms,
                            fade_out_ms=fade_out_ms,
                        )
                        remake_success = True
                        logger.info(f"Suno AI remake succeeded for {filename}")
                except Exception as suno_err:
                    logger.warning(f"Suno AI failed for {filename}: {suno_err}")
                    update_status(
                        f"Suno AI error for {filename}, trying Udio fallback...", 42
                    )

            # --- Priority 2: Udio AI (Official OAuth API) ---
            if (
                not remake_success
                and (remake_priority == "suno" or remake_priority == "udio-oauth")
                and udio_oauth_remaker
                and udio_oauth_remaker.is_available()
            ):
                update_status(
                    f"Step 2/4: Remaking Audio via Udio OAuth API ({filename})...", 43
                )
                try:
                    udio_result = udio_oauth_remaker.remake(
                        base_audio_path, style, variance=udio_variance
                    )
                    if udio_result and os.path.exists(udio_result):
                        if udio_result != remake_audio_path:
                            import shutil

                            shutil.move(udio_result, remake_audio_path)
                        update_status(f"Udio OAuth remake complete for {filename}", 55)
                        process_audio(
                            remake_audio_path,
                            remake_audio_path,
                            normalize=normalize_audio,
                            fade_in_ms=fade_in_ms,
                            fade_out_ms=fade_out_ms,
                        )
                        remake_success = True
                        logger.info(f"Udio OAuth remake succeeded for {filename}")
                except Exception as udio_err:
                    logger.warning(f"Udio OAuth failed for {filename}: {udio_err}")
                    update_status("Udio OAuth error, trying session-based Udio...", 44)

            # --- Priority 3: Udio AI (Session-based) ---
            if not remake_success and (
                remake_priority == "suno"
                or remake_priority == "udio"
                or (
                    remake_priority == "udio-oauth"
                    and udio_remaker
                    and udio_remaker.is_available()
                )
            ):
                update_status(
                    f"Step 2/4: Remaking Audio via Udio AI ({filename})...", 45
                )
                try:
                    clean_title = (
                        pre_extracted_metadata.get("title")
                        or name_no_ext.replace("_", " ").replace("-", " ")
                    ).title()
                    composer = pre_extracted_metadata.get("composer") or "Traditional"
                    rich_prompt = f"A modern {style} remix of '{clean_title}' by {composer}. Inspired by the original MIDI melody as reference media. {target_bpm:.1f} BPM."

                    udio_result = udio_remaker.remake(
                        base_audio_path,
                        rich_prompt,
                        variance=udio_variance,
                        negative_prompt=udio_neg_prompt,
                    )
                    if udio_result and os.path.exists(udio_result):
                        if udio_result != remake_audio_path:
                            import shutil

                            shutil.move(udio_result, remake_audio_path)
                        update_status(f"Udio AI remake complete for {filename}", 55)
                        process_audio(
                            remake_audio_path,
                            remake_audio_path,
                            normalize=normalize_audio,
                            fade_in_ms=fade_in_ms,
                            fade_out_ms=fade_out_ms,
                        )
                        remake_success = True
                        logger.info(f"Udio AI remake succeeded for {filename}")
                except Exception as udio_err:
                    logger.warning(f"Udio AI failed for {filename}: {udio_err}")
                    update_status(
                        f"Udio AI error for {filename}, trying Replicate fallback...",
                        47,
                    )

            # --- Priority 4: Replicate MusicGen ---
            if not remake_success:
                update_status(
                    f"Step 2/4: Trying Replicate MusicGen fallback ({filename})...", 43
                )
                try:
                    tempo_enforced_style = f"{style}. The track must be exactly {target_bpm:.1f} BPM. Keep this exact tempo."
                    remake_url = remaker.remake(base_audio_path, tempo_enforced_style)
                    response = requests.get(remake_url)
                    response.raise_for_status()
                    with open(remake_audio_path, "wb") as f:
                        f.write(response.content)
                    process_audio(
                        remake_audio_path,
                        remake_audio_path,
                        normalize=normalize_audio,
                        fade_in_ms=fade_in_ms,
                        fade_out_ms=fade_out_ms,
                    )
                    remake_success = True
                    logger.info(f"Replicate MusicGen remake succeeded for {filename}")
                except Exception as remake_err:
                    logger.warning(f"Remake failed for {filename}: {remake_err}")

            # --- Priority 5: Base Audio Fallback ---
            if not remake_success:
                update_status(f"Using base audio as fallback for {filename}", 55)
                import shutil

                shutil.copy2(base_audio_path, remake_audio_path)
                process_audio(
                    remake_audio_path,
                    remake_audio_path,
                    normalize=normalize_audio,
                    fade_in_ms=fade_in_ms,
                    fade_out_ms=fade_out_ms,
                )
        else:
            update_status(
                f"Skipping remake for {filename}, {remake_audio_path} exists.", 60
            )

        # 3. Generate Content (Metadata, Lyrics & Art)
        update_status(
            f"Step 3/4: Analyzing Audio and Generating Lyrics, Art & Metadata ({filename})...",
            70,
        )
        metadata_path = os.path.join(output_dir, f"{name_no_ext}_metadata.json")

        if os.path.exists(metadata_path):
            with open(metadata_path, "r") as f:
                metadata = json.load(f)
            lyrics = metadata.get("lyrics", [])
            art_prompt = metadata.get(
                "art_prompt",
                f"Abstract album art for {metadata.get('title', name_no_ext)}, {style} style, high quality, 4k",
            )
        else:
            analysis_data = content_gen.analyze_audio_for_content(
                base_audio_path, name_no_ext, style=style
            )
            if not analysis_data:
                logger.warning(
                    f"Audio analysis failed for {name_no_ext}. Using fallbacks."
                )
                analysis_data = {
                    "metadata": {},
                    "lyrics": [],
                    "theme": "Peaceful reflection",
                    "visual_prompt": f"Peaceful landscape, {style}",
                }

            metadata = analysis_data.get("metadata", {})
            lyrics = analysis_data.get("lyrics", [])
            extracted_lyrics = pre_extracted_metadata.get("lyrics")
            if (
                extracted_lyrics
                and isinstance(extracted_lyrics, list)
                and len(extracted_lyrics) > 0
            ):
                lyrics = extracted_lyrics
            art_prompt = content_gen.generate_art_prompt(analysis_data, style=style)
            with open(metadata_path, "w") as f:
                metadata["lyrics"] = lyrics
                metadata["art_prompt"] = art_prompt
                json.dump(metadata, f, indent=4)

        if interactive_callback:
            edited_data = interactive_callback(
                {"metadata": metadata, "lyrics": lyrics, "art_prompt": art_prompt}
            )
            if edited_data:
                metadata = edited_data.get("metadata", metadata)
                lyrics = edited_data.get("lyrics", lyrics)
                art_prompt = edited_data.get("art_prompt", art_prompt)
                with open(metadata_path, "w") as f:
                    metadata["lyrics"] = lyrics
                    metadata["art_prompt"] = art_prompt
                    json.dump(metadata, f, indent=4)

        # Generate Art
        update_status(f"Generating Album Art via Gemini Imagen 3 ({filename})...", 79)
        art_path = os.path.join(output_dir, f"{name_no_ext}_art.png")
        art_url = content_gen.generate_image(art_prompt, art_path)
        if not art_url:
            fallback_art_path = os.path.join(
                output_dir, f"{name_no_ext}_fallback_art.png"
            )
            art_url = generate_fallback_gradient(fallback_art_path)
            if not art_url:
                art_url = "black"

        # Quotes
        if use_quotes:
            lyrics = generate_beat_synced_quotes(
                remake_audio_path
                if os.path.exists(remake_audio_path)
                else base_audio_path,
                target_bpm,
            )

        # Vocals
        vocal_track_path = None

        # Hip-Hop Vocal Remix Integration
        if hiphop_vocal_path:
            update_status(
                "Step 3.5/4: Isolating and Grid-locking Hip-Hop Vocals (Python)...", 82
            )
            try:
                vocal_remixer = VocalRemixer()
                vocal_track_path = os.path.join(
                    output_dir, f"{name_no_ext}_hiphop_vocal.wav"
                )
                # Attempt to determine key from hymn DNA if possible
                root_key = 0  # Default C
                if pre_extracted_metadata and "root_key" in pre_extracted_metadata:
                    root_key = pre_extracted_metadata["root_key"]

                vocal_remixer.process_remix(
                    hiphop_vocal_path,
                    vocal_track_path,
                    target_bpm=target_bpm,
                    target_key_root=root_key,
                )

                if os.path.exists(vocal_track_path):
                    logger.info(f"Isolated hip-hop vocals ready at: {vocal_track_path}")
                else:
                    logger.error("Vocal processing failed.")
            except Exception as e:
                logger.error(f"Hip-hop vocal integration failed: {e}")

        if not vocal_track_path and generate_vocals and tts_generator and lyrics:
            vocal_track_path = os.path.join(output_dir, f"{name_no_ext}_vocals.wav")
            try:
                tts_generator.generate_vocals(
                    lyrics,
                    vocal_track_path,
                    voice_id=voice_id,
                    model=model,
                    status_callback=status_callback,
                )
            except Exception:
                vocal_track_path = None

        if vocal_track_path:
            stems = None
            if stem_separator:
                stem_out_dir = os.path.join(output_dir, f"{name_no_ext}_stems")
                try:
                    stems = stem_separator.separate(remake_audio_path, stem_out_dir)
                except Exception:
                    pass
            process_audio(
                remake_audio_path,
                remake_audio_path,
                normalize=normalize_audio,
                fade_in_ms=fade_in_ms,
                fade_out_ms=fade_out_ms,
                vocal_track_path=vocal_track_path,
                stems=stems,
            )

        # 4. Create Video

        # Automated Quality Check (v1.37.0 Production Gate)
        if quality_evaluator:
            update_status(f"Running automated quality check for {filename}...", 84)
            score = quality_evaluator.evaluate(remake_audio_path)
            if score < 40.0:
                logger.warning(f"QUALITY GATE: {filename} scored low ({score}). Manual review recommended.")
            else:
                logger.info(f"QUALITY GATE: {filename} passed with score {score}.")
        update_status(f"Step 4/4: Creating Video with Subtitles ({filename})...", 85)
        video_path = os.path.join(output_dir, f"{name_no_ext}.mp4")
        final_art_or_video = art_url
        if ai_video_gen:
            if hasattr(content_gen, "generate_video_veo") and not local_video:
                veo_video_path = os.path.join(output_dir, f"{name_no_ext}_veo_bg.mp4")
                generated_bg = content_gen.generate_video_veo(
                    art_prompt, art_url, veo_video_path
                )
                if generated_bg:
                    final_art_or_video = generated_bg
            if final_art_or_video == art_url:
                ai_video_path = os.path.join(output_dir, f"{name_no_ext}_ai_bg.mp4")
                generated_bg = ai_video_gen.generate_video(
                    remake_audio_path,
                    art_url,
                    ai_video_path,
                    prompt=art_prompt,
                    tempo=target_bpm,
                    force_local=local_video,
                    model_type=video_model,
                    model_size=video_model_size,
                    quotes=lyrics,
                )
                if generated_bg:
                    final_art_or_video = generated_bg

        sub_align = 5 if use_quotes else 2
        sub_font = "Georgia" if use_quotes else "Arial"
        video_producer.create_video(
            remake_audio_path,
            final_art_or_video,
            video_path,
            lyrics=lyrics,
            video_format=video_format,
            sub_font_size=sub_font_size,
            sub_primary_color=sub_primary_color,
            sub_outline_color=sub_outline_color,
            sub_back_color=sub_back_color,
            sub_box=sub_box,
            enable_visualizer=enable_visualizer,
            visualizer_mode=visualizer_mode,
            sub_alignment=sub_align,
            sub_font_name=sub_font,
            tempo_bpm=target_bpm,
        )

        if create_shorts:
            video_producer.create_shorts(video_path, output_dir)
        if upload:
            video_id = video_producer.upload_to_youtube(video_path, metadata)
            update_status(f"Video uploaded: https://youtu.be/{video_id}", 100)
        else:
            update_status(f"Finished processing {filename}", 100)

    except Exception as e:
        logger.error(f"Error processing {midi_path}: {e}")
        raise e


if __name__ == "__main__":
    main()
