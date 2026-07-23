#pragma once

#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>

#include "Project/Project.h"

namespace Tapedawf {
    struct ProjectEntry {
        std::string name;
        std::filesystem::path path;
        std::filesystem::file_time_type modifiedTime;
        std::filesystem::file_time_type createdTime;
    };

    class ProjectManager {
    public:
        ProjectManager() {
            loadManifest();
        }

        std::vector<ProjectEntry> getProjects() const {
            std::vector<ProjectEntry> projects;
            std::error_code ec;

            for (const auto& pathStr : m_recentPaths) {
                std::filesystem::path path(pathStr);

                if (!std::filesystem::exists(path, ec)) continue;

                auto ftime = std::filesystem::last_write_time(path, ec);
                if (ec) ftime = std::filesystem::file_time_type::min();

                std::string projName = path.stem().string();

                std::ifstream file(path);
                if (file.is_open()) {
                    nlohmann::json j;

                    try {
                        file >> j;

                        if (j.contains("name") && j["name"].is_string()) {
                            projName = j["name"].get<std::string>();
                        }
                    } catch (...) {}
                }

                projects.push_back({projName, path, ftime, getFileCreationTime(path)});
            }

            std::sort(projects.begin(), projects.end(), [](const ProjectEntry& a, const ProjectEntry& b) {
                return a.modifiedTime > b.modifiedTime;
            });

            return projects;
        }

        std::unique_ptr<Project> createNewProject(const std::string& name, const std::filesystem::path& customDirectory = "") {
            std::filesystem::path targetDir = customDirectory / name;

            std::error_code ec;
            std::filesystem::create_directories(targetDir, ec);

            auto proj = std::make_unique<Project>();
            proj->name = name;
            proj->filePath = targetDir / (name + ".json");

            proj->saveToDisk();

            addToManifest(proj->filePath);

            return proj;
        }

        std::unique_ptr<Project> loadProject(const std::filesystem::path& path) {
            std::ifstream file(path);
            if (!file.is_open()) return nullptr;

            nlohmann::json j;
            try {
                file >> j;
            } catch (...) {
                return nullptr;
            }

            addToManifest(path);

            return Project::fromJson(j, path);
        }

    private:
        std::filesystem::path m_manifestPath = "tapedawf_manifest.json";
        std::vector<std::string> m_recentPaths;

        std::filesystem::file_time_type getFileCreationTime(const std::filesystem::path& path) const {
            std::error_code ec;
            return std::filesystem::last_write_time(path, ec);;
        }

        void loadManifest() {
            std::ifstream file(m_manifestPath);

            if (file.is_open()) {
                nlohmann::json j;
                try {
                    file >> j;
                    if (j.contains("recent_projects") && j["recent_projects"].is_array()) {
                        for (const auto& p : j["recent_projects"]) {
                            m_recentPaths.push_back(p.get<std::string>());
                        }
                    }
                } catch (...) {}
            }
        }

        void saveManifest() const {
            nlohmann::json j;

            j["recent_projects"] = m_recentPaths;

            std::ofstream file(m_manifestPath);
            if (file.is_open()) {
                file << j.dump(4);
            }
        }

        void addToManifest(const std::filesystem::path& path) {
            std::string pathStr = path.string();

            // Remove it if it already exists so we don't get duplicates
            auto it = std::find(m_recentPaths.begin(), m_recentPaths.end(), pathStr);
            if (it != m_recentPaths.end()) {
                m_recentPaths.erase(it);
            }

            // Insert at the front
            m_recentPaths.insert(m_recentPaths.begin(), pathStr);
            saveManifest();
        }
    };
}