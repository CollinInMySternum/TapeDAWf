#pragma once

#include <readerwriterqueue.h>
#include <vector>

#include "Clips/MidiClip.h"
#include "Tracks/Track.h"

namespace Tapedawf {
    class MidiTrack : public ITrack {
    public:
        MidiTrack() { name = "MIDI Track"; }

        TrackType getType() const override { return TrackType::Midi; }

        void processAudio(float *outBuffer, int numFrames) override {
            // Audio thread logic
        }

        void addClip(const MidiClip& clip) { clips.push_back(clip); }
        std::vector<MidiClip>& getClips() { return clips; }
        const std::vector<MidiClip>& getClips() const { return clips; }

    private:
        std::vector<MidiClip> clips;
    };
}