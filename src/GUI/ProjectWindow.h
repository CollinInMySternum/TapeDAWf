#pragma once

#include <memory>

#include "Common/AudioCommands.h"
#include "GUI/TransportWindow.h"
#include "GUI/LibraryWindow.h"
#include "GUI/TrackWindow.h"
#include "Project/Project.h"

namespace Tapedawf {
    class ProjectWindow {
    public:

        ProjectWindow(std::unique_ptr<Project> project, AudioControls& controls) : m_project(std::move(project)), m_controls(controls) {}

        bool render() {
            bool keepProjectOpen = true;

            if (ImGui::BeginMainMenuBar()) {
                if (ImGui::BeginMenu("File")) {
                    if (ImGui::MenuItem("Save Project", "Ctrl+S")) {
                        m_project->saveToDisk();
                    }
                    if (ImGui::MenuItem("Close Project")) {
                        keepProjectOpen = false;
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

            TransportWindow::Render(m_controls, *m_project);
            m_libraryWindow.render(*m_project);
            m_trackWindow.render(*m_project);

            return keepProjectOpen;
        }

    private:
        std::unique_ptr<Project> m_project;
        AudioControls& m_controls;

        LibraryWindow m_transportWindow;
        LibraryWindow m_libraryWindow;
        TrackWindow m_trackWindow;
    };
}