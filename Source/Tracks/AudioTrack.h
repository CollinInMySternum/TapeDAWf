#pragma once

#include <readerwriterqueue.h>
#include <vector>

#include "Clips/AudioClip.h"
#include "Tracks/Track.h"

namespace Tapedawf {
    class AudioTrack : public ITrack {
    public:
        AudioTrack() { name = "Audio Track"; }

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

    inline bool spliceAudioClip(AudioTrack& track, size_t clipIndex, double splitTime) {
        auto& clips = const_cast<std::vector<AudioClip>&>(track.getClips());
        if (clipIndex >= clips.size()) return false;

        AudioClip original = clips[clipIndex];

        // Ensure split point falls inside the clip boundary
        if (splitTime <= original.timelineStart || splitTime >= original.timelineStart + original.duration) {
            return false;
        }

        double leftDuration = splitTime - original.timelineStart;
        double rightDuration = original.duration - leftDuration;

        // Clip 1 (Left Part)
        AudioClip leftClip = original;
        leftClip.duration = leftDuration;

        // Clip 2 (Right Part)
        AudioClip rightClip = original;
        rightClip.name = original.name + " (Split)";
        rightClip.timelineStart = splitTime;
        rightClip.sourceOffset = original.sourceOffset + leftDuration;
        rightClip.duration = rightDuration;

        // Replace original clip with left clip, insert right clip directly after
        clips[clipIndex] = leftClip;
        clips.insert(clips.begin() + clipIndex + 1, rightClip);

        return true;
    }
}