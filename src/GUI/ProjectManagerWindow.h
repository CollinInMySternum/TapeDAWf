#pragma once

#include <imgui.h>
#include <memory>

#include "Project/ProjectManager.h"
#include "Common/Log.h"

namespace Tapedawf {
    class ProjectManagerWindow {
    public:

        std::unique_ptr<Project> render(ProjectManager& manager) {

            // LAZY INITIALIZATION OF DEFAULT VALUES ( I know, it's stupid )
            if (!m_initialized) {
                std::strncpy(m_newName, "New Project", sizeof(m_newName) - 1);
                m_newName[sizeof(m_newName) - 1] = '\0';

                std::string rootStr = manager.getProjectsRoot().string();
                std::strncpy(m_newPath, rootStr.c_str(), sizeof(m_newPath) - 1);
                m_newPath[sizeof(m_newPath) - 1] = '\0';

                m_initialized = true; // Locks initialization out of future frames
            }

            std::unique_ptr<Project> loadedProject = nullptr;

            ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);

            ImGui::Begin("Welcome to Tapedawf!", nullptr, ImGuiWindowFlags_NoCollapse);

            // Left Side: Recent projects
            ImGui::BeginChild("Projects", ImVec2(250, 0), true);
            ImGui::Text("Projects");
            ImGui::Separator();

            for (const auto& entry : manager.getProjects()) {
                if (ImGui::Selectable(entry.name.c_str())) {
                    LOG("ProjectManager", "User selected project to load: '{}' at path: '{}'", entry.name, entry.path.string());
                    loadedProject = manager.loadProject(entry.path);
                    if (!loadedProject) {
                        LOG("ProjectManager", "ERROR: Failed to load project from path: '{}'", entry.path.string());
                    }
                }
                if (ImGui::IsItemHovered()) {
                    ImGui::SetTooltip("%s", entry.path.string().c_str());
                }
            }
            ImGui::EndChild();

            ImGui::SameLine();

            // Right side: Create New
            ImGui::BeginChild("NewProject", ImVec2(0, 0), true);
            ImGui::Text("Create New Project");
            ImGui::Separator();

            ImGui::InputText("Name", m_newName, IM_ARRAYSIZE(m_newName));
            ImGui::InputText("Path", m_newPath, IM_ARRAYSIZE(m_newPath));

            if (ImGui::Button("Create", ImVec2(120, 30))) {
                std::filesystem::path dir(m_newPath);
                dir /= m_newName;

                LOG("ProjectManager", "Attempting to create new project '{}' at directory: '{}'", m_newName, dir.string());

                loadedProject = manager.createNewProject(m_newName, dir);
                if (loadedProject) {
                    LOG("ProjectManager", "Successfully created new project: '{}'", m_newName);
                } else {
                    LOG("ProjectManager", "ERROR: Failed to create project '{}'", m_newName);
                }
            }
            ImGui::EndChild();

            ImGui::End();

            return loadedProject;
        }
    private:
        bool m_initialized = false;
        char m_newName[128] = "";
        char m_newPath[512] = "";
    };
}