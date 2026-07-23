#pragma once

#include <imgui.h>
#include <filesystem>
#include <vector>
#include <string>
#include <algorithm>

#include "portable-file-dialogs.h"
#include "Project/Project.h"

namespace Tapedawf {
    class LibraryWindow {
    public:
        LibraryWindow() = default;

        void render(Project& project) {
            ImGui::Begin("Library");

            if (!project.libraryDirectories.empty() && (m_selectedPath.empty() || std::find(project.libraryDirectories.begin(), project.libraryDirectories.end(), m_selectedPath) == project.libraryDirectories.end())) {
                m_selectedPath = project.libraryDirectories[0];
            } else if (project.libraryDirectories.empty()) {
                m_selectedPath.clear();
            }

            if (ImGui::BeginTable("LibrarySplitView", 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable, ImVec2(0, 0))) {
                ImGui::TableSetupColumn("Folders", ImGuiTableColumnFlags_WidthFixed, 180.0f);
                ImGui::TableSetupColumn("Contents", ImGuiTableColumnFlags_WidthStretch);

                ImGui::TableNextRow();

                // Left column
                ImGui::TableSetColumnIndex(0);
                ImGui::BeginChild("LeftFolderList", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

                ImGui::TextDisabled("Root Directories");

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                for (size_t i = 0; i < project.libraryDirectories.size(); ++i) {
                    const auto& path = project.libraryDirectories[i];

                    std::string displayName = path.filename().string();
                    if (displayName.empty()) displayName = path.string();

                    bool isSelected = (m_selectedPath == path);

                    ImGui::PushID(static_cast<int>(i));

                    if (ImGui::Selectable(displayName.c_str(), isSelected)) {
                        m_selectedPath = path;
                    }

                    ImGui::PopID();
                }

                ImGui::Spacing();
                ImGui::Separator();
                ImGui::Spacing();

                // Add folder button
                if (ImGui::Button("+ Directory", ImVec2(-1, 0))) {
                    auto selection = pfd::select_folder("Select Audio Library Folder").result();

                    if (!selection.empty()) {
                        std::filesystem::path newPath(selection);

                        if (std::filesystem::exists(newPath) && std::filesystem::is_directory(newPath)) {
                            if (std::find(project.libraryDirectories.begin(), project.libraryDirectories.end(), newPath) == project.libraryDirectories.end()) {
                                project.libraryDirectories.push_back(newPath);
                                m_selectedPath = newPath;
                            }
                        }
                    }
                }

                ImGui::EndChild();

                // Right column
                ImGui::TableSetColumnIndex(1);
                ImGui::BeginChild("RightContentPane", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

                if (!m_selectedPath.empty() && std::filesystem::exists(m_selectedPath)) {
                    ImGui::TextDisabled("Viewing: %s", m_selectedPath.string().c_str());

                    ImGui::Spacing();
                    ImGui::Separator();
                    ImGui::Spacing();

                    renderDirectoryTree(m_selectedPath);
                } else {
                    ImGui::Text("Select a folder on the left to view contents.");
                }

                ImGui::EndChild();
                ImGui::EndTable();
            }

            ImGui::End();
        }
    private:
        std::filesystem::path m_selectedPath = "";

        void renderDirectoryTree(const std::filesystem::path& currentPath) {
            std::error_code ec;
            auto iterator = std::filesystem::directory_iterator(currentPath, ec);

            if (ec) return;

            std::vector<std::filesystem::path> directories;
            std::vector<std::filesystem::path> audioFiles;

            for (const auto& entry : iterator) {
                if (entry.is_directory(ec)) {
                    directories.push_back(entry.path());
                } else if (entry.is_regular_file(ec)) {
                    std::string ext = entry.path().extension().string();

                    if (ext == ".wav" || ext == ".flac" || ext == ".mp3") {
                        audioFiles.push_back(entry.path());
                    }
                }
            }

            for (const auto& dir : directories) {
                std::string dirName = dir.filename().string();

                if (ImGui::TreeNodeEx(dirName.c_str(), ImGuiTreeNodeFlags_OpenOnArrow)) {
                    renderDirectoryTree(dir);
                    ImGui::TreePop();
                }
            }

            for (const auto& file : audioFiles) {
                std::string fileName = file.filename().string();

                ImGuiTreeNodeFlags fileFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                ImGui::TreeNodeEx(fileName.c_str(), fileFlags);

                if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
                    std::string fullPath = file.string();
                    ImGui::SetDragDropPayload("DND_AUDIO_FILE", fullPath.c_str(), fullPath.length() + 1);
                    ImGui::Text("Drop to load: %s", fileName.c_str());
                    ImGui::EndDragDropSource();
                }
            }
        }
    };
}
