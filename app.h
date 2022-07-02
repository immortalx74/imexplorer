#pragma once

// #define STRICT_TYPED_ITEMIDS
#define IMGUI_ENABLE_FREETYPE
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
#include "external/SDL2/include/SDL_syswm.h"
#include <Shlobj.h>
#include <atlbase.h>
#include <atlstr.h>
#include <sstream>
#include <iomanip>

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
	int win_w = 1200;
	int win_h = 800;
	float dpi_scale;
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
	std::string* gstr;

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
	std::string FileSizeToStringKB( LARGE_INTEGER n);
	std::string FileSizeToString( LARGE_INTEGER n);
	std::string SystemTimeToString( SYSTEMTIME st );
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
	ImGuiWindowFlags status_bar_window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse; /*ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;*/
	ImGuiWindowFlags preview_window_flags = 0; /*ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;*/
	ImGuiTabBarFlags fs_tab_bar_flags = ImGuiTabBarFlags_AutoSelectNewTabs | ImGuiTabBarFlags_Reorderable; //  | ImGuiTabBarFlags_Reorderable
	ImGuiTableFlags fs_table_flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Sortable;
	Array<ToolBarButton*> main_toolbar;
	Array<ToolBarButton*> navigation_toolbar;

	void RenderDebugWindow();
	void BeginDockSpace();
	void EndDockSpace();
	void RenderFSWindow();
	void RenderPreviewWindow();
	void RenderStatusBarWindow();
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
	struct { LARGE_INTEGER li; std::string text; } size;
	struct { SYSTEMTIME systemtime; std::string text; } date_created;
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
	~FSTab();
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