#pragma once

#include <imgui.h>
#include <memory>
#include <portable-file-dialogs.h>

#include "Project/ProjectManager.h"
#include "Common/Logging.h"

namespace Tapedawf {
    class ProjectManagerWindow {
    public:

        std::unique_ptr<Project> render(ProjectManager& manager) {

            // LAZY INITIALIZATION OF DEFAULT VALUES ( I know, it's stupid )
            if (!m_initialized) {
                std::strncpy(m_newName, "New Project", sizeof(m_newName) - 1);
                m_newName[sizeof(m_newName) - 1] = '\0';

                std::string defaultPath = (std::filesystem::current_path() / "Projects").string();
                std::strncpy(m_newPath, defaultPath.c_str(), sizeof(m_newPath) - 1);
                m_newPath[sizeof(m_newPath) - 1] = '\0';

                m_initialized = true;
            }

            std::unique_ptr<Project> loadedProject = nullptr;

            ImGuiViewport* viewport = ImGui::GetMainViewport();

            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);

            ImGuiWindowFlags windowFlags =
                ImGuiWindowFlags_NoCollapse |
                ImGuiWindowFlags_NoResize |
                ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoDocking;

            ImGui::Begin("Welcome to TapeDAWf!", nullptr, windowFlags);

            // Left Side: Recent projects
            ImGui::BeginChild("Projects", ImVec2(250, 0), true);
            ImGui::Text("Projects");
            ImGui::Separator();

            ImGui::BeginChild("ProjectList", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()), false, ImGuiWindowFlags_HorizontalScrollbar);
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

            if (ImGui::Button("Open Other...", ImVec2(-1, 0))) {
                auto selection = pfd::open_file("Select Project File", "", {"Tapedawf Projects", "*.json"}).result();
                if (!selection.empty()) {
                    loadedProject = manager.loadProject(selection[0]);
                }
            }

            ImGui::EndChild();
            ImGui::SameLine();

            // Right side: Create new

            ImGui::BeginChild("NewProject", ImVec2(0, 0), true);
            ImGui::Text("Create New Project");
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::InputText("Name", m_newName, IM_ARRAYSIZE(m_newName));

            // Set up a table or straightforward layout for input + browse button
            ImGui::InputText("Location", m_newPath, IM_ARRAYSIZE(m_newPath));
            ImGui::SameLine();
            if (ImGui::Button("Browse...")) {
                auto selection = pfd::select_folder("Select Project Location").result();
                if (!selection.empty()) {
                    std::strncpy(m_newPath, selection.c_str(), sizeof(m_newPath) - 1);
                    m_newPath[sizeof(m_newPath) - 1] = '\0';
                }
            }

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (ImGui::Button("Create", ImVec2(120, 30))) {
                std::filesystem::path dir(m_newPath);

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