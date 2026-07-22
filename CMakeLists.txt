cmake_minimum_required(VERSION 3.5)
project(Tapedawf VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)

# ==============================================================================
# 1. FETCH DEPENDENCIES
# ==============================================================================

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

# Dear ImGUI (Docking Branch)
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG docking
)

# MiniAudio
FetchContent_Declare(
    miniaudio
    GIT_REPOSITORY https://github.com/mackron/miniaudio.git
    GIT_TAG 0.11.21
)

# Lock-Free SPSC Queue Dependency
FetchContent_Declare(
    readerwriterqueue
    GIT_REPOSITORY https://github.com/cameron314/readerwriterqueue.git
    GIT_TAG v1.0.7
)

# Portable file dialogs
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
FetchContent_Declare(
    portable-file-dialogs
    GIT_REPOSITORY https://github.com/samhocevar/portable-file-dialogs.git
    GIT_TAG 0.1.0
)

# JSON for Modern C++
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.12.0
)

# ==============================================================================
# 2. DOWNLOAD AND EXTRACT ALL FETCHED CONTENT
# ==============================================================================
FetchContent_MakeAvailable(
    glfw
    imgui
    miniaudio
    readerwriterqueue
    portable-file-dialogs
    json
)

# ==============================================================================
# 3. System OpenGL
# ==============================================================================
find_package(OpenGL REQUIRED)

# ==============================================================================
# 4. CONFIGURE DEPENDENCY TARGETS
# ==============================================================================

# ImGui Static Library Setup
add_library(imgui STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

target_link_libraries(imgui PUBLIC glfw OpenGL::GL)

# Miniaudio Interface Target
add_library(miniaudio INTERFACE)
target_include_directories(miniaudio INTERFACE ${miniaudio_SOURCE_DIR})

# ==============================================================================
# 5. CONFIGURE MAIN EXECUTABLE
# ==============================================================================
add_executable(Tapedawf
    src/main.cpp
    src/audio/miniaudio_impl.cpp
)

# Include directories for source code
target_include_directories(Tapedawf PRIVATE
    src
)
target_link_libraries(Tapedawf PRIVATE
    imgui # UI
    glfw # Window
    miniaudio # Audio
    readerwriterqueue # Lock-free SPSC Queue
    OpenGL::GL # Graphics
    portable_file_dialogs # File management
    nlohmann_json::nlohmann_json
)