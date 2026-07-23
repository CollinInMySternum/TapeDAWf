#include <imgui.h>

class Styles {

public:
	static void setupImGuiDarkStyle(ImGuiStyle& style) {
		setupImGuiDarkStyle(style);
	}

	static void setupImGuiDraculaStyle(ImGuiStyle& style) {
	    // --- 1. Sizing and Spacing (Clean & Balanced) ---
	    style.WindowPadding = ImVec2(10.0f, 10.0f);
	    style.FramePadding = ImVec2(6.0f, 4.0f);
	    style.ItemSpacing = ImVec2(8.0f, 6.0f);
	    style.ScrollbarSize = 14.0f;
	    style.GrabMinSize = 12.0f;

	    // --- 2. Borders & Rounding ---
	    style.WindowRounding = 6.0f;
	    style.FrameRounding = 4.0f;
	    style.PopupRounding = 4.0f;
	    style.ScrollbarRounding = 12.0f;
	    style.GrabRounding = 4.0f;
	    style.TabRounding = 4.0f;

	    style.WindowBorderSize = 1.0f;
	    style.FrameBorderSize = 1.0f;

	    // --- 3. The Dracula Color Palette ---
	    // Background: #282a36 | Selection: #44475a | Foreground: #f8f8f2
	    // Comment: #6272a4    | Cyan: #8be9fd      | Green: #50fa7b
	    // Orange: #ffb86c     | Pink: #ff79c6      | Purple: #bd93f9
	    // Red: #ff5555        | Yellow: #f1fa8c

	    // Text
	    style.Colors[ImGuiCol_Text] = ImVec4(0.97f, 0.97f, 0.95f, 1.00f); // #f8f8f2
	    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f); // #6272a4

	    // Backgrounds
	    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f); // #282a36
	    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.16f, 0.16f, 0.21f, 0.00f);
	    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.16f, 0.16f, 0.21f, 0.96f);

	    // Borders
	    style.Colors[ImGuiCol_Border] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f); // #44475a
	    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

	    // Frames (Inputs, etc.)
	    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f); // #44475a
	    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f); // #6272a4
	    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.48f, 0.55f, 0.74f, 1.00f);

	    // Title Bars
	    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.13f, 0.14f, 0.18f, 1.00f); // Darker
	    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.13f, 0.14f, 0.18f, 1.00f);

	    // Menus
	    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.13f, 0.14f, 0.18f, 1.00f);

	    // Scrollbars
	    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.48f, 0.55f, 0.74f, 1.00f);

	    // Interactables
	    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.31f, 0.98f, 0.48f, 1.00f); // #50fa7b (Green)
	    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.74f, 0.58f, 0.98f, 1.00f); // #bd93f9 (Purple)
	    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.84f, 0.68f, 1.00f, 1.00f);
	    style.Colors[ImGuiCol_Button] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
	    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.47f, 0.78f, 1.00f); // #ff79c6 (Pink)
	    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.37f, 0.62f, 1.00f);
	    style.Colors[ImGuiCol_Header] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
	    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f);
	    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.48f, 0.55f, 0.74f, 1.00f);

	    // Tabs
	    style.Colors[ImGuiCol_Tab] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
	    style.Colors[ImGuiCol_TabActive] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
	    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.13f, 0.14f, 0.18f, 1.00f);
	    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);

	    // Tables
	    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
	    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.38f, 0.45f, 0.64f, 1.00f);
	    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);

	    // Misc
	    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.55f, 0.91f, 0.99f, 1.00f); // #8be9fd (Cyan)
	    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.27f, 0.28f, 0.35f, 1.00f);
	    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.74f, 0.58f, 0.98f, 1.00f);

	#ifdef IMGUI_HAS_DOCK
	    style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.74f, 0.58f, 0.98f, 0.50f);
	    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.16f, 0.16f, 0.21f, 1.00f);
	#endif
	}

	// https://github.com/ocornut/imgui/issues/707
	static void setupImGuiCatpuccinMochaStyle(ImGuiStyle& style)
	{
	    // --- 1. Sizing and Spacing (Soft & Modern) ---
	    style.WindowPadding = ImVec2(12.0f, 12.0f);
	    style.FramePadding = ImVec2(6.0f, 4.0f);
	    style.ItemSpacing = ImVec2(8.0f, 6.0f);
	    style.ScrollbarSize = 14.0f;
	    style.GrabMinSize = 12.0f;

	    // --- 2. Borders & Rounding ---
	    style.WindowRounding = 8.0f;
	    style.FrameRounding = 5.0f;
	    style.PopupRounding = 5.0f;
	    style.ScrollbarRounding = 12.0f;
	    style.GrabRounding = 5.0f;
	    style.TabRounding = 5.0f;

	    style.WindowBorderSize = 1.0f;
	    style.FrameBorderSize = 0.0f; // Minimalist look
	    style.PopupBorderSize = 1.0f;

	    // --- 3. The Catppuccin Mocha Palette ---
	    // Base: #1e1e2e | Mantle: #181825 | Crust: #11111b
	    // Text: #cdd6f4 | Subtext0: #a6adc8 | Surface0: #313244
	    // Lavender: #b4befe | Sapphire: #74c7ec | Mauve: #cba6f7

	    // Text
	    style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.84f, 0.96f, 1.00f); // Text
	    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.42f, 0.45f, 0.55f, 1.00f); // Surface1

	    // Backgrounds
	    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f); // Base
	    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f); // Mantle
	    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.11f, 0.96f); // Crust

	    // Borders
	    style.Colors[ImGuiCol_Border] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f); // Surface0
	    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

	    // Frames (Inputs, etc.)
	    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f); // Surface0
	    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.26f, 0.35f, 1.00f); // Surface1
	    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f); // Surface2

	    // Title Bars
	    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f); // Mantle
	    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f); // Base
	    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.07f, 0.07f, 0.11f, 1.00f); // Crust

	    // Menus
	    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);

	    // Scrollbars
	    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f); // Surface2
	    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.37f, 0.38f, 0.51f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.42f, 0.45f, 0.55f, 1.00f);

	    // Interactables
	    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.75f, 1.00f, 1.00f); // Lavender
	    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.45f, 0.78f, 0.93f, 1.00f); // Sapphire
	    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.45f, 0.78f, 0.93f, 1.00f);
	    style.Colors[ImGuiCol_Button] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f);
	    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.80f, 0.65f, 0.97f, 1.00f); // Mauve
	    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.70f, 0.55f, 0.87f, 1.00f);
	    style.Colors[ImGuiCol_Header] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f);
	    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.26f, 0.35f, 1.00f);
	    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f);

	    // Tabs
	    style.Colors[ImGuiCol_Tab] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f);
	    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f);
	    style.Colors[ImGuiCol_TabActive] = ImVec4(0.19f, 0.20f, 0.27f, 1.00f);
	    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.09f, 0.09f, 0.15f, 1.00f);
	    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f);

	    // Misc
	    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.94f, 0.72f, 0.42f, 1.00f); // Marigold
	    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.31f, 0.32f, 0.42f, 1.00f);
	    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.71f, 0.75f, 1.00f, 1.00f); // Lavender

	#ifdef IMGUI_HAS_DOCK
	    style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.71f, 0.75f, 1.00f, 0.50f);
	    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.12f, 0.12f, 0.18f, 1.00f);
	#endif
	}

	static void setupImGuiGruvboxHardStyle(ImGuiStyle& style)
	{
	    // --- 1. Sizing and Spacing (Industrial & Square) ---
	    style.WindowPadding = ImVec2(10.0f, 10.0f);
	    style.FramePadding = ImVec2(6.0f, 4.0f);
	    style.ItemSpacing = ImVec2(8.0f, 4.0f);
	    style.ScrollbarSize = 14.0f;
	    style.GrabMinSize = 12.0f;

	    // --- 2. Borders & Rounding (Gruvbox usually looks best with sharp or low rounding) ---
	    style.WindowRounding = 2.0f;
	    style.FrameRounding = 2.0f;
	    style.PopupRounding = 2.0f;
	    style.ScrollbarRounding = 2.0f;
	    style.GrabRounding = 2.0f;
	    style.TabRounding = 2.0f;

	    style.WindowBorderSize = 1.0f;
	    style.FrameBorderSize = 1.0f;
	    style.PopupBorderSize = 1.0f;

	    // --- 3. The Gruvbox Dark Hard Palette ---
	    // Background: #1d2021 (Dark Hard) | Foreground: #ebdbb2
	    // Red: #fb4934 | Green: #b8bb26 | Yellow: #fabd2f | Blue: #83a598
	    // Gray: #928374 | Orange: #fe8019

	    // Text
	    style.Colors[ImGuiCol_Text] = ImVec4(0.92f, 0.86f, 0.70f, 1.00f); // #ebdbb2
	    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.57f, 0.51f, 0.45f, 1.00f); // #928374

	    // Backgrounds
	    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f); // #1d2021
	    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.11f, 0.13f, 0.13f, 0.00f);
	    style.Colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.13f, 0.13f, 0.95f);

	    // Borders
	    style.Colors[ImGuiCol_Border] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f); // #504945
	    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);

	    // Frames
	    style.Colors[ImGuiCol_FrameBg] = ImVec4(0.24f, 0.22f, 0.21f, 1.00f); // #3c3836
	    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f); // #504945
	    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.40f, 0.36f, 0.33f, 1.00f); // #665c54

	    // Title Bars
	    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
	    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
	    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);

	    // Menus
	    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.14f, 0.13f, 1.00f); // #282828

	    // Scrollbars
	    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.36f, 0.33f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.57f, 0.51f, 0.45f, 1.00f);

	    // Interactables
	    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.72f, 0.73f, 0.15f, 1.00f); // #b8bb26 (Green)
	    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.51f, 0.65f, 0.60f, 1.00f); // #83a598 (Blue)
	    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.55f, 0.73f, 0.67f, 1.00f);
	    style.Colors[ImGuiCol_Button] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
	    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.98f, 0.29f, 0.20f, 1.00f); // #fb4934 (Red)
	    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.80f, 0.20f, 0.15f, 1.00f);
	    style.Colors[ImGuiCol_Header] = ImVec4(0.24f, 0.22f, 0.21f, 1.00f);
	    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
	    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.40f, 0.36f, 0.33f, 1.00f);

	    // Tabs
	    style.Colors[ImGuiCol_Tab] = ImVec4(0.24f, 0.22f, 0.21f, 1.00f);
	    style.Colors[ImGuiCol_TabHovered] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
	    style.Colors[ImGuiCol_TabActive] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);

	    // Misc
	    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.98f, 0.74f, 0.18f, 1.00f); // #fabd2f (Yellow)
	    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.31f, 0.29f, 0.27f, 1.00f);
	    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.98f, 0.29f, 0.20f, 1.00f);

	#ifdef IMGUI_HAS_DOCK
	    style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.72f, 0.73f, 0.15f, 0.50f);
	    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.11f, 0.13f, 0.13f, 1.00f);
	#endif
	}

	inline static void setupImGuiNuklearDarkGrayStyle(ImGuiStyle& style) {
		style.WindowBorderSize = 1.0f;
		style.ChildBorderSize = 1.0f;
		style.PopupBorderSize = 1.0f;
		style.FrameBorderSize = 1.0f;

		style.WindowRounding = 2.0f;
		style.ChildRounding = 2.0f;
		style.FrameRounding = 2.0f;
		style.PopupRounding = 2.0f;
		style.GrabRounding = 2.0f;

		style.Colors[ImGuiCol_Text]                   = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		style.Colors[ImGuiCol_TextDisabled]           = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_WindowBg]               = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_PopupBg]                = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_Border]                 = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		style.Colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_FrameBg]                = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_FrameBgActive]          = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		style.Colors[ImGuiCol_TitleBg]                = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_TitleBgActive]          = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.18f, 0.18f, 0.18f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
		style.Colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
		style.Colors[ImGuiCol_CheckMark]              = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		style.Colors[ImGuiCol_CheckboxSelectedBg]     = ImVec4(0.15f, 0.15f, 0.15f, 0.50f);
		style.Colors[ImGuiCol_SliderGrab]             = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
		style.Colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.59f, 0.59f, 0.59f, 1.00f);
		style.Colors[ImGuiCol_Button]                 = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		style.Colors[ImGuiCol_ButtonHovered]          = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_ButtonActive]           = ImVec4(0.12f, 0.12f, 0.12f, 1.00f);
		style.Colors[ImGuiCol_Header]                 = ImVec4(0.18f, 0.18f, 0.18f, 0.00f);
		style.Colors[ImGuiCol_HeaderHovered]          = ImVec4(0.22f, 0.22f, 0.22f, 0.78f);
		style.Colors[ImGuiCol_HeaderActive]           = ImVec4(0.29f, 0.29f, 0.29f, 0.78f);
		style.Colors[ImGuiCol_Separator]              = ImVec4(0.29f, 0.29f, 0.29f, 0.50f);
		style.Colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.49f, 0.49f, 0.49f, 0.78f);
		style.Colors[ImGuiCol_SeparatorActive]        = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		style.Colors[ImGuiCol_ResizeGrip]             = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
		style.Colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		style.Colors[ImGuiCol_InputTextCursor]        = ImVec4(0.78f, 0.78f, 0.78f, 1.00f);
		style.Colors[ImGuiCol_TabHovered]             = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
		style.Colors[ImGuiCol_Tab]                    = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_TabSelected]            = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
		style.Colors[ImGuiCol_TabSelectedOverline]    = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
		style.Colors[ImGuiCol_TabDimmed]              = ImVec4(0.29f, 0.29f, 0.29f, 0.78f);
		style.Colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.39f, 0.39f, 0.39f, 0.78f);
		style.Colors[ImGuiCol_TabDimmedSelectedOverline]  = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
		style.Colors[ImGuiCol_DockingPreview]         = ImVec4(0.69f, 0.69f, 0.69f, 0.78f);
		style.Colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.22f, 0.22f, 0.22f, 1.00f);
		style.Colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
		style.Colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
		style.Colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
		style.Colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.29f, 0.29f, 0.29f, 1.00f);
		style.Colors[ImGuiCol_TableBorderLight]       = ImVec4(0.29f, 0.29f, 0.29f, 0.50f);
		style.Colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		style.Colors[ImGuiCol_TextLink]               = ImVec4(0.29f, 0.50f, 1.00f, 1.00f);
		style.Colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
		style.Colors[ImGuiCol_TreeLines]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
		style.Colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
		style.Colors[ImGuiCol_DragDropTargetBg]       = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		style.Colors[ImGuiCol_UnsavedMarker]          = ImVec4(0.69f, 0.69f, 0.69f, 1.00f);
		style.Colors[ImGuiCol_NavCursor]              = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
		style.Colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
		style.Colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
		style.Colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);
	}

	static void setupImGuiPaperAndInkStyle(ImGuiStyle& style) {
	    // --- 1. Sizing & Spacing (Clean & Rigid) ---
	    style.WindowPadding = ImVec2(12.0f, 12.0f);
	    style.FramePadding = ImVec2(6.0f, 4.0f);
	    style.CellPadding = ImVec2(6.0f, 4.0f);
	    style.ItemSpacing = ImVec2(8.0f, 6.0f);
	    style.ItemInnerSpacing = ImVec2(6.0f, 4.0f);
	    style.ScrollbarSize = 14.0f;
	    style.GrabMinSize = 12.0f;

	    // --- 2. Borders & Rounding (Technical/Drafting feel) ---
	    style.WindowRounding = 2.0f;
	    style.ChildRounding = 2.0f;
	    style.FrameRounding = 2.0f;
	    style.PopupRounding = 2.0f;
	    style.ScrollbarRounding = 12.0f;
	    style.GrabRounding = 2.0f;
	    style.TabRounding = 2.0f;

	    style.WindowBorderSize = 1.0f;
	    style.ChildBorderSize = 1.0f;
	    style.PopupBorderSize = 1.0f;
	    style.FrameBorderSize = 1.0f;
	    style.TabBorderSize = 1.0f;

	    // --- 3. Full Color Palette ---

	    // Main Text & Background
	    style.Colors[ImGuiCol_Text] = ImVec4(0.12f, 0.12f, 0.12f, 1.00f); // Deep Carbon Ink
	    style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.55f, 0.55f, 0.55f, 1.00f);
	    style.Colors[ImGuiCol_WindowBg] = ImVec4(0.96f, 0.96f, 0.94f, 1.00f); // Warm Paper
	    style.Colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.03f);
	    style.Colors[ImGuiCol_PopupBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f); // Clean White Popups

	    // Borders & Separators
	    style.Colors[ImGuiCol_Border] = ImVec4(0.75f, 0.75f, 0.72f, 1.00f);
	    style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	    style.Colors[ImGuiCol_Separator] = ImVec4(0.80f, 0.80f, 0.78f, 1.00f);
	    style.Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.17f, 0.34f, 0.59f, 0.78f);
	    style.Colors[ImGuiCol_SeparatorActive] = ImVec4(0.17f, 0.34f, 0.59f, 1.00f);

	    // Frames (Inputs, Checkboxes, etc)
	    style.Colors[ImGuiCol_FrameBg] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	    style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.92f, 0.95f, 1.00f);
	    style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.85f, 0.88f, 0.92f, 1.00f);

	    // Titles & Menus
	    style.Colors[ImGuiCol_TitleBg] = ImVec4(0.92f, 0.92f, 0.90f, 1.00f);
	    style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.88f, 0.88f, 0.86f, 1.00f);
	    style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.92f, 0.92f, 0.90f, 0.75f);
	    style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.92f, 0.92f, 0.90f, 1.00f);

	    // Scrollbars
	    style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.96f, 0.96f, 0.94f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.78f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.70f, 0.70f, 0.68f, 1.00f);
	    style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.60f, 0.60f, 0.58f, 1.00f);

	    // Interactables (Blueprint Blue)
	    style.Colors[ImGuiCol_CheckMark] = ImVec4(0.17f, 0.34f, 0.59f, 1.00f);
	    style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.17f, 0.34f, 0.59f, 0.70f);
	    style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.17f, 0.34f, 0.59f, 1.00f);
	    style.Colors[ImGuiCol_Button] = ImVec4(0.17f, 0.34f, 0.59f, 0.08f);
	    style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.17f, 0.34f, 0.59f, 0.20f);
	    style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.17f, 0.34f, 0.59f, 0.35f);

	    // Header (Selection in lists/trees)
	    style.Colors[ImGuiCol_Header] = ImVec4(0.17f, 0.34f, 0.59f, 0.12f);
	    style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.17f, 0.34f, 0.59f, 0.25f);
	    style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.17f, 0.34f, 0.59f, 0.40f);

	    // Tables (Crucial for Light Mode)
	    style.Colors[ImGuiCol_TableHeaderBg] = ImVec4(0.90f, 0.90f, 0.88f, 1.00f);
	    style.Colors[ImGuiCol_TableBorderStrong] = ImVec4(0.75f, 0.75f, 0.72f, 1.00f);
	    style.Colors[ImGuiCol_TableBorderLight] = ImVec4(0.85f, 0.85f, 0.82f, 1.00f);
	    style.Colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.00f, 0.00f, 0.00f, 0.03f);

	    // Tabs
	    style.Colors[ImGuiCol_Tab] = ImVec4(0.92f, 0.92f, 0.90f, 1.00f);
	    style.Colors[ImGuiCol_TabHovered] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	    style.Colors[ImGuiCol_TabActive] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	    style.Colors[ImGuiCol_TabUnfocused] = ImVec4(0.92f, 0.92f, 0.90f, 1.00f);
	    style.Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.96f, 0.96f, 0.94f, 1.00f);

	    // Misc
	    style.Colors[ImGuiCol_PlotLines] = ImVec4(0.17f, 0.34f, 0.59f, 1.00f);
	    style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.17f, 0.34f, 0.59f, 1.00f);
	    style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.17f, 0.34f, 0.59f, 0.25f);
	    style.Colors[ImGuiCol_DragDropTarget] = ImVec4(0.17f, 0.34f, 0.59f, 0.90f);
	    style.Colors[ImGuiCol_NavHighlight] = ImVec4(0.17f, 0.34f, 0.59f, 1.00f);

	#ifdef IMGUI_HAS_DOCK
	    style.Colors[ImGuiCol_DockingPreview] = ImVec4(0.17f, 0.34f, 0.59f, 0.40f);
	    style.Colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.96f, 0.96f, 0.94f, 1.00f);
	#endif
	}
};
