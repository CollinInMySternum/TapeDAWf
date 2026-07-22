#pragma once

#include <vector>
#include <memory>
#include <string>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Tracks/AudioTrack.h"
#include "Tracks/MidiTrack.h"
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

        std::shared_ptr<ITrack> addTrack(TrackType type, const std::string& trackName = "") {
            std::shared_ptr<ITrack> newTrack;

            if (type == TrackType::Audio) {
                auto track = std::make_shared<AudioTrack>();
                track->name = trackName.empty() ? "Audio " + std::to_string(tracks.size() + 1) : trackName;
                newTrack = track;
            } else {
                auto track = std::make_shared<MidiTrack>();
                track->name = trackName.empty() ? "MIDI " + std::to_string(tracks.size() + 1) : trackName;
                newTrack = track;
            }

            tracks.push_back(newTrack);
            return newTrack;
        }

        void removeTrack(size_t index) {
            if (index < tracks.size()) {
                tracks.erase(tracks.begin() + index);
            }
        }

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
            for (const auto& track : tracks) {
                json tj;
                tj["name"] = track->name;
                tj["type"] = static_cast<int>(track->getType());
                tj["volume"] = track->volume.load();
                tj["pan"] = track->pan.load();
                tj["isMuted"] = track->isMuted.load();

                if (track->getType() == TrackType::Audio) {
                    auto audioTrack = std::static_pointer_cast<AudioTrack>(track);

                    json clipsJson = json::array();
                    for (const auto& clip : audioTrack->getClips()) {
                        clipsJson.push_back({
                            {"name", clip.name},
                            {"filePath", clip.filePath.string()},
                            {"timelineStart", clip.timelineStart},
                            {"sourceOffset", clip.sourceOffset},
                            {"duration", clip.duration}
                        });
                    }
                    tj["clips"] = clipsJson;
                }
                j["tracks"].push_back(tj);
            }

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

            if (j.contains("tracks")) {
                for (const auto& tj : j["tracks"]) {
                    TrackType type = static_cast<TrackType>(tj.value("type", 0));

                    auto track = proj->addTrack(type, tj.value("name", "Track"));

                    track->volume.store(tj.value("volume", 1.0f));
                    track->pan.store(tj.value("pan", 0.0f));
                    track->isMuted.store(tj.value("isMuted", false));

                    if (type == TrackType::Audio && tj.contains("clips")) {
                        auto audioTrack = std::static_pointer_cast<AudioTrack>(track);

                        for (const auto& cj : tj["clips"]) {
                            AudioClip clip;

                            clip.name = cj.value("name", "Clip");
                            clip.filePath = cj.value("filePath", "");
                            clip.timelineStart = cj.value("timelineStart", 0.0);
                            clip.sourceOffset = cj.value("sourceOffset", 0.0);
                            clip.duration = cj.value("duration", 0.0);

                            audioTrack->addClip(clip);
                        }
                    }
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