#pragma once

#include "app.h"

void App_s::Init()
{
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0 )
	{
		printf( "Error: %s\n", SDL_GetError() );
		return;
	}

	this->window = SDL_CreateWindow( "Explorer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->win_w, this->win_h, SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI );
	this->renderer = SDL_CreateRenderer( this->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED );

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	this->imgui_io = &ImGui::GetIO();
	this->imgui_io->ConfigFlags |= ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForSDLRenderer( this->window, this->renderer );
	ImGui_ImplSDLRenderer_Init( this->renderer );

	FSRCTabs.tabs.Reserve( 1 );

	FSRecordList* fsrc = new FSRecordList( "This PC", 10 );
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
		// if (this->event.type == SDL_WINDOWEVENT && this->event.window.event == SDL_WINDOWEVENT_CLOSE && this->event.window.windowID == SDL_GetWindowID(this->window))
		// {
		// 	this->running = true;
		// }
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