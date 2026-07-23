#pragma once

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "Audio/AudioEngine.h"
#include "Common/AudioCommands.h"

#include "GUI/ProjectManagerWindow.h"
#include "GUI/ProjectWindow.h"
#include "Common/Logging.h"
#include "whereami.h"
#include "Common/Styles.h"

namespace Tapedawf {
    class App {
    public:
        bool init() {
            LOG("App", "Initializing application...");
            if (!initWindow()) {
                LOG("App", "Failed to initialize GLFW window!");
                return false;
            }
            LOG("App", "GLFW window initialized successfully.");

            initImGui();
            LOG("App", "ImGui context and backend initialized.");

            if (!initAudio()) {
                LOG("App", "Failed to initialize/start audio engine!");
                return false;
            }
            LOG("App", "Audio engine started successfully.");

            return true;
        }

        void run() {
            LOG("App", "Entering main application loop...");
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
            LOG("App", "Main loop terminated.");
        }

        void shutdown() {
            LOG("App", "Shutting down...");

            m_audioEngine.stop();
            m_audioEngine.shutdown();
            LOG("App", "Stopped audio engine.");

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            LOG("App", "Shutdown ImGui.");

            if (m_window) glfwDestroyWindow(m_window);
            glfwTerminate();

            LOG("App", "Destroyed GLFW window.");
            LOG("App", "Shutdown complete.");
        }

    private:
        GLFWwindow* m_window{nullptr};
        AudioEngine m_audioEngine;
        AudioControls m_controls;

        ProjectManager m_projectManager;

        ProjectManagerWindow m_pmWindow;
        std::unique_ptr<ProjectWindow> m_activeProject{nullptr};

        bool initWindow() {
            LOG("Window", "Initializing GLFW...");
            if (!glfwInit()) return false;

            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);
            glfwWindowHint(GLFW_SRGB_CAPABLE, GL_FALSE);

            LOG("Window", "Creating GLFW window @(640x480)");
            m_window = glfwCreateWindow(640, 480, "TapeDAWf - Project Manager", nullptr, nullptr);

            if (!m_window) {
                LOG("Window", "GLFW window creation failed!");
                glfwTerminate();
                return false;
            }

            glfwMakeContextCurrent(m_window);
            glfwSwapInterval(1); // VSync

            LOG("Window", "OpenGL context set and VSync enabled.");

            return true;
        }

        void initImGui() {
            LOG("ImGUI", "Configuring ImGui flags and style...");

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();

            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
            io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

            ImGuiStyle& style = ImGui::GetStyle();
            ImGui::StyleColorsDark();
            //Styles::setupImGuiNuklearDarkGrayStyle(style);

            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
                style.WindowRounding = 0.0f;
                style.Colors[ImGuiCol_WindowBg].w = 1.0f;
            }

            std::string fontPath = getExecutableRelativePath("Resources/Fonts/Montserrat/Montserrat-Medium.ttf").string();
            std::cout << fontPath;
            //io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 16.0f);

            ImGui_ImplGlfw_InitForOpenGL(m_window, true);
            ImGui_ImplOpenGL3_Init("#version 330");
        }

        bool initAudio() {
            LOG("AudioEngine", "Initializing audio backend (48000Hz, 2 channels)...");

            if (m_audioEngine.init(m_controls, 48000, 2)) {
                LOG("AudioEngine", "Starting audio stream...");
                return m_audioEngine.start();
            }
            LOG("AudioEngine", "Audio initialization failed.");
            return false;
        }

        void renderUI() {
            if (!m_activeProject) {
                if (auto newProj = m_pmWindow.render(m_projectManager)) {
                    std::string title = "TapeDAWf - " + newProj->name;
                    LOG("App", "Project loaded/created successfully: '{}'", newProj->name);

                    m_activeProject = std::make_unique<ProjectWindow>(std::move(newProj), m_controls);

                    LOG("Window", "Resizing window to (1280x720) for DAW workspace.");
                    glfwSetWindowSize(m_window, 1280, 720);
                    glfwSetWindowTitle(m_window, title.c_str());
                }
                return;
            }

            if (!m_activeProject->render()) {
                LOG("App", "Project close requested by user. Resetting active project.");
                m_activeProject.reset();

                LOG("Window", "Resizing window back to (640x480) for Project Manager.");
                glfwSetWindowSize(m_window, 640, 480);
                glfwSetWindowTitle(m_window, "TapeDAWf - Project Manager");
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


        std::filesystem::path getExecutablePath() {
            int length, dirnameLength;
            wai_getExecutablePath(NULL, 0, &length);

            std::string path(length, '\0');
            wai_getExecutablePath(&path[0], length, &dirnameLength);

            path.resize(dirnameLength);
            return std::filesystem::path(path);
        }

        std::filesystem::path getExecutableRelativePath(const std::filesystem::path& relativePath) {
            return (getExecutablePath() / relativePath).lexically_normal();
        }
    };
}
