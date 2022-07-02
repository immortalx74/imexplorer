#pragma once

#include "app.h"

void App_s::Init()
{
	SetProcessDpiAwarenessContext( DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE );
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );
	IMG_Init( IMG_INIT_PNG );
	this->window = SDL_CreateWindow( "ImExplorer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->win_w, this->win_h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
	this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED );
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer( this->window, this->renderer );
	ImGui_ImplSDLRenderer_Init( this->renderer );

	// Get dpi
	SDL_SysWMinfo wmInfo;
	SDL_VERSION( &wmInfo.version );
	SDL_GetWindowWMInfo( window, &wmInfo );
	HWND hwnd = wmInfo.info.win.window;
	UINT dpi_pixels = GetDpiForWindow( hwnd );
	this->dpi_scale = ( float )dpi_pixels / 96.0f;

	// Fonts
	this->imgui_io = &ImGui::GetIO();
	ImFontGlyphRangesBuilder builder;
	static const ImWchar ranges[] = { 0x20, 0xFFFF, 0, };
	builder.AddRanges( ranges );
	App.font = this->imgui_io->Fonts->AddFontFromFileTTF( "res/DejaVuSansMono.ttf", 14.0f * this->dpi_scale, NULL, ranges );
	App.icon_font = this->imgui_io->Fonts->AddFontFromFileTTF( "res/icons.ttf", 14.0f * this->dpi_scale );
	this->imgui_io->Fonts->Build();

	// Misc
	this->imgui_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_NavEnableKeyboard;
	App.icon_tex = IMG_LoadTexture( this->renderer, "res/file_icons.png" );
	SDL_QueryTexture( App.icon_tex, NULL, NULL, &App.icon_tex_x, &App.icon_tex_y );
	FileIcons.Init();
	Settings.Read();
	this->SetColors();
	FSTab* first_tab = new FSTab();

	// Init toolbar
	ToolBarButton* btn;
	btn = new ToolBarButton( "h", "New", &UI.navigation_toolbar, ToolBarButtonID_e::NavigationToolBar_New );
	btn = new ToolBarButton( "n", "Separator", &UI.navigation_toolbar, ToolBarButtonID_e::Separator, true );
	btn = new ToolBarButton( "a", "Up", &UI.navigation_toolbar, ToolBarButtonID_e::NavigationToolBar_Up );
	btn = new ToolBarButton( "b", "Previous", &UI.navigation_toolbar, ToolBarButtonID_e::NavigationToolBar_Previous );
	btn = new ToolBarButton( "c", "Next", &UI.navigation_toolbar, ToolBarButtonID_e::NavigationToolBar_Next );
	btn = new ToolBarButton( "d", "Cut", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_Cut );
	btn = new ToolBarButton( "e", "Copy", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_Copy );
	btn = new ToolBarButton( "f", "Paste", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_Paste );
	btn = new ToolBarButton( "o", "Rename", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_Rename );
	btn = new ToolBarButton( "g", "Delete", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_Delete );
	btn = new ToolBarButton( "n", "Separator", &UI.main_toolbar, ToolBarButtonID_e::Separator, true );
	btn = new ToolBarButton( "i", "View", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_View );
	btn = new ToolBarButton( "k", "Sort", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_Sort );
	btn = new ToolBarButton( "j", "Search", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_Search );
	btn = new ToolBarButton( "m", "Properties", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_Properties );
	btn = new ToolBarButton( "l", "Settings", &UI.main_toolbar, ToolBarButtonID_e::MainToolBar_Settings );
}

void App_s::ProcessEvents()
{
	while ( SDL_PollEvent( &this->event ) )
	{
		ImGui_ImplSDL2_ProcessEvent( &this->event );
		if ( this->event.type == SDL_QUIT )
		{
			this->running = false;
		}
		if ( this->event.type == SDL_WINDOWEVENT && this->event.window.event == SDL_WINDOWEVENT_RESIZED )
		{
			SDL_GetWindowSize( this->window, &this->win_w, &this->win_h );

			SDL_SysWMinfo wmInfo;
			SDL_VERSION( &wmInfo.version );
			SDL_GetWindowWMInfo( window, &wmInfo );
			HWND hwnd = wmInfo.info.win.window;
			UINT dpi_pixels = GetDpiForWindow( hwnd );
			this->dpi_scale = ( float )dpi_pixels / 96.0f;
			// TODO: Handle this properly. Both the UI & fonts should scale when Windows display scale has changed.
		}
	}

	ImGuiModFlags modifiers = 0;

	if ( ImGui::IsKeyDown( ImGuiKey_ModCtrl ) )
	{
		modifiers |= ImGuiModFlags_Ctrl;
	}
	if ( ImGui::IsKeyDown( ImGuiKey_ModShift ) )
	{
		modifiers |= ImGuiModFlags_Shift;
	}

	if ( modifiers & ImGuiModFlags_Ctrl && ImGui::IsKeyPressed( ImGuiKey_A ) )
	{
		std::cout << "ctrl+a" << std::endl;
	}
	else if ( modifiers & ImGuiModFlags_Shift && ImGui::IsKeyPressed( ImGuiKey_A ) )
	{
		std::cout << "shift+a" << std::endl;
	}
	else if ( modifiers & ImGuiModFlags_Ctrl | ImGuiModFlags_Shift && ImGui::IsKeyPressed( ImGuiKey_A ) )
	{
		std::cout << "shift+ctrl+a" << std::endl;
	}
	else if ( modifiers == 0 && ImGui::IsKeyPressed( ImGuiKey_A ) )
	{
		std::cout << "a" << std::endl;
	}
}

void App_s::BeginFrame()
{
	ImGui_ImplSDLRenderer_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
}

void App_s::Render()
{
	ImGui::Render();
	SDL_SetRenderDrawColor( this->renderer, 0, 0, 0, 0 );
	SDL_RenderClear( this->renderer );
	ImGui_ImplSDLRenderer_RenderDrawData( ImGui::GetDrawData() );
	SDL_RenderPresent( this->renderer );
}

void App_s::ShutDown()
{
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_DestroyRenderer( this->renderer );
	SDL_DestroyWindow( this->window );
	IMG_Quit();
	SDL_Quit();
}

void App_s::SetColors()
{
	ImGuiStyle* style = &ImGui::GetStyle();
	style->ScaleAllSizes( this->dpi_scale );
	style->CellPadding = ImVec2( 10.0f, 0.0f );
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ ImGuiCol_Text ] = ImVec4( 0.85f, 0.85f, 0.85f, 1.00f );
	colors[ ImGuiCol_TextDisabled ] = ImVec4( 0.50f, 0.50f, 0.50f, 1.00f );
	colors[ ImGuiCol_WindowBg ] = ImVec4( 0.09f, 0.09f, 0.09f, 1.00f );
	colors[ ImGuiCol_ChildBg ] = ImVec4( 0.04f, 0.04f, 0.04f, 1.00f );
	colors[ ImGuiCol_PopupBg ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	colors[ ImGuiCol_Border ] = ImVec4( 0.43f, 0.43f, 0.50f, 0.50f );
	colors[ ImGuiCol_BorderShadow ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_FrameBg ] = ImVec4( 0.25f, 0.25f, 0.25f, 1.00f );
	colors[ ImGuiCol_FrameBgHovered ] = ImVec4( 0.38f, 0.38f, 0.38f, 1.00f );
	colors[ ImGuiCol_FrameBgActive ] = ImVec4( 0.67f, 0.67f, 0.67f, 0.39f );
	colors[ ImGuiCol_TitleBg ] = ImVec4( 0.08f, 0.08f, 0.09f, 1.00f );
	colors[ ImGuiCol_TitleBgActive ] = ImVec4( 0.08f, 0.08f, 0.09f, 1.00f );
	colors[ ImGuiCol_TitleBgCollapsed ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.51f );
	colors[ ImGuiCol_MenuBarBg ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	colors[ ImGuiCol_ScrollbarBg ] = ImVec4( 0.02f, 0.02f, 0.02f, 0.53f );
	colors[ ImGuiCol_ScrollbarGrab ] = ImVec4( 0.24f, 0.24f, 0.24f, 1.00f );
	colors[ ImGuiCol_ScrollbarGrabHovered ] = ImVec4( 0.41f, 0.41f, 0.41f, 1.00f );
	colors[ ImGuiCol_ScrollbarGrabActive ] = ImVec4( 0.51f, 0.51f, 0.51f, 1.00f );
	colors[ ImGuiCol_CheckMark ] = ImVec4( 0.11f, 0.64f, 0.92f, 1.00f );
	colors[ ImGuiCol_SliderGrab ] = ImVec4( 0.11f, 0.64f, 0.92f, 1.00f );
	colors[ ImGuiCol_SliderGrabActive ] = ImVec4( 0.08f, 0.50f, 0.72f, 1.00f );
	colors[ ImGuiCol_Button ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	colors[ ImGuiCol_ButtonHovered ] = ImVec4( 0.18f, 0.18f, 0.18f, 1.00f );
	colors[ ImGuiCol_ButtonActive ] = ImVec4( 0.67f, 0.67f, 0.67f, 0.39f );
	colors[ ImGuiCol_Header ] = ImVec4( 0.22f, 0.22f, 0.22f, 1.00f );
	colors[ ImGuiCol_HeaderHovered ] = ImVec4( 0.25f, 0.25f, 0.25f, 1.00f );
	colors[ ImGuiCol_HeaderActive ] = ImVec4( 0.67f, 0.67f, 0.67f, 0.39f );
	colors[ ImGuiCol_Separator ] = ImVec4( 0.22f, 0.22f, 0.22f, 0.50f );
	colors[ ImGuiCol_SeparatorHovered ] = ImVec4( 0.54f, 0.54f, 0.54f, 1.00f );
	colors[ ImGuiCol_SeparatorActive ] = ImVec4( 0.10f, 0.40f, 0.75f, 1.00f );
	colors[ ImGuiCol_ResizeGrip ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_ResizeGripHovered ] = ImVec4( 0.29f, 0.30f, 0.31f, 0.67f );
	colors[ ImGuiCol_ResizeGripActive ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.95f );
	colors[ ImGuiCol_Tab ] = ImVec4( 0.00f, 0.00f, 0.00f, 1.00f );
	colors[ ImGuiCol_TabHovered ] = ImVec4( 0.40f, 0.40f, 0.40f, 0.83f );
	colors[ ImGuiCol_TabActive ] = ImVec4( 0.18f, 0.18f, 0.18f, 1.00f );
	colors[ ImGuiCol_TabUnfocused ] = ImVec4( 0.08f, 0.08f, 0.09f, 1.00f );
	colors[ ImGuiCol_TabUnfocusedActive ] = ImVec4( 0.13f, 0.14f, 0.15f, 1.00f );
	colors[ ImGuiCol_DockingPreview ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.70f );
	colors[ ImGuiCol_DockingEmptyBg ] = ImVec4( 0.20f, 0.20f, 0.20f, 1.00f );
	colors[ ImGuiCol_PlotLines ] = ImVec4( 0.61f, 0.61f, 0.61f, 1.00f );
	colors[ ImGuiCol_PlotLinesHovered ] = ImVec4( 1.00f, 0.43f, 0.35f, 1.00f );
	colors[ ImGuiCol_PlotHistogram ] = ImVec4( 0.90f, 0.70f, 0.00f, 1.00f );
	colors[ ImGuiCol_PlotHistogramHovered ] = ImVec4( 1.00f, 0.60f, 0.00f, 1.00f );
	colors[ ImGuiCol_TableHeaderBg ] = ImVec4( 0.19f, 0.19f, 0.20f, 1.00f );
	colors[ ImGuiCol_TableBorderStrong ] = ImVec4( 0.31f, 0.31f, 0.35f, 1.00f );
	colors[ ImGuiCol_TableBorderLight ] = ImVec4( 0.23f, 0.23f, 0.25f, 1.00f );
	colors[ ImGuiCol_TableRowBg ] = ImVec4( 0.00f, 0.00f, 0.00f, 0.00f );
	colors[ ImGuiCol_TableRowBgAlt ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.06f );
	colors[ ImGuiCol_TextSelectedBg ] = ImVec4( 0.26f, 0.59f, 0.98f, 0.35f );
	colors[ ImGuiCol_DragDropTarget ] = ImVec4( 0.11f, 0.64f, 0.92f, 1.00f );
	colors[ ImGuiCol_NavHighlight ] = ImVec4( 0.26f, 0.59f, 0.98f, 1.00f );
	colors[ ImGuiCol_NavWindowingHighlight ] = ImVec4( 1.00f, 1.00f, 1.00f, 0.70f );
	colors[ ImGuiCol_NavWindowingDimBg ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.20f );
	colors[ ImGuiCol_ModalWindowDimBg ] = ImVec4( 0.80f, 0.80f, 0.80f, 0.35f );
}