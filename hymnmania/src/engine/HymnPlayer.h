#ifndef HYMNPLAYER_H
#define HYMNPLAYER_H

#include <string>
#include <fluidsynth.h>

class HymnPlayer {
public:
    HymnPlayer(const std::string& soundfontPath = "/usr/share/sounds/sf2/FluidR3_GM.sf2");
    ~HymnPlayer();

    bool load(const std::string& filename);
    void play();
    void pause();
    void stop();

    bool isPlaying() const;
    void renderAudio(float* buffer, int numFrames);

    // Mixer methods
    void set_gain(float gain);
    void set_channel_volume(int channel, float volume);

    // Real-time Event methods
    void send_cc(int channel, int control, int value);
    void send_note_on(int channel, int key, int velocity);
    void send_note_off(int channel, int key);

    // Real-time methods
    void start_realtime();
    void stop_realtime();

private:
    bool playing;
    std::string currentFile;

    // FluidSynth components
    fluid_settings_t* settings;
    fluid_synth_t* synth;
    fluid_player_t* player;
    fluid_audio_driver_t* adriver;

    int soundfontId;
};

#endif // HYMNPLAYER_H
