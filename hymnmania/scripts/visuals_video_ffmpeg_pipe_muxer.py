import os
import sys
import ctypes
import subprocess
import pyglet
from pyglet.gl import GL_RGBA, GL_UNSIGNED_BYTE, glReadPixels

ROOT = os.path.dirname(os.path.abspath(__file__))
FFMPEG = os.path.join(ROOT, "..", "hymn_remaker", "bin", "ffmpeg.exe")
if not os.path.exists(FFMPEG):
    FFMPEG = "ffmpeg"

def mux_frames_to_video(pcm_data, audio_path, output_path, duration, width=640, height=360, fps=30):
    from visuals_milkdrop_preset_energy_analysis_transition_renderer import DLL, load_presets, precompute_rms_transitions
    
    spf = 44100 // fps
    total = len(pcm_data) // 4
    nframes = (total // spf) // 2
    pcm_buf = ctypes.create_string_buffer(pcm_data)

    transition_times = precompute_rms_transitions(pcm_data, nframes, spf, fps)
    presets = load_presets()

    try:
        pyglet.options["shadow_window"] = False
    except:
        pass
    config = pyglet.gl.Config(double_buffer=True, depth_size=24)
    win = pyglet.window.Window(width=width, height=height, config=config, visible=False)
    win.switch_to()

    handle = DLL.projectm_create()
    if not handle:
        return False
    
    DLL.projectm_set_window_size(handle, width, height)
    DLL.projectm_set_mesh_size(handle, 48, 36)
    DLL.projectm_set_fps(handle, fps)

    if presets:
        DLL.projectm_load_preset_file(handle, presets[0].encode(), True)

    cf = subprocess.CREATE_NO_WINDOW if hasattr(subprocess, "CREATE_NO_WINDOW") else 0
    ff = subprocess.Popen([
        FFMPEG, "-y", "-f", "rawvideo", "-pix_fmt", "rgba", "-s", f"{width}x{height}", "-r", str(fps), "-i", "-",
        "-i", audio_path, "-c:v", "libx264", "-preset", "medium", "-crf", "23", "-c:a", "aac", "-b:a", "192k",
        "-pix_fmt", "yuv420p", "-shortest", output_path
    ], stdin=subprocess.PIPE, creationflags=cf)

    frame_size = width * height * 4
    fb = (ctypes.c_ubyte * frame_size)()
    t_idx = 0
    p_idx = 0

    for fi in range(min(nframes, duration * fps)):
        off = fi * spf * 2
        if off + spf * 2 > total:
            break

        elapsed = fi / fps
        if t_idx < len(transition_times) and elapsed >= transition_times[t_idx]:
            p_idx = (p_idx + 1) % len(presets)
            DLL.projectm_load_preset_file(handle, presets[p_idx].encode(), True)
            t_idx += 1

        boff = off * 4
        fp = ctypes.cast(
            ctypes.addressof(pcm_buf) + boff,
            ctypes.POINTER(ctypes.c_float)
        )
        DLL.projectm_pcm_add_float(handle, fp, spf, 2)
        DLL.projectm_opengl_render_frame(handle)
        glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, fb)

        # Flip vertically
        flipped = (ctypes.c_ubyte * frame_size)()
        for y in range(height):
            s = y * width * 4
            d = (height - 1 - y) * width * 4
            flipped[d : d + width * 4] = fb[s : s + width * 4]
        ff.stdin.write(bytes(flipped))

    ff.stdin.close()
    ff.wait()
    DLL.projectm_destroy(handle)
    win.close()
    return os.path.exists(output_path)

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument("--audio", required=True)
    parser.add_argument("--video", required=True)
    parser.add_argument("--duration", type=int, default=120)
    args = parser.parse_args()

    # Decode PCM first
    pcm_file = args.audio.replace(".mp3", ".pcm")
    cf = subprocess.CREATE_NO_WINDOW if hasattr(subprocess, "CREATE_NO_WINDOW") else 0
    subprocess.run([
        FFMPEG, "-y", "-i", args.audio, "-f", "f32le", "-acodec", "pcm_f32le", "-ar", "44100", "-ac", "2", pcm_file
    ], capture_output=True, creationflags=cf)

    with open(pcm_file, "rb") as f:
        pcm_data = f.read()
    if os.path.exists(pcm_file):
        os.remove(pcm_file)

    success = mux_frames_to_video(pcm_data, args.audio, args.video, args.duration)
    sys.exit(0 if success else 1)
