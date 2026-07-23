#pragma once

#include <filesystem>
#include <string>

namespace Tapedawf {
    struct AudioClip {
        std::string name;
        std::filesystem::path filePath;

        double timelineStart = 0.0;
        double sourceOffset = 0.0;
        double duration = 0.0;
    };
}