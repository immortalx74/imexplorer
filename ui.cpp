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
			// Delete tab on close
			if ( !FSTabList.tabs[ i ]->opened )
			{
				if ( FSTabList.tabs.length == 1 )
				{
					FSTabList.tabs[ 0 ]->opened = true;
				}
				else
				{
					delete FSTabList.tabs[ i ];
					FSTabList.tabs.Erase( i );
					break;
				}
			}

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

void UI_s::RenderStatusBarWindow()
{
	ImGui::Begin( "status bar##status_bar_window", NULL, UI.status_bar_window_flags );

	int len = FSTabList.tabs[ FSTabList.active_tab_index ]->records.length;
	FSRecord* rec;
	LARGE_INTEGER total_size = { 0 };
	int selected_count = 0;

	for ( int i = 0; i < len; ++i )
	{
		rec = FSTabList.tabs[ FSTabList.active_tab_index ]->records[ i ];
		if ( rec->selected )
		{
			total_size.QuadPart += rec->size.li.QuadPart;
			selected_count++;
		}
	}

	std::string total_size_str = Util.FileSizeToString( total_size );
	ImGui::Text( std::to_string( len ).c_str() );
	ImGui::SameLine();
	ImGui::Text( "Items |" );
	ImGui::SameLine();
	ImGui::Text( std::to_string( selected_count ).c_str() );
	ImGui::SameLine();
	ImGui::Text( "Item(s) selected |" );
	ImGui::SameLine();
	ImGui::Text( total_size_str.c_str() );

	ImGui::SameLine();
	UI.RenderFilter();

	ImGui::End();
}

void UI_s::RenderTable()
{
	ImGui::TableSetupColumn( "Name", ImGuiTableColumnFlags_DefaultSort );
	ImGui::TableSetupColumn( "Size", ImGuiTableColumnFlags_DefaultSort );
	ImGui::TableSetupColumn( "Date Created", ImGuiTableColumnFlags_DefaultSort );
	ImGui::TableSetupScrollFreeze( 0, 1 );
	ImGui::TableHeadersRow();

	if ( ImGuiTableSortSpecs* specs = ImGui::TableGetSortSpecs() )
	{
		if ( specs->SpecsDirty )
		{
			// std::cout << "dirty" << std::endl;
		}
	}

	int record_count = FSTabList.tabs[ FSTabList.active_tab_index ]->records.length;

	for ( int i = 0; i < record_count; i++ )
	{
		ImGui::TableNextRow( ImGuiTableRowFlags_None, 22.0f );

		// extension icon
		ImGui::TableSetColumnIndex( 0 );
		FSRecord* record = FSTabList.tabs[ FSTabList.active_tab_index ]->records[ i ];

		int cell_x = record->icon_idx % 32;
		int cell_y = record->icon_idx / 32;
		ImVec2 uv0 = ImVec2( ( 64.0f * cell_x ) / ( float )App.icon_tex_x, ( 64.0f * cell_y ) / ( float )App.icon_tex_y );
		ImVec2 uv1 = ImVec2( ( ( 64.0f * cell_x ) + 64.0f ) / ( float )App.icon_tex_x, ( ( 64.0f * cell_y ) + 64.0f ) / ( float )App.icon_tex_y );
		ImGui::Image( App.icon_tex, ImVec2( 16, 16 ), uv0, uv1 );
		ImGui::SameLine();

		// column name
		if ( ImGui::Selectable( record->name, record->selected, ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns ) )
		{
			// Selection
			if ( ImGui::GetIO().KeyCtrl )
			{
				record->selected = !record->selected;
			}
			else
			{
				for ( int i = 0; i < record_count; ++i )
				{
					FSTabList.tabs[ FSTabList.active_tab_index ]->records[ i ]->selected = false;
				}

				record->selected = true;
			}

			if ( ImGui::IsMouseDoubleClicked( 0 ) )
			{
				if ( record->type == FSRecordType_e::Volume )
				{
					FSTabList.tabs[ FSTabList.active_tab_index ]->PathAddVolume( record->name );
					break; //Previous call calls Populate() which deletes current records.
				}
				else if ( record->type == FSRecordType_e::Folder )
				{
					std::string* rname = new std::string( record->name );
					FSTabList.tabs[ FSTabList.active_tab_index ]->PathAddFolder( rname );
					break; // Previous call changes the record_count.
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

					ShellExecuteW( GetDesktopWindow(), L"open", Util.ConvertUtf8ToWide( paf ).c_str(), 0, 0, SW_SHOW );
					// SHObjectProperties( NULL, SHOP_FILEPATH, Util.ConvertUtf8ToWide( paf ).c_str(), NULL );
				}
			}
		}

		// column size
		ImGui::TableSetColumnIndex( 1 );

		// Right align
		ImVec2 content_width = ImGui::GetContentRegionAvail();
		ImVec2 text_size = ImGui::CalcTextSize( record->size.text.c_str() );
		ImGui::SetCursorPosX( ImGui::GetCursorPosX() + content_width.x - text_size.x );

		if ( record->type == FSRecordType_e::File )
		{
			ImGui::Text( record->size.text.c_str() );
		}

		// column date created
		ImGui::TableSetColumnIndex( 2 );
		ImGui::Text( record->date_created.text.c_str() );
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

	ImGui::BeginChild( "breadcrumb_container", ImVec2( ImGui::GetWindowWidth() - ImGui::GetCursorPosX() - 10, ImGui::GetFrameHeight() ), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse );

	ImGui::SetScrollX( ImGui::GetScrollMaxX() );

	int len = FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder.length;

	if ( ImGui::Button( ( "This PC" ) ) )
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
				break; // Previous call changes len.
			}
		}
	}
	ImGui::EndChild();
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();
}

void UI_s::RenderFilter()
{
	ImGui::PushStyleVar( ImGuiStyleVar_FramePadding, ImVec2( 0.0f, 0.0f ) );
	ImGui::PushItemWidth( ImGui::GetWindowWidth() - ImGui::GetCursorPosX() - 10 );

	if ( ImGui::IsKeyDown( ImGuiKey_ModCtrl ) && ImGui::IsKeyPressed( ImGuiKey_F ) )
	{
		ImGui::SetKeyboardFocusHere();
	}

	if ( ImGui::InputTextWithHint( "##type here", "*filter results*", FSTabList.tabs[ FSTabList.active_tab_index ]->filter, 100 ) )
	{
		FSTabList.tabs[ FSTabList.active_tab_index ]->Populate();
	}

	ImGui::PopItemWidth();
	ImGui::PopStyleVar();
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
	ImGui::Text( std::to_string( FSTabList.active_tab_index ).c_str() );
	ImGui::End();
}

void UI_s::SetScale( float scale )
{
	ImFontGlyphRangesBuilder builder;
	static const ImWchar ranges[] = { 0x20, 0xFFFF, 0, };
	builder.AddRanges( ranges );
	App.font = App.imgui_io->Fonts->AddFontFromFileTTF( "res/DejaVuSansMono.ttf", 14.0f * scale, NULL, ranges );
	App.icon_font = App.imgui_io->Fonts->AddFontFromFileTTF( "res/icons.ttf", 14.0f * scale );
	App.imgui_io->Fonts->Build();

	ImGuiStyle* style = &ImGui::GetStyle();
	style->ScaleAllSizes( scale );
}