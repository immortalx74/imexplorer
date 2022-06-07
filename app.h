#pragma once

#include "external/imgui/imgui.h"
#include "external/imgui/imgui_impl_sdl.h"
#include "external/imgui/imgui_impl_sdlrenderer.h"
#include <stdio.h>
#include "external/SDL2/include/SDL.h"
#include "external/everything/include/Everything.h"
#include "container.h"
#include <iostream>

// Forward declarations
union Vec2;
union Vec4;
struct App_s;
struct UI_s;
struct FSRecord;
struct FSRecordCollection;

// Types
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
	int win_w = 1200;
	int win_h = 800;
	bool running = true;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
	ImGuiIO* imgui_io;
	Color color_bg = {200, 100, 100, 255};

	void Init();
	void ProcessEvents();
	void BeginFrame();
	void Render();
	void ShutDown();
} App;

struct UI_s
{
	void BeginDockSpace();
	void EndDockSpace();
	void FileListWindow();
	void PreviewWindow();
	void PropertiesWindow();
} UI;

struct FSRecord
{
	char* name;
	bool is_folder;
	int size;
};

struct FSRecordCollection
{
	Array<FSRecord*> fs_records;
	std::string label;
	std::string path;
	std::string filter;
	bool opened = true;

	FSRecordCollection(std::string label, size_t init_capacity);
};

struct FSRCTabs_s
{
	Array<FSRecordCollection*> tabs;
} FSRCTabs;

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