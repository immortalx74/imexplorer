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
		// NOTE: This is temp. Prev/Next should navigate on history
		if ( FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder.length == 0 )
		{
			FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveVolume();
		}
		else
		{
			FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveFolder( 1 );
		}

	}
	else if ( ID == ToolBarButtonID_e::MainToolBar_Cut )
	{
		//NOTE Just some test
		// LPCWSTR fname = L"";
		// CopyFileW( fname, L"", FALSE );
	}
	else if ( ID == ToolBarButtonID_e::MainToolBar_Properties )
	{
		Array<std::string*> filenames;
		Util.GetSelectedRecordsFullFileNames( &filenames );
		int file_count = filenames.length;
		Util.DisplayMultiRecordProperties( filenames, file_count );

		for ( int i = 0; i < file_count; ++i )
		{
			delete filenames[ i ];
		}

		filenames.Destroy();
	}
}