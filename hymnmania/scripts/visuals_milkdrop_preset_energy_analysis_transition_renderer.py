import os
import sys
import ctypes
import glob
import numpy as np

sys.stdout.reconfigure(encoding="utf-8", errors="replace")

ROOT = os.path.dirname(os.path.abspath(__file__))
PM_DIR = os.path.join(ROOT, "..", "projectm_bin", "lib")
os.environ["PATH"] = os.path.abspath(PM_DIR) + ";" + os.environ["PATH"]

DLL = ctypes.CDLL(os.path.join(PM_DIR, "projectM-4.dll"))
DLL.projectm_create.restype = ctypes.c_void_p
DLL.projectm_create.argtypes = []
DLL.projectm_destroy.argtypes = [ctypes.c_void_p]
DLL.projectm_pcm_add_float.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_float), ctypes.c_uint, ctypes.c_uint]
DLL.projectm_set_window_size.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.c_size_t]
DLL.projectm_set_mesh_size.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.c_size_t]
DLL.projectm_set_fps.argtypes = [ctypes.c_void_p, ctypes.c_int]
DLL.projectm_get_version_string.restype = ctypes.c_char_p
DLL.projectm_load_preset_file.argtypes = [ctypes.c_void_p, ctypes.c_char_p, ctypes.c_bool]
DLL.projectm_opengl_render_frame.argtypes = [ctypes.c_void_p]

def load_presets():
    d = os.path.join(ROOT, "..", "projectm_bin", "presets")
    return sorted(glob.glob(os.path.join(d, "*.milk")))

def precompute_rms_transitions(pcm_data, nframes, spf, fps):
    rms_per_frame = np.zeros(nframes, dtype=np.float32)
    floats_view = np.frombuffer(pcm_data, dtype=np.float32)
    for fi in range(nframes):
        off = fi * spf * 2
        chunk = floats_view[off : off + spf * 2]
        rms_per_frame[fi] = float(np.sqrt(np.mean(chunk**2))) if len(chunk) > 0 else 0.0

    win = max(1, int(fps * 0.5))
    kernel = np.ones(win) / win
    rms_smooth = np.convolve(rms_per_frame, kernel, mode="same")

    baseline_win = fps * 5
    baseline = np.zeros_like(rms_smooth)
    for fi in range(nframes):
        lo = max(0, fi - baseline_win)
        hi = min(nframes, fi + baseline_win // 2)
        baseline[fi] = float(np.mean(rms_smooth[lo:hi]))

    min_cooldown = int(fps * 8)
    first_transition_delay = int(fps * 4)
    transitions = []
    last_t = -min_cooldown
    for fi in range(first_transition_delay, nframes):
        if fi - last_t < min_cooldown:
            continue
        b = baseline[fi]
        if b < 0.001:
            continue
        ratio = rms_smooth[fi] / b
        if ratio > 1.5 or ratio < 0.4:
            transitions.append(fi)
            last_t = fi
    return [t / fps for t in transitions]
