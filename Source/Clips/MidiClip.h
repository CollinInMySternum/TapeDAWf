#pragma once

#include <filesystem>
#include <string>

namespace Tapedawf {
    struct MidiNote {
        int noteNumber = 60;
        double start = 0.0;
        double duration = 1.0;
        float velocity = 0.8f;
    };

    struct MidiClip {
        std::string name = "MIDI Sequence";
        double timelineStart = 0.0;
        double duration = 4.0;
        std::vector<MidiNote> notes;
    };
}