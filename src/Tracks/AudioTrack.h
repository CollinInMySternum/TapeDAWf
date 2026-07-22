#pragma once

#include <readerwriterqueue.h>
#include <vector>

#include "Clips/AudioClip.h"
#include "Tracks/Track.h"

namespace Tapedawf {
    class AudioTrack : public ITrack {
    public:
        AudioTrack() {
            name = "Audio Track";
        }

        TrackType getType() const override { return TrackType::Audio; }

        void processAudio(float *outBuffer, int numFrames) override {
            // Audio thread logic
        }

        void addClip(const AudioClip& clip) {
            clips.push_back(clip);
        }

        const std::vector<AudioClip>& getClips() const {
            return clips;
        }

    private:
        moodycamel::ReaderWriterQueue<float> sampleQueue;
        std::vector<AudioClip> clips;
    };
}