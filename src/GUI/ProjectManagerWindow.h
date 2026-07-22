#pragma once

#include <imgui.h>
#include <memory>

#include "Project/ProjectManager.h"

namespace Tapedawf {
    class ProjectManagerWindow {
    public:
        std::unique_ptr<Project> render(ProjectManager& manager) {
            std::unique_ptr<Project> loadedProject = nullptr;

            ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(), ImGuiCond_Always, ImVec2(0.5f, 0.5f));
            ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);

            ImGui::Begin("Welcome to Tapedawf!", nullptr, ImGuiWindowFlags_NoCollapse);

            // Left Side: Recent projects
            ImGui::BeginChild("RecentProjects", ImVec2(250, 0), true);
            ImGui::Text("Recent Projects");
            ImGui::Separator();

            for (const auto& entry : manager.getProjects()) {
                if (ImGui::Selectable(entry.name.c_str())) {
                    loadedProject = manager.loadProject(entry.path);
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

            std::strncpy(m_newName, "New Project", sizeof(m_newName) - 1);
            m_newName[sizeof(m_newName) - 1] = '\0'; // Guarantee null-termination

            std::strncpy(m_newPath, manager.getProjectsRoot().string().c_str(), sizeof(m_newPath) - 1);
            m_newPath[sizeof(m_newPath) - 1] = '\0'; // Guarantee null-termination

            ImGui::InputText("Name", m_newName, IM_ARRAYSIZE(m_newName));
            ImGui::InputText("Path", m_newPath, IM_ARRAYSIZE(m_newPath));

            if (ImGui::Button("Create", ImVec2(120, 30))) {
                std::filesystem::path dir(m_newPath);
                dir /= m_newName;
                loadedProject = manager.createNewProject(m_newName, dir);
            }
            ImGui::EndChild();

            ImGui::End();

            return loadedProject;
        }
    private:
        char m_newName[128] = "";
        char m_newPath[512] = "";
    };
}