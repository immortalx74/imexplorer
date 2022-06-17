#pragma once

#include "app.h"

void UI_s::BeginDockSpace()
{
	ImGui::PushStyleVar( ImGuiStyleVar_WindowRounding, 0.0f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0.0f );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0.0f, 0.0f ) );

	ImGui::SetNextWindowPos( ImVec2( 0, 0 ) );
	ImGui::SetNextWindowSize( ImVec2( App.win_w, App.win_h ) );
	ImGui::Begin( "ds_window", NULL, UI.ds_window_flags );

	if ( Settings.show_menubar )
	{
		UI.RenderMenu();
	}
	if ( Settings.show_toolbar )
	{
		UI.RenderToolBar( UI.main_toolbar );
		ImGui::Separator();
	}
	if ( Settings.show_navigation_bar )
	{
		UI.RenderToolBar( UI.navigation_toolbar );
		ImGui::SameLine();
		UI.RenderBreadCrumb();
		ImGui::SameLine();
		UI.RenderFilter();
		ImGui::Separator();
	}

	ImGui::DockSpace( ImGui::GetID( "ds_window" ), ImVec2( 0, 0 ), ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoTabBar );
	ImGui::PopStyleVar( 3 );
}

void UI_s::EndDockSpace()
{
	ImGui::End();
}

void UI_s::RenderFSWindow()
{
	ImGui::Begin( "fs_window", NULL, UI.fs_window_flags );

	if ( ImGui::BeginTabBar( "fs_tab_bar", UI.fs_tab_bar_flags ) )
	{
		for ( int i = 0; i < FSTabList.tabs.length; ++i )
		{
			if ( ImGui::BeginTabItem( ( FSTabList.tabs[ i ]->label + "###" + std::to_string( i ) ).c_str(), &FSTabList.tabs[ i ]->opened ) )
			{
				FSTabList.active_tab_index = i;

				if ( ImGui::BeginTable( ( "fs_table##" + std::to_string( i ) ).c_str(), FSTabList.tabs[ i ]->num_columns, fs_table_flags ) )
				{
					UI.RenderTable();
					ImGui::EndTable();
				}
				ImGui::EndTabItem();
			}
		}

		if ( ImGui::TabItemButton( "+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip ) )
		{
			FSTab* tab = new FSTab();
			FSTabList.active_tab_index = FSTabList.tabs.length - 1;
		}

		ImGui::EndTabBar();
	}
	ImGui::End();
}

void UI_s::RenderPreviewWindow()
{
	ImGui::Begin( "preview_window", NULL, UI.preview_window_flags );
	ImGui::End();
}

void UI_s::RenderPropertiesWindow()
{
	ImGui::Begin( "properties_window", NULL, UI.properties_window_flags );
	ImGui::End();
}

void UI_s::RenderTable()
{
	int record_count = FSTabList.tabs[ FSTabList.active_tab_index ]->records.length;
	ImGui::TableSetupColumn( "Name" );
	ImGui::TableSetupColumn( "Size" );
	ImGui::TableSetupScrollFreeze( 0, 1 );
	ImGui::TableHeadersRow();

	for ( int i = 0; i < record_count; i++ )
	{
		ImGui::TableNextRow();

		// column name
		ImGui::TableSetColumnIndex( 0 );
		FSRecord* record = FSTabList.tabs[ FSTabList.active_tab_index ]->records[ i ];

		if ( ImGui::Selectable( record->name, record->selected, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns ) )
		{
			if ( ImGui::IsMouseDoubleClicked( 0 ) )
			{
				if ( record->type == FSRecordType_e::Volume )
				{
					FSTabList.tabs[ FSTabList.active_tab_index ]->PathAddVolume( record->name );
				}
				else if ( record->type == FSRecordType_e::Folder )
				{
					std::string* temp = new std::string( "blah" );
					*temp = record->name;
					// FSTabList.tabs[ FSTabList.active_tab_index ]->PathAddFolder( record->name );
					FSTabList.tabs[ FSTabList.active_tab_index ]->PathAddFolder( temp );
					return;
				}
			}
			// if ( !ImGui::GetIO().KeyCtrl )
			// {
			// 	memset( selected, 0, sizeof( selected ) );
			// }
			// selected[ tab_index ] = !selected[ i ];
		}

		// column size
		ImGui::TableSetColumnIndex( 1 );
		if ( record->type == FSRecordType_e::File )
		{
			ImGui::Text( std::to_string( record->size.LowPart + record->size.HighPart ).c_str() );
		}
	}
}

void UI_s::RenderMenu()
{
	if ( ImGui::BeginMenuBar() )
	{

		if ( ImGui::BeginMenu( "New" ) )
		{
			if ( ImGui::MenuItem( "Folder" ) )
			{

			}
			if ( ImGui::MenuItem( "Shortcut" ) )
			{

			}
			if ( ImGui::MenuItem( "Text Document" ) )
			{

			}
			ImGui::EndMenu();
		}
		if ( ImGui::BeginMenu( "Edit" ) )
		{
			if ( ImGui::MenuItem( "Cut" ) )
			{

			}
			if ( ImGui::MenuItem( "Copy" ) )
			{

			}
			if ( ImGui::MenuItem( "Paste" ) )
			{

			}
			if ( ImGui::MenuItem( "Rename" ) )
			{

			}
			if ( ImGui::MenuItem( "Delete" ) )
			{

			}
			ImGui::EndMenu();
		}
		if ( ImGui::BeginMenu( "View" ) )
		{
			if ( ImGui::MenuItem( "Details" ) )
			{

			}
			if ( ImGui::MenuItem( "Small Icons" ) )
			{

			}
			if ( ImGui::MenuItem( "Large Icons" ) )
			{

			}
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void UI_s::RenderToolBar( Array<ToolBarButton*> toolbar )
{
	for ( int i = 0; i < toolbar.length; ++i )
	{
		ImGui::PushFont( App.icon_font );

		if ( toolbar[ i ]->is_separator )
		{
			ImGui::BeginDisabled();
			ImGui::PushStyleColor( ImGuiCol_Button, ImVec4( 0, 0, 0, 0 ) );
			ImGui::PushStyleColor( ImGuiCol_Text, ImVec4( 1, 1, 1, 0.3 ) );
		}
		if ( ImGui::Button( toolbar[ i ]->btn_char ) )
		{

		}
		if ( toolbar[ i ]->is_separator )
		{
			ImGui::EndDisabled();
			ImGui::PopStyleColor( 2 );
		}
		ImGui::PopFont();

		if ( ImGui::IsItemHovered() )
		{
			ImGui::BeginTooltip();
			ImGui::Text( toolbar[ i ]->tooltip );
			ImGui::EndTooltip();
		}

		if ( i < toolbar.length - 1 )
		{
			ImGui::SameLine();
		}
	}
}

void UI_s::RenderBreadCrumb()
{
	ImGui::PushStyleVar( ImGuiStyleVar_ItemSpacing, ImVec2( 0, 0 ) );
	ImGui::PushStyleColor( ImGuiCol_Button, ImVec4( 0, 0, 0, 0 ) );

	ImGui::SmallButton( ( "This PC##adada" ) );

	FSPath cur_path = FSTabList.tabs[ FSTabList.active_tab_index ]->path_composed;

	if ( cur_path.volume != "" )
	{
		ImGui::SameLine();
		ImGui::Text( ">" );
		ImGui::SameLine();
		ImGui::Button( cur_path.volume.c_str() );
	}

	int len = FSTabList.tabs[ FSTabList.active_tab_index ]->path_composed.folder.length;
	if ( len > 0 )
	{
		for ( int i = 0; i < len; ++i )
		{
			ImGui::SameLine();
			ImGui::Text( ">" );
			ImGui::SameLine();
			ImGui::Button( cur_path.folder[ i ]->c_str() );
		}
	}
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void UI_s::RenderFilter()
{
	static char* buf = ( char* )malloc( 100 );
	memset( buf, 0, 100 );
	// ImGui::PushItemWidth( ImGui::GetWindowWidth() - 114 );
	ImGui::PushItemWidth( ImGui::GetWindowWidth() - ImGui::GetCursorPosX() - 2 );
	// ImGui::InputText( "##type here", FSTabList.tabs[ FSTabList.active_tab_index ]->filter, 100 );
	ImGui::InputText( "##type here", buf, 100 );
	ImGui::PopItemWidth();
}

ToolBarButton::ToolBarButton( const char* btn_char, const char* tooltip, Array<ToolBarButton*>* toolbar, bool is_separator )
{
	this->btn_char = btn_char;
	this->tooltip = tooltip;
	this->is_separator = is_separator;
	toolbar->Push( this );
}