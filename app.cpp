#pragma once

#include "app.h"

void App_s::Init()
{
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );
	this->window = SDL_CreateWindow( "ImExplorer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->win_w, this->win_h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
	this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED );
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForSDLRenderer( this->window, this->renderer );
	ImGui_ImplSDLRenderer_Init( this->renderer );

	this->imgui_io = &ImGui::GetIO();
	ImFontGlyphRangesBuilder builder;
	static const ImWchar ranges[] = { 0x20, 0xFFFF, 0, };
	builder.AddRanges( ranges );
	App.font = this->imgui_io->Fonts->AddFontFromFileTTF( "res/DejaVuSansMono.ttf", 14, NULL, ranges );
	App.icon_font = this->imgui_io->Fonts->AddFontFromFileTTF( "res/icons.ttf", 14 );
	this->imgui_io->Fonts->Build();
	this->imgui_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_NavEnableKeyboard;

	Settings.Read();
	// Settings.Write();

	FSTab* first_tab = new FSTab();
	embraceTheDarkness();

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
		}
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
	SDL_SetRenderDrawColor( this->renderer, ( Uint8 )( this->color_bg.r ), ( Uint8 )( this->color_bg.g ), ( Uint8 )( this->color_bg.b ), ( Uint8 )( this->color_bg.a ) );
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
	SDL_Quit();
}