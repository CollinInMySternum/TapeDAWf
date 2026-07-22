#pragma once

#include <memory>

#include "Common/AudioCommands.h"
#include "GUI/TransportWindow.h"
#include "GUI/LibraryWindow.h"
#include "GUI/ArrangementWindow.h"
#include "Project/Project.h"

namespace Tapedawf {
    class ProjectWindow {
    public:

        ProjectWindow(std::unique_ptr<Project> project, AudioControls& controls) : m_project(std::move(project)), m_controls(controls) {}

        bool render() {
            bool keepProjectOpen = true;

            if (m_firstLayout) {
                m_firstLayout = false;

                // Grab the ID of the dockspace created in App.h
                ImGuiID dockspace_id = ImGui::GetID("DockSpace");

                // Clear existing layout
                ImGui::DockBuilderRemoveNode(dockspace_id);
                ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);
                ImGui::DockBuilderSetNodeSize(dockspace_id, ImGui::GetMainViewport()->Size);

                ImGuiID dock_main_id = dockspace_id;

                ImGuiID dock_top_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Up, 0.05f, nullptr, &dock_main_id);
                ImGuiID dock_left_id = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.20f, nullptr, &dock_main_id);

                ImGui::DockBuilderDockWindow("Transport", dock_top_id);
                ImGui::DockBuilderDockWindow("Library", dock_left_id);
                ImGui::DockBuilderDockWindow("Arrangement", dock_main_id);

                ImGuiDockNode* topNode = ImGui::DockBuilderGetNode(dock_top_id);
                if (topNode) {
                    topNode->LocalFlags |= ImGuiDockNodeFlags_NoTabBar | ImGuiDockNodeFlags_NoDockingOverMe;
                }

                ImGui::DockBuilderFinish(dockspace_id);
            }

            // Menu
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

            // Render windows
            TransportWindow::Render(m_controls, *m_project);
            m_libraryWindow.render(*m_project);
            m_trackWindow.render(*m_project);

            return keepProjectOpen;
        }

    private:
        std::unique_ptr<Project> m_project;
        AudioControls& m_controls;

        TransportWindow m_transportWindow;
        LibraryWindow m_libraryWindow;
        ArrangementWindow m_trackWindow;

        bool m_firstLayout = true;
    };
}