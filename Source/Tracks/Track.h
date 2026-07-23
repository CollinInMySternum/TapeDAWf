#pragma once

#include <string>
#include <atomic>

namespace Tapedawf {
    enum class TrackType { Audio, Midi };

    class ITrack {
    public:
        virtual ~ITrack() = default;

        virtual void processAudio(float* outBuffer, int numFrames) = 0;
        virtual TrackType getType() const = 0;

        std::string name = "Track";

        std::atomic<float> volume{1.0f};
        std::atomic<float> pan{1.0f};
        std::atomic<bool> isMuted{false};
        std::atomic<bool> isSoloed{false};
        std::atomic<bool> isArmed{false};
    };
}