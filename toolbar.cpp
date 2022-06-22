#pragma once

#include "app.h"

ToolBarButton::ToolBarButton( const char* btn_char, const char* tooltip, Array<ToolBarButton*>* toolbar, ToolBarButtonID_e ID, bool is_separator )
{
	this->btn_char = btn_char;
	this->tooltip = tooltip;
	this->ID = ID;
	this->is_separator = is_separator;
	toolbar->Push( this );
}

void ToolBarButton::OnClick( ToolBarButtonID_e ID )
{
	if ( ID == ToolBarButtonID_e::MainToolBar_Settings )
	{
		ImGui::OpenPopup( "Settings##settings_window" );
	}
	else if ( ID == ToolBarButtonID_e::NavigationToolBar_Previous )
	{
		if ( FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder.length == 0 )
		{
			FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveVolume();
		}

		FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveFolder( 1 );
	}
	else if ( ID == ToolBarButtonID_e::MainToolBar_Cut )
	{
		// ImGuiStyle* style = &ImGui::GetStyle();
		// UI.SetScale( 1.4f );
	}
}