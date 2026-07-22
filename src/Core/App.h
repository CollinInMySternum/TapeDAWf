#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Audio/AudioEngine.h"
#include "Common/AudioCommands.h"

#include "GUI/ProjectManagerWindow.h"
#include "GUI/ProjectWindow.h"

namespace Tapedawf {
    class App {
    public:
        bool init() {
            if (!initWindow()) return false;
            initImGui();
            if (!initAudio()) return false;

            return true;
        }

        void run() {
            while (!glfwWindowShouldClose(m_window)) {
                glfwPollEvents();

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                if (m_activeProject) {
                    ImGuiID dockspace_id = ImGui::GetID("DockSpace");
                    ImGui::DockSpaceOverViewport(dockspace_id, ImGui::GetMainViewport());
                }

                renderUI();
                renderFrame();
            }
        }

        void shutdown() {
            m_audioEngine.stop();
            m_audioEngine.shutdown();

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();

            if (m_window) glfwDestroyWindow(m_window);
            glfwTerminate();
        }

    private:
        GLFWwindow* m_window{nullptr};
        AudioEngine m_audioEngine;
        AudioControls m_controls;

        ProjectManager m_projectManager;

        ProjectManagerWindow m_pmWindow;
        std::unique_ptr<ProjectWindow> m_activeProject{nullptr};

        bool initWindow() {
            if (!glfwInit()) return false;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

            m_window = glfwCreateWindow(640, 480, "TapeDAWf - Project Manager", nullptr, nullptr);

            if (!m_window) {
                glfwTerminate();
                return false;
            }

            glfwMakeContextCurrent(m_window);
            glfwSwapInterval(1); // VSync

            return true;
        }

        void initImGui() {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();

            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            ImGui::StyleColorsDark();

            // Fine tuning viewport styling
            ImGuiStyle& style = ImGui::GetStyle();

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            ImGui_ImplGlfw_InitForOpenGL(m_window, true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }

        bool initAudio() {
            if (m_audioEngine.init(m_controls, 48000, 2)) {
                return m_audioEngine.start();
            }
            return false;
        }

        void renderUI() {
            if (!m_activeProject) {
                if (auto newProj = m_pmWindow.render(m_projectManager)) {
                    std::string title = "TapeDAWf - " + newProj->name;

                    m_activeProject = std::make_unique<ProjectWindow>(std::move(newProj), m_controls);

                    glfwSetWindowSize(m_window, 1280, 720);
                    glfwSetWindowTitle(m_window, title.c_str());
                }
                return;
            }

            if (!m_activeProject->render()) {
                m_activeProject.reset();
            }
        }

        void renderFrame() {
            ImGui::Render();

            int display_w, display_h;

            glfwGetFramebufferSize(m_window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.10f, 0.10f, 0.12f, 1.00f);
            glClear(GL_COLOR_BUFFER_BIT);

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
            glfwSwapBuffers(m_window);
        }
    };
}
