#pragma once

#include "external/imgui/imgui.h"
#include "external/imgui/imgui_internal.h"
#include "external/imgui/imgui_impl_sdl.h"
#include "external/imgui/imgui_impl_sdlrenderer.h"
#include <stdio.h>
#include "external/SDL2/include/SDL.h"
#include "external/everything/include/Everything.h"
#include "container.h"
#include <iostream>
#include <string>

void embraceTheDarkness()
{
	// ImGuiStyle& style = ImGui::GetStyle();
	ImGuiStyle* style = &ImGui::GetStyle();
	// ImVec4* colors = ImGui::GetStyle().Colors;
	style->Colors[ ImGuiCol_Text ] = ImVec4( 0.85f, 0.85f, 0.85f, 1.00f );
	style->Colors[ ImGuiCol_WindowBg ] = ImVec4( 0.09f, 0.09f, 0.09f, 1.00f );
	style->Colors[ ImGuiCol_ChildBg ] = ImVec4( 0.04f, 0.04f, 0.04f, 1.00f );
	style->Colors[ ImGuiCol_PopupBg ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	style->Colors[ ImGuiCol_MenuBarBg ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	style->Colors[ ImGuiCol_ScrollbarGrab ] = ImVec4( 0.24f, 0.24f, 0.24f, 1.00f );
	style->Colors[ ImGuiCol_Button ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	style->Colors[ ImGuiCol_ButtonHovered ] = ImVec4( 0.18f, 0.18f, 0.18f, 1.00f );
	style->Colors[ ImGuiCol_Separator ] = ImVec4( 0.22f, 0.22f, 0.22f, 0.50f );
	style->Colors[ ImGuiCol_SeparatorHovered ] = ImVec4( 0.54f, 0.54f, 0.54f, 1.00f );
	style->Colors[ ImGuiCol_Tab ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	style->Colors[ ImGuiCol_TabHovered ] = ImVec4( 0.40f, 0.40f, 0.40f, 0.83f );
	style->Colors[ ImGuiCol_TabActive ] = ImVec4( 0.18f, 0.18f, 0.18f, 1.00f );
	style->Colors[ ImGuiCol_TextDisabled ] = ImVec4( 0.50f, 0.50f, 0.50f, 1.00f );
	style->Colors[ ImGuiCol_Border ] = ImVec4( 0.43f, 0.43f, 0.50f, 0.50f );
	style->Colors[ ImGuiCol_BorderShadow ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	style->Colors[ ImGuiCol_FrameBg ] = ImVec4( 0.25f, 0.25f, 0.25f, 1.00f );
	style->Colors[ ImGuiCol_FrameBgHovered ] = ImVec4( 0.38f, 0.38f, 0.38f, 1.00f );
	style->Colors[ ImGuiCol_FrameBgActive ] = ImVec4( 0.67f, 0.67f, 0.67f, 0.39f );
	style->Colors[ ImGuiCol_TitleBg ] = ImVec4( 0.08f, 0.08f, 0.09f, 1.00f );
	style->Colors[ ImGuiCol_TitleBgActive ] = ImVec4( 0.08f, 0.08f, 0.09f, 1.00f );
	style->Colors[ ImGuiCol_TitleBgCollapsed ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.51f );
	style->Colors[ ImGuiCol_ScrollbarBg ] = ImVec4( 0.02f, 0.02f, 0.02f, 0.53f );
	style->Colors[ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 0.41f, 0.41f, 0.41f, 1.00f );
	style->Colors[ ImGuiCol_ScrollbarGrabActive ] = ImVec4( 0.51f, 0.51f, 0.51f, 1.00f );
	style->Colors[ ImGuiCol_CheckMark ] = ImVec4( 0.11f, 0.64f, 0.92f, 1.00f );
	style->Colors[ ImGuiCol_SliderGrab ] = ImVec4( 0.11f, 0.64f, 0.92f, 1.00f );
	style->Colors[ ImGuiCol_SliderGrabActive ] = ImVec4( 0.08f, 0.50f, 0.72f, 1.00f );
	style->Colors[ ImGuiCol_ButtonActive ] = ImVec4( 0.67f, 0.67f, 0.67f, 0.39f );
	style->Colors[ ImGuiCol_Header ] = ImVec4( 0.22f, 0.22f, 0.22f, 1.00f );
	style->Colors[ ImGuiCol_HeaderHovered ] = ImVec4( 0.25f, 0.25f, 0.25f, 1.00f );
	style->Colors[ ImGuiCol_HeaderActive ] = ImVec4( 0.67f, 0.67f, 0.67f, 0.39f );
	style->Colors[ ImGuiCol_ResizeGrip ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	style->Colors[ ImGuiCol_ResizeGripHovered ] = ImVec4( 0.29f, 0.30f, 0.31f, 0.67f );
	style->Colors[ ImGuiCol_ResizeGripActive ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.95f );
	style->Colors[ ImGuiCol_TabUnfocused ] = ImVec4( 0.08f, 0.08f, 0.09f, 1.00f );
	style->Colors[ ImGuiCol_TabUnfocusedActive ] = ImVec4( 0.13f, 0.14f, 0.15f, 1.00f );
	style->Colors[ ImGuiCol_DockingPreview ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.70f );
	style->Colors[ ImGuiCol_DockingEmptyBg ] = ImVec4( 0.20f, 0.20f, 0.20f, 1.00f );
	style->Colors[ ImGuiCol_PlotLines ] = ImVec4( 0.61f, 0.61f, 0.61f, 1.00f );
	style->Colors[ ImGuiCol_PlotLinesHovered ] = ImVec4( 1.00f, 0.43f, 0.35f, 1.00f );
	style->Colors[ ImGuiCol_PlotHistogram ] = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
	style->Colors[ ImGuiCol_PlotHistogramHovered ] = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	style->Colors[ ImGuiCol_TextSelectedBg ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.35f );
	style->Colors[ ImGuiCol_DragDropTarget ] = ImVec4( 0.11f, 0.64f, 0.92f, 1.00f );
	style->Colors[ ImGuiCol_NavHighlight ] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
	style->Colors[ ImGuiCol_NavWindowingHighlight ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.70f );
	style->Colors[ ImGuiCol_NavWindowingDimBg ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.20f );
	style->Colors[ ImGuiCol_ModalWindowDimBg ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );
	style->GrabRounding = style->FrameRounding = 2.3f;
}


// Forward declarations
union Vec2;
union Vec4;
struct App_s;
struct UI_s;
struct FSRecord;
struct FSRecordList;
struct FSTab;
struct FSTabList;
struct Everything;
struct FSRecord;

// Types
enum struct FSRecordType_e
{
	Volume,
	Folder,
	File
};

enum struct FSPathElement_e
{
	BrowserRoot,
	Volume,
	Folder
};

union Vec2
{
	struct { int x, y; };
	struct { int w, h; };
};

union Vec4
{
	struct { int x, y, w, h; };
	struct { int r, g, b, a; };
};

typedef Vec4 Color;

struct App_s
{
	int win_w = 800;
	int win_h = 600;
	bool running = true;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	ImGuiIO* imgui_io;
	Color color_bg = { 200, 100, 100, 255 };
	ImFont* font;
	ImFont* icon_font;

	void Init();
	void ProcessEvents();
	void BeginFrame();
	void Render();
	void ShutDown();
} App;

struct Util_s
{
	std::string Util_s::ConvertWideToANSI( const std::wstring& wstr );
	std::wstring Util_s::ConvertAnsiToWide( const std::string& str );
	std::string ConvertWideToUtf8( const std::wstring& wstr );
	std::wstring ConvertUtf8ToWide( const std::string& str );
} Util;

struct ToolBarButton
{
	const char* btn_char;
	const char* tooltip;
	bool is_separator = false;

	ToolBarButton( const char* btn_char, const char* tooltip, Array<ToolBarButton*>* toolbar, bool is_separator = false );
};

struct UI_s
{
	ImGuiWindowFlags ds_window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;
	ImGuiWindowFlags fs_window_flags = 0; /*ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;*/
	ImGuiWindowFlags properties_window_flags = 0; /*ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;*/
	ImGuiWindowFlags preview_window_flags = 0; /*ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;*/
	ImGuiTabBarFlags fs_tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable; //  | ImGuiTabBarFlags_Reorderable
	ImGuiTableFlags fs_table_flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_Sortable;
	Array<ToolBarButton*> toolbar_buttons;
	Array<ToolBarButton*> main_toolbar;
	Array<ToolBarButton*> navigation_toolbar;

	void BeginDockSpace();
	void EndDockSpace();
	void RenderFSWindow();
	void RenderPreviewWindow();
	void RenderPropertiesWindow();
	void RenderTable();
	void RenderMenu();
	void RenderToolBar( Array<ToolBarButton*> toolbar );
	void RenderNavigationBar();
	void RenderBreadCrumb();
	void RenderFilter();
} UI;

struct Everything
{
	DWORD request_flags = EVERYTHING_REQUEST_FILE_NAME | EVERYTHING_REQUEST_PATH | EVERYTHING_REQUEST_SIZE | EVERYTHING_REQUEST_FULL_PATH_AND_FILE_NAME;
	std::string search = "";
};

struct FSRecord
{
	char* name;
	LARGE_INTEGER size;
	bool selected = false;
	FSRecordType_e type;
};

struct FSPath
{
	std::string volume = "";
	Array<std::string*> folder;
};

struct FSTab
{
	std::string label = "This PC";
	char* filter;
	int num_columns = 2; // NOTE temp, default should be configurable and each tab should remember its visble columns
	bool opened = true;
	Array<FSRecord*> records;
	FSPath path_composed;

	FSTab();
	void PathAddVolume( std::string volume_name );
	void PathAddFolder( std::string* folder_name );
	void Populate();
};

struct FSTabList_s
{
	int active_tab_index = 0;
	Array<FSTab*> tabs;
} FSTabList;

struct Settings_s
{
	bool show_menubar;
	bool show_toolbar;
	bool show_navigation_bar;

	void Read();
	void Write();
	void SetDefaults();
} Settings;





// 


// Load Fonts
// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
// - Read 'docs/FONTS.md' for more instructions and details.
// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
// io.Fonts->AddFontDefault();
// io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
// io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
// io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
// io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
// ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
// IM_ASSERT(font != NULL);


// Poll and handle events (inputs, window resize, etc.)
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.