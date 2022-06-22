#pragma once

#include "external/imgui/imgui.h"
#include "external/imgui/imgui_internal.h"
#include "external/imgui/imgui_impl_sdl.h"
#include "external/imgui/imgui_impl_sdlrenderer.h"
#include <stdio.h>
#include "external/SDL2/include/SDL.h"
#include "external/SDL2/include/SDL_image.h"
#include "external/everything/include/Everything.h"
#include "container.h"
#include <iostream>
#include <string>
#include <map>

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

enum struct ToolBarButtonID_e
{
	Separator,
	NavigationToolBar_New,
	NavigationToolBar_Up,
	NavigationToolBar_Previous,
	NavigationToolBar_Next,
	MainToolBar_Cut,
	MainToolBar_Copy,
	MainToolBar_Paste,
	MainToolBar_Rename,
	MainToolBar_Delete,
	MainToolBar_View,
	MainToolBar_Sort,
	MainToolBar_Search,
	MainToolBar_Properties,
	MainToolBar_Settings
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
	bool debug = false;
	bool demo = false;
	int win_w = 800;
	int win_h = 600;
	bool running = true;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	ImGuiIO* imgui_io;
	ImFont* font;
	ImFont* icon_font;
	SDL_Texture* icon_tex;
	ImVec2 icon_tex_size;
	int icon_tex_x;
	int icon_tex_y;

	void SetColors();
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
	void FileSizeToString( LARGE_INTEGER n, char** output );
	void SystemTimeToString( SYSTEMTIME st, char** output );
} Util;

struct ToolBarButton
{
	const char* btn_char;
	const char* tooltip;
	bool enabled = true;
	bool is_separator = false;
	ToolBarButtonID_e ID;

	ToolBarButton( const char* btn_char, const char* tooltip, Array<ToolBarButton*>* toolbar, ToolBarButtonID_e ID, bool is_separator = false );
	void OnClick( ToolBarButtonID_e ID );
};

struct UI_s
{
	ImGuiWindowFlags ds_window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus;
	ImGuiWindowFlags fs_window_flags = 0; /*ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;*/
	ImGuiWindowFlags properties_window_flags = 0; /*ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;*/
	ImGuiWindowFlags preview_window_flags = 0; /*ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;*/
	ImGuiTabBarFlags fs_tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable; //  | ImGuiTabBarFlags_Reorderable
	ImGuiTableFlags fs_table_flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_Sortable;
	Array<ToolBarButton*> main_toolbar;
	Array<ToolBarButton*> navigation_toolbar;

	void RenderDebugWindow();
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
	void RenderSettingsWindow();
	void SetScale( float size );
} UI;

struct Everything_s
{
	DWORD request_flags = EVERYTHING_REQUEST_FILE_NAME | EVERYTHING_REQUEST_PATH | EVERYTHING_REQUEST_SIZE | EVERYTHING_REQUEST_FULL_PATH_AND_FILE_NAME | EVERYTHING_REQUEST_DATE_CREATED | EVERYTHING_REQUEST_EXTENSION;
	std::string search = "";
} Everything;

struct FSRecord
{
	char* name;
	struct { LARGE_INTEGER li; char* text; } size;
	struct { SYSTEMTIME systemtime; char* text; } date_created;
	bool selected = false;
	FSRecordType_e type;
	int icon_idx;
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
	int num_columns = 3; // NOTE temp, default should be configurable and each tab should remember its visble columns
	bool opened = true;
	Array<FSRecord*> records;
	FSPath path;

	FSTab();
	void PathAddVolume( std::string volume_name );
	void PathAddFolder( std::string* folder_name );
	void PathRemoveVolume();
	void PathRemoveFolder( int count );
	void Populate();
};


struct FSTabList_s
{
	int active_tab_index = 0;
	Array<FSTab*> tabs;
} FSTabList;

struct Settings_s
{
	bool show_menubar = true;
	bool show_toolbar = true;
	bool show_navigation_bar = true;
	bool show_preview_pane;

	void Read();
	void Write();
	void SetDefaults();
} Settings;

struct FileIcons_s
{
	std::map<std::string, int> extensions;

	void Init();
} FileIcons;

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