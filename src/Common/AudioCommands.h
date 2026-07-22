#pragma once

#include <atomic>
#include <variant>
#include <cstdint>
#include <readerwriterqueue.h>

namespace Tapedawf {
    struct PlayCommand { uint32_t startSample{0}; };
    struct StopCommand {};
    struct AddNodeCommand { uint32_t nodeId{0}; int nodeType{0}; };

    using AudioCommand = std::variant<PlayCommand, StopCommand, AddNodeCommand>;

    struct AudioControls {
        std::atomic<float> masterGain{1.0f};
        std::atomic<float> track1Pan{0.0f};

        moodycamel::ReaderWriterQueue<AudioCommand> commandQueue{1024};
    };
}