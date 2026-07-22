#pragma once

#include <vector>
#include <memory>
#include <string>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Tracks/Track.h"

using json = nlohmann::json;

namespace Tapedawf {
    class Project {
    public:
        Project(std::string projectName = "Untitled Project") : name(std::move(projectName)) {}

        std::string name;
        std::filesystem::path filePath;

        std::vector<std::filesystem::path> libraryDirectories;
        std::vector<std::shared_ptr<ITrack>> tracks;

        double bpm = 120.0;
        int timeSignatureTop = 4;
        int timeSignatureBottom = 4;

        json toJson() const {
            json j;
            j["name"] = name;
            j["bpm"] = bpm;
            j["timeSignatureTop"] = timeSignatureTop;
            j["timeSignatureBottom"] = timeSignatureBottom;

            j["libraryDirectories"] = json::array();
            for (const auto& dir : libraryDirectories) {
                j["libraryDirectories"].push_back(dir.string());
            }

            j["tracks"] = json::array();
            return j;
        }

        static std::unique_ptr<Project> fromJson(const json& j, const std::filesystem::path& loadPath) {
            auto proj = std::make_unique<Project>();

            proj->filePath = loadPath;
            proj->name = j.value("name", "Untitled");
            proj->bpm = j.value("bpm", 120.0);
            proj->timeSignatureTop = j.value("timeSignatureTop", 4);
            proj->timeSignatureBottom = j.value("timeSignatureBottom", 4);

            if (j.contains("libraryDirectories")) {
                for (const auto& dir : j["libraryDirectories"]) {
                    proj->libraryDirectories.push_back(dir.get<std::string>());
                }
            }

            return proj;
        }

        bool saveToDisk() const {
            std::ofstream file(filePath);
            if (!file.is_open()) return false;
            file << toJson().dump(4);
            return true;
        }
    };
}