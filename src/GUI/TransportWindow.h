#pragma once

#include <atomic>
#include <imgui.h>
#include <imgui_internal.h>

#include "Common/AudioCommands.h"

#include "Project/Project.h"

namespace Tapedawf {
    class TransportWindow {
    public:
        static void Render(AudioControls& controls, Project& project) {
            ImGui::Begin("Transport");

            if (ImGui::Button("PLAY")) {
                controls.commandQueue.try_enqueue(PlayCommand{.startSample = 0});
            }
            ImGui::SameLine();
            if (ImGui::Button("STOP")) {
                controls.commandQueue.try_enqueue(StopCommand{});
            }

            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();

            // Project Tempo & Time Signature
            ImGui::SetNextItemWidth(100.0f);
            ImGui::DragScalar("BPM", ImGuiDataType_Double, &project.bpm, 0.1f, nullptr, nullptr, "%.1f");

            ImGui::SameLine();
            ImGui::SetNextItemWidth(30.0f);
            ImGui::InputInt("##TimeSigTop", &project.timeSignatureTop, 0);
            ImGui::SameLine();
            ImGui::Text("/");
            ImGui::SameLine();
            ImGui::SetNextItemWidth(30.0f);
            ImGui::InputInt("##TimeSigBot", &project.timeSignatureBottom, 0);

            ImGui::SameLine();
            ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
            ImGui::SameLine();

            // Gain
            static float gain = 1.0f;
            if (ImGui::SliderFloat("Master Gain", &gain, 0.0f, 2.0f)) {
                controls.masterGain.store(gain, std::memory_order_relaxed);
            }

            ImGui::End();
        }
    };
}