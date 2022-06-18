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

	UI.RenderSettingsWindow();

	if ( Settings.show_menubar )
	{
		UI.ds_window_flags |= ImGuiWindowFlags_MenuBar;
		UI.RenderMenu();
	}
	else
	{
		UI.ds_window_flags &= ~ImGuiWindowFlags_MenuBar;
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

	ImGui::DockSpace( ImGui::GetID( "main##ds_window" ), ImVec2( 0, 0 ), ImGuiDockNodeFlags_AutoHideTabBar | ImGuiDockNodeFlags_NoTabBar );
	ImGui::PopStyleVar( 3 );
}

void UI_s::EndDockSpace()
{
	ImGui::End();
}

void UI_s::RenderFSWindow()
{
	ImGui::Begin( "file list##fs_window", NULL, UI.fs_window_flags );

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
	ImGui::Begin( "file preview##preview_window", NULL, UI.preview_window_flags );
	ImGui::End();
}

void UI_s::RenderPropertiesWindow()
{
	ImGui::Begin( "file properties##properties_window", NULL, UI.properties_window_flags );
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
					std::string* temp = new std::string( record->name ); // NOTE these are never deleted.
					FSTabList.tabs[ FSTabList.active_tab_index ]->PathAddFolder( temp );
					return; // NOTE Early return. Previous call changes the record_count.
				}
				else if ( record->type == FSRecordType_e::File )
				{
					std::string vol = FSTabList.tabs[ FSTabList.active_tab_index ]->path.volume;
					std::string path = "\\";

					for ( int i = 0; i < FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder.length; ++i )
					{
						path += *FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder[ i ];
						path += "\\";
					}
					std::string fname = record->name;
					std::string paf = vol + path + fname;
					std::cout << paf << std::endl;

					ShellExecuteW( GetDesktopWindow(), L"open", Util.ConvertUtf8ToWide( paf ).c_str(), 0, 0, SW_SHOW );
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
			toolbar[ i ]->OnClick( toolbar[ i ]->ID );
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
	ImGui::BeginChild( "breadcrumb_container", ImVec2( ImGui::GetWindowWidth() / 1.8f, 20 ), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse );

	ImGui::SetScrollX( ImGui::GetScrollMaxX() );

	int len = FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder.length;

	if ( ImGui::Button( ( "This PC##adada" ) ) )
	{
		FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveFolder( len );
		FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveVolume();
	}

	FSPath cur_path = FSTabList.tabs[ FSTabList.active_tab_index ]->path;

	if ( cur_path.volume != "" )
	{
		ImGui::SameLine();
		ImGui::Text( ">" );
		ImGui::SameLine();
		if ( ImGui::Button( cur_path.volume.c_str() ) )
		{
			FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveFolder( len );
		}
	}

	len = FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder.length;
	if ( len > 0 )
	{
		for ( int i = 0; i < len; ++i )
		{
			ImGui::SameLine();
			ImGui::Text( ">" );
			ImGui::SameLine();
			if ( ImGui::Button( cur_path.folder[ i ]->c_str() ) )
			{
				FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveFolder( len - i - 1 );
			}
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void UI_s::RenderFilter()
{
	static char* buf = ( char* )malloc( 100 );
	memset( buf, 0, 100 );
	ImGui::PushItemWidth( ImGui::GetWindowWidth() - ImGui::GetCursorPosX() - 2 );
	ImGui::InputText( "##type here", buf, 100 );
	ImGui::PopItemWidth();
}

void UI_s::RenderSettingsWindow()
{
	if ( ImGui::BeginPopupModal( "Settings##settings_window", NULL, ImGuiWindowFlags_AlwaysAutoResize ) )
	{
		ImGui::Checkbox( "Show menu##settings_window", &Settings.show_menubar );
		ImGui::Checkbox( "Show toolbar##settings_window", &Settings.show_toolbar );
		ImGui::Checkbox( "Show navigation bar##settings_window", &Settings.show_navigation_bar );
		ImGui::Checkbox( "Show preview pane##settings_window", &Settings.show_preview_pane );

		if ( ImGui::Button( "Reset to defaults##settings_window" ) )
		{
			Settings.SetDefaults();
		}
		ImGui::SameLine();
		if ( ImGui::Button( "Close##settings_window" ) )
		{
			Settings.Write();
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void UI_s::RenderDebugWindow()
{
	ImGui::Begin( "Debug Window" );
	ImGui::Text( std::to_string( App.win_w ).c_str() );
	ImGui::End();
}