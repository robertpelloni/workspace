#include <iostream>
#include <fstream>
#include "src/engine/HymnPlayer.h"

// Simple test framework
#define ASSERT_TRUE(condition) \
    if (!(condition)) { \
        std::cerr << "Assertion failed: " << #condition << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        return 1; \
    }

#define ASSERT_FALSE(condition) \
    if (condition) { \
        std::cerr << "Assertion failed: " << #condition << " at " << __FILE__ << ":" << __LINE__ << std::endl; \
        return 1; \
    }

// Create a valid dummy MIDI file
bool createDummyMidi(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) return false;

    // Minimal valid MIDI file header
    const unsigned char midiData[] = {
        'M', 'T', 'h', 'd',  // Header chunk type
        0, 0, 0, 6,          // Chunk length
        0, 0,                // Format 0
        0, 1,                // 1 track
        0, 96,               // 96 ticks per quarter note

        'M', 'T', 'r', 'k',  // Track chunk type
        0, 0, 0, 4,          // Chunk length
        0, 0xFF, 0x2F, 0     // End of track meta event
    };

    file.write(reinterpret_cast<const char*>(midiData), sizeof(midiData));
    return true;
}

int main() {
    HymnPlayer player;

    // Initial state
    ASSERT_FALSE(player.isPlaying());

    // Create dummy MIDI file
    ASSERT_TRUE(createDummyMidi("dummy.mid"));

    // Load file
    ASSERT_TRUE(player.load("dummy.mid"));

    // Play
    player.play();
    ASSERT_TRUE(player.isPlaying());

    // Render some audio
    float buffer[1024];
    player.renderAudio(buffer, 512); // Should not crash

    // Pause
    player.pause();
    ASSERT_FALSE(player.isPlaying());

    // Render silence while paused
    player.renderAudio(buffer, 512);
    for (int i = 0; i < 1024; ++i) {
        ASSERT_TRUE(buffer[i] == 0.0f);
    }

    // Stop
    player.stop();
    ASSERT_FALSE(player.isPlaying());

    // Cleanup
    std::remove("dummy.mid");

    std::cout << "All HymnPlayer tests passed successfully." << std::endl;
    return 0;
}
