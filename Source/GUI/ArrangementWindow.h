#pragma once

#include <imgui.h>
#include <vector>
#include <memory>

#include "Tracks/Track.h"
#include "Tracks/AudioTrack.h"

namespace Tapedawf {
    class ArrangementWindow {
    public:
        float zoomPixelsPerSecond = 50.0f;
        double playheadTime = 0.0;

        int selectedTrackIdx = -1;
        int selectedClipIndex = -1;

        const float TRACK_HEIGHT = 80.0f;
        const float TRACK_SPACING = 8.0f;
        const float ROUNDING = 6.0f;

        void render(Project& project) {
            ImGui::Begin("Arrangement");

            renderToolbar(project);

            ImGui::Separator();

            if (ImGui::BeginTable("ArrangementTable", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY, ImVec2(0, 0))) {
                ImGui::TableSetupColumn("Timeline Sequencer", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("Track Controls", ImGuiTableColumnFlags_WidthFixed, 250.0f);

                ImGui::TableHeadersRow();

                for (size_t i = 0; i < project.tracks.size(); ++i) {
                    ImGui::PushID(static_cast<int>(i));

                    // Track sequencer viewport
                    ImGui::TableNextRow(0, 60.0f);

                    ImGui::TableSetColumnIndex(0);
                    renderTrackTimeline(project, i);

                    // Track control header
                    ImGui::TableSetColumnIndex(1);
                    renderTrackHeader(project, i);

                    ImGui::PopID();
                }

                ImGui::EndTable();
            }

            ImGui::End();
        }
    private:
        void renderToolbar(Project& project) {
            if (ImGui::Button("+ Audio Track")) {
                project.addTrack(TrackType::Audio);
            }
            ImGui::SameLine();
            if (ImGui::Button("+ MIDI Track")) {
                project.addTrack(TrackType::Midi);
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(120.0f);
            ImGui::SliderFloat("Zoom", &zoomPixelsPerSecond, 10.0f, 200.0f, "%.0f px/s");

            ImGui::SameLine();
            ImGui::Text(" | Playhead: %.2f s", playheadTime);
        }

        void renderTrackHeader(Project& project, size_t index) {
            auto track = project.tracks[index];

            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, ROUNDING);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10.0f, 10.0f));

            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImGui::GetStyleColorVec4(ImGuiCol_Button));

            std::string headerId = "Header_" + std::to_string(index);

            ImGui::BeginChild(headerId.c_str(), ImVec2(0, TRACK_HEIGHT), true, ImGuiWindowFlags_NoScrollbar);

            // Track Name and Type
            const char* typeBadge = (track->getType() == TrackType::Audio) ? "[AUDIO]" : "[MIDI]";
            ImGui::Text("%s %s", typeBadge, track->name.c_str());

            ImGui::Spacing();

            // Mute / Solo / Arm
            bool muted = track->isMuted.load();
            if (ImGui::Checkbox("M", &muted)) track->isMuted.store(muted);

            ImGui::SameLine();
            bool soloed = track->isSoloed.load();
            if (ImGui::Checkbox("S", &soloed)) track->isSoloed.store(soloed);

            ImGui::SameLine();
            bool armed = track->isArmed.load();
            if (ImGui::Checkbox("A", &armed)) track->isArmed.store(armed);

            // Volume slider
            float vol = track->volume.load();
            ImGui::SetNextItemWidth(100.0f);
            if (ImGui::SliderFloat("##Vol", &vol, 0.0f, 1.0f, "Vol: %.2f")) {
                track->volume.store(vol);
            }

            ImGui::EndChild();

            ImGui::PopStyleColor();
            ImGui::PopStyleVar(2);

            // Right click context menu
            if (ImGui::BeginPopupContextItem("TrackPopup")) {
                if (ImGui::MenuItem("Delete Track")) {
                    project.removeTrack(index);
                }
                ImGui::EndPopup();
            }

            ImGui::Dummy(ImVec2(0, TRACK_SPACING));
        }

        void renderTrackTimeline(Project& project, size_t index) {
            auto track = project.tracks[index];

            ImVec2 canvasPos = ImGui::GetCursorScreenPos();
            ImVec2 canvasSize = ImVec2(ImGui::GetContentRegionAvail().x, TRACK_HEIGHT);

            ImDrawList* drawList = ImGui::GetWindowDrawList();

            ImU32 trackBgColor = ImGui::GetColorU32(ImGuiCol_FrameBg);
            ImU32 trackBorderColor = ImGui::GetColorU32(ImGuiCol_Border);

            // Sequencer background
            drawList->AddRectFilled(canvasPos, ImVec2(canvasPos.x + canvasSize.x, canvasPos.y + canvasSize.y), trackBgColor);
            drawList->AddRect(canvasPos, ImVec2(canvasPos.x + canvasSize.x, canvasPos.y + canvasSize.y), trackBorderColor);

            // Grid lines
            float stepPx = zoomPixelsPerSecond;
            for (float x = 0; x < canvasSize.x; x += stepPx) {
                drawList->AddLine(
                    ImVec2(canvasPos.x + x, canvasPos.y),
                    ImVec2(canvasPos.x + x, canvasPos.y + canvasSize.y),
                    trackBorderColor
                );
            }

            // Render track audio clips
            if (track->getType() == TrackType::Audio) {
                auto audioTrack = std::static_pointer_cast<AudioTrack>(track);
                auto& clips = const_cast<std::vector<AudioClip>&>(audioTrack->getClips());

                for (size_t cIdx = 0; cIdx < clips.size(); ++cIdx) {
                    renderAudioClip(audioTrack, clips[cIdx], cIdx, canvasPos, canvasSize);
                }
            }

            // Render track midi clips
            else if (track->getType() == TrackType::Midi) {
                auto midiTrack = std::static_pointer_cast<MidiTrack>(track);
                auto& clips = midiTrack->getClips();

                for (size_t cIdx = 0; cIdx < clips.size(); ++cIdx) {
                    renderMidiClip(clips[cIdx], cIdx, canvasPos, canvasSize);
                }
            }

            // Invisible button for interaction over the timeline track slot
            ImGui::SetCursorScreenPos(canvasPos);
            ImGui::InvisibleButton("TrackCanvas", canvasSize);

            // Handle scrubbing/moving playhead
            if (ImGui::IsItemActive() && ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
                float clickX = ImGui::GetIO().MousePos.x - canvasPos.x;
                playheadTime = std::max(0.0f, clickX / zoomPixelsPerSecond);
            }

            // Draw playhead line
            float playheadPx = canvasPos.x + static_cast<float>(playheadTime) * zoomPixelsPerSecond;
            if (playheadPx >= canvasPos.x && playheadPx <= canvasPos.x + canvasSize.x) {
                drawList->AddLine(
                    ImVec2(playheadPx, canvasPos.y),
                    ImVec2(playheadPx, canvasPos.y + canvasSize.y),
                    IM_COL32(255, 80, 80, 255), 2.0f
                );
            }

            ImGui::SetCursorScreenPos(canvasPos);
            ImGui::Dummy(canvasSize);

            ImGui::Dummy(ImVec2(0, TRACK_SPACING));
        }

        void renderAudioClip(std::shared_ptr<AudioTrack> track, AudioClip& clip, size_t clipIdx, ImVec2 canvasPos, ImVec2 canvasSize) {
            ImDrawList* drawList = ImGui::GetWindowDrawList();

            float clipX1 = canvasPos.x + static_cast<float>(clip.timelineStart) * zoomPixelsPerSecond;
            float clipX2 = clipX1 + static_cast<float>(clip.duration) * zoomPixelsPerSecond;

            ImVec2 clipMin(clipX1, canvasPos.y + 4.0f);
            ImVec2 clipMax(clipX2, canvasPos.y + canvasSize.y - 4.0f);

            bool isSelected = (selectedClipIndex == static_cast<int>(clipIdx));

            // Clip Body
            ImU32 clipColor = isSelected ? IM_COL32(70, 130, 180, 230) : IM_COL32(50, 90, 140, 200);
            drawList->AddRectFilled(clipMin, clipMax, clipColor, 4.0f);
            drawList->AddRect(clipMin, clipMax, IM_COL32(120, 180, 240, 255), 4.0f);

            // Label
            drawList->AddText(ImVec2(clipMin.x + 6.0f, clipMin.y + 4.0f), IM_COL32(255, 255, 255, 255), clip.name.c_str());

            // Drag & Splice
            ImGui::PushID(static_cast<int>(clipIdx));
            ImGui::SetCursorScreenPos(clipMin);
            ImGui::InvisibleButton("AudioClipBtn", ImVec2(clipMax.x - clipMin.x, clipMax.y - clipMin.y));

            if (ImGui::IsItemClicked(ImGuiMouseButton_Left)) {
                selectedClipIndex = static_cast<int>(clipIdx);
            }

            // Drag clip to move along timeline
            if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                float deltaX = ImGui::GetIO().MouseDelta.x;
                clip.timelineStart += deltaX / zoomPixelsPerSecond;
                if (clip.timelineStart < 0.0) clip.timelineStart = 0.0;
            }

            // Splice Shortcut: Select Clip and press 'S' key
            if (isSelected && ImGui::IsKeyPressed(ImGuiKey_S)) {
                spliceAudioClip(*track, clipIdx, playheadTime);
            }

            ImGui::PopID();
        }

        void renderMidiClip(MidiClip& clip, size_t clipIdx, ImVec2 canvasPos, ImVec2 canvasSize) {
            ImDrawList* drawList = ImGui::GetWindowDrawList();

            float clipX1 = canvasPos.x + static_cast<float>(clip.timelineStart) * zoomPixelsPerSecond;
            float clipX2 = clipX1 + static_cast<float>(clip.duration) * zoomPixelsPerSecond;
            ImVec2 clipMin(clipX1, canvasPos.y + 4.0f);
            ImVec2 clipMax(clipX2, canvasPos.y + canvasSize.y - 4.0f);

            // MIDI Clip Body
            drawList->AddRectFilled(clipMin, clipMax, IM_COL32(120, 80, 140, 200), 4.0f);
            drawList->AddRect(clipMin, clipMax, IM_COL32(180, 130, 200, 255), 4.0f);
            drawList->AddText(ImVec2(clipMin.x + 6.0f, clipMin.y + 4.0f), IM_COL32(255, 255, 255, 255), clip.name.c_str());

            // Mini MIDI Note Preview Visualization
            for (const auto& note : clip.notes) {
                float noteX1 = clipMin.x + static_cast<float>(note.start) * zoomPixelsPerSecond;
                float noteX2 = noteX1 + static_cast<float>(note.duration) * zoomPixelsPerSecond;
                float noteY = clipMin.y + 20.0f + (88 - note.noteNumber) * 0.2f; // Scaled note pitch height

                drawList->AddRectFilled(
                    ImVec2(noteX1, noteY),
                    ImVec2(noteX2, noteY + 3.0f),
                    IM_COL32(255, 220, 100, 255)
                );
            }

            // Dragging MIDI Clips
            ImGui::PushID(static_cast<int>(clipIdx));
            ImGui::SetCursorScreenPos(clipMin);
            ImGui::InvisibleButton("MidiClipBtn", ImVec2(clipMax.x - clipMin.x, clipMax.y - clipMin.y));

            if (ImGui::IsItemActive() && ImGui::IsMouseDragging(ImGuiMouseButton_Left)) {
                float deltaX = ImGui::GetIO().MouseDelta.x;
                clip.timelineStart += deltaX / zoomPixelsPerSecond;
                if (clip.timelineStart < 0.0) clip.timelineStart = 0.0;
            }

            ImGui::PopID();
        }
    };
}