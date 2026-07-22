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

        }

        std::vector<ProjectEntry> getProjects() const {
            std::vector<ProjectEntry> projects;
            std::error_code ec;

            if (!std::filesystem::exists(m_projectsRoot, ec)) return projects;

            auto it = std::filesystem::recursive_directory_iterator(m_projectsRoot, ec);
            if (ec) {
                return projects;
            }

            for (const auto& entry : it) {
                if (entry.is_regular_file() && entry.path().extension() == ".json") {
                    auto path = entry.path();
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
            }

            return projects;
        }

        std::unique_ptr<Project> createNewProject(const std::string& name, const std::filesystem::path& customDirectory = "") {
            std::filesystem::path targetDir = customDirectory.empty() ? (m_projectsRoot / name) : customDirectory;

            std::error_code ec;
            std::filesystem::create_directories(targetDir, ec);

            auto proj = std::make_unique<Project>();
            proj->name = name;
            proj->filePath = targetDir / (name + ".json");

            proj->saveToDisk();
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

           return Project::fromJson(j, path);
        }

        const std::filesystem::path& getProjectsRoot() const {
            return m_projectsRoot;
        }

    private:
        std::filesystem::path m_projectsRoot = R"(C:\TapedawfProjects)";

        std::filesystem::file_time_type getFileCreationTime(const std::filesystem::path& path) const {
            std::error_code ec;
            auto ftime = std::filesystem::last_write_time(path, ec);

            return ftime;
        }
    };
}