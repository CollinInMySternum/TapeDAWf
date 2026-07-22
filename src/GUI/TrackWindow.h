#pragma once

#include <imgui.h>
#include <vector>
#include <memory>

#include "Tracks/Track.h"
#include "Tracks/AudioTrack.h"

namespace Tapedawf {
    class TrackWindow {
    public:
        void render(Project& project) {
            ImGui::Begin("Arrangement");

            if (ImGui::BeginTable("ArrangementTable", 2, ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY, ImVec2(0, 0))) {
                ImGui::TableSetupColumn("Headers", ImGuiTableColumnFlags_WidthFixed, 250.0f);
                ImGui::TableSetupColumn("Timeline", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableHeadersRow();

                for (size_t i = 0; i < project.tracks.size(); ++i) {
                    ImGui::PushID(static_cast<int>(i));
                    renderTrackRow(project.tracks[i], i);
                    ImGui::PopID();
                }

                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                ImGui::Dummy(ImVec2(ImGui::GetContentRegionAvail().x, 50.0f));
                handleDragAndDrop(project.tracks, std::nullopt);

                ImGui::EndTable();
            }

            ImGui::End();
        }

        void renderTrackRow(std::shared_ptr<ITrack> track, size_t index) {
            ImGui::TableNextRow();

            // Left Column: Timeline/Clips
            ImGui::TableSetColumnIndex(1);

            if (track->getType() == TrackType::Audio) {
                auto audioTrack = std::static_pointer_cast<AudioTrack>(track);
                const auto& clips = audioTrack->getClips();

                if (clips.empty()) {
                    ImGui::TextDisabled("Drop audio files here..");
                } else {
                    for (const auto& clip : clips) {
                        ImGui::Button(clip.name.c_str());
                        ImGui::SameLine();
                    }
                }
            } else {
                ImGui::TextDisabled("MIDI track (no clips yet)");
            }

            ImGui::Separator();

            // Right column: Track header
            ImGui::TableSetColumnIndex(1);

            ImGui::TextUnformatted(track->name.c_str());
            ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 40.0f);
            ImGui::TextDisabled(track->getType() == TrackType::Audio ? "[A]" : "[M]");

            bool muted = track->isMuted.load();
            if (ImGui::Selectable(muted ? "M" : "m", muted, 0, ImVec2(20, 20))) track->isMuted.store(!muted);

            ImGui::SameLine();
            bool soloed = track->isSoloed.load();
            if (ImGui::Selectable(soloed ? " S " : " s ", soloed, 0, ImVec2(20, 20))) track->isSoloed.store(!soloed);

            ImGui::SameLine();
            bool armed = track->isArmed.load();
            if (ImGui::Selectable(armed ? " R " : " r ", armed, 0, ImVec2(20, 20))) track->isArmed.store(!armed);

            float vol = track->volume.load();
            ImGui::SetNextItemWidth(120.0f);
            if (ImGui::SliderFloat("Vol", &vol, 0.0f, 1.0f, "%.2f")) {
                track->volume.store(vol);
            }

            float pan = track->pan.load();
            ImGui::SetNextItemWidth(120.0f);
            if (ImGui::SliderFloat("Pan", &pan, -1.0f, 1.0f, "%.2f")) {
                track->pan.store(pan);
            }
        }

        void handleDragAndDrop(std::vector<std::shared_ptr<ITrack>>& engineTracks, std::optional<size_t> trackIndex) {
        }
    };
}