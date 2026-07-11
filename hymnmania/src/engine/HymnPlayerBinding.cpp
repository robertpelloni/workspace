#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "HymnPlayer.h"

namespace py = pybind11;

// Wrapper function to handle numpy arrays seamlessly
py::array_t<float> renderAudioWrapper(HymnPlayer& player, int numFrames) {
    // We expect stereo interleaved, so 2 channels
    auto result = py::array_t<float>(numFrames * 2);

    // Get mutable pointer to the data
    py::buffer_info buf = result.request();
    float* ptr = static_cast<float*>(buf.ptr);

    // Call the original renderAudio function
    player.renderAudio(ptr, numFrames);

    return result;
}

PYBIND11_MODULE(hymn_player_ext, m) {
    m.doc() = "Python bindings for the native HymnPlayer C++ audio engine using FluidSynth";

    py::class_<HymnPlayer>(m, "HymnPlayer")
        .def(py::init<const std::string&>(), py::arg("soundfontPath") = "/usr/share/sounds/sf2/FluidR3_GM.sf2")
        .def("load", &HymnPlayer::load, "Load a MIDI file into the player", py::arg("filename"))
        .def("play", &HymnPlayer::play, "Start playback of the loaded MIDI file")
        .def("pause", &HymnPlayer::pause, "Pause playback")
        .def("stop", &HymnPlayer::stop, "Stop playback")
        .def("is_playing", &HymnPlayer::isPlaying, "Check if the player is currently playing")
        .def("set_gain", &HymnPlayer::set_gain, "Set global synthesizer gain (0.0 to 10.0)", py::arg("gain"))
        .def("set_channel_volume", &HymnPlayer::set_channel_volume, "Set volume for a specific MIDI channel (0.0 to 1.0)", py::arg("channel"), py::arg("volume"))
        .def("send_cc", &HymnPlayer::send_cc, "Send MIDI CC event", py::arg("channel"), py::arg("control"), py::arg("value"))
        .def("send_note_on", &HymnPlayer::send_note_on, "Send MIDI note on event", py::arg("channel"), py::arg("key"), py::arg("velocity"))
        .def("send_note_off", &HymnPlayer::send_note_off, "Send MIDI note off event", py::arg("channel"), py::arg("key"))
        .def("start_realtime", &HymnPlayer::start_realtime, "Start real-time audio output")
        .def("stop_realtime", &HymnPlayer::stop_realtime, "Stop real-time audio output")
        .def("render_audio", &renderAudioWrapper, "Render audio into a numpy array of floats (stereo interleaved)", py::arg("numFrames"));
}
