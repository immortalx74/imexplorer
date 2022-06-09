#pragma once

#include "app.h"

void UI_s::BeginDockSpace()
{
	ImGuiDockNodeFlags_AutoHideTabBar;
	ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	ImGui::SetNextWindowPos( ImVec2( 0, 0 ) );
	ImGui::SetNextWindowSize( ImVec2( App.win_w, App.win_h ) );
	ImGui::Begin( "dock_space", NULL, flags );
	ImGui::DockSpace( ImGui::GetID( "dock_space" ) );
}

void UI_s::EndDockSpace()
{
	ImGui::End();
}

void UI_s::FileListWindow()
{
	ImGui::Begin( "file_list_window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
	if ( ImGui::BeginTabBar( "main_tabbar", ImGuiTabBarFlags_Reorderable ) )
	{
		for ( int i = 0; i < FSRCTabs.tabs.length; i++ )
		{
			std::string tabid = FSRCTabs.tabs[ i ]->label + "##" + std::to_string( i );

			if ( ImGui::BeginTabItem( tabid.c_str(), &FSRCTabs.tabs[ i ]->opened ) )
			{
				if ( ImGui::Button( ( "Up##" + std::to_string( i ) ).c_str() ) )
				{
				}
				ImGui::SameLine();
				if ( ImGui::Button( "Prev" ) )
				{
				}
				ImGui::SameLine();
				if ( ImGui::Button( "Next" ) )
				{
				}

				char buf[ 100 ] = "type some text";
				ImGui::PushItemWidth( ImGui::GetWindowWidth() - 16 );
				ImGui::InputText( "##type here", buf, 100 );
				ImGui::PopItemWidth();


				DWORD result_len = Everything_GetNumResults();
				ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ScrollX | ImGuiTableFlags_ScrollY;
				static bool selected[ 1000 ];

				if ( ImGui::BeginTable( "my_table", 2, flags ) )
				{
					ImGui::TableSetupColumn( "Name" );
					ImGui::TableSetupColumn( "Size" );
					ImGui::TableSetupScrollFreeze( 0, 1 );
					ImGui::TableHeadersRow();

					for ( int row = 0; row < result_len; row++ )
					{
						ImGui::TableNextRow();

						// column name
						ImGui::TableSetColumnIndex( 0 );
						LPCSTR str = Everything_GetResultFileNameA( row );

						if ( ImGui::Selectable( str, selected[ row ], ImGuiSelectableFlags_AllowDoubleClick | ImGuiSelectableFlags_SpanAllColumns ) )
						{
							if ( ImGui::IsMouseDoubleClicked( 0 ) )
							{
								Everything_SetSearchA( "infolder:D:" );
								Everything_QueryA( TRUE );
								std::cout << row << std::endl;
							}
							if ( !ImGui::GetIO().KeyCtrl )
							{
								memset( selected, 0, sizeof( selected ) );
							}
							selected[ i ] = !selected[ row ];
						}

						// column size
						ImGui::TableSetColumnIndex( 1 );
						LARGE_INTEGER entry_size = { 0 };
						Everything_GetResultSize( row, &entry_size );
						ImGui::Text( std::to_string( entry_size.LowPart + entry_size.HighPart ).c_str() );

					}

					ImGui::EndTable();
				}

				// if ( ImGui::BeginListBox( ( "##listbox" + std::to_string( i ) ).c_str(), ImVec2( 0.0f, ImGui::GetContentRegionAvail().y ) ) )
				// {
				// 	DWORD result_len = Everything_GetNumResults();
				// 	static bool selected[ 1000 ];

				// 	for ( DWORD i = 0; i < result_len; i++ )
				// 	{
				// 		LPCSTR str = Everything_GetResultFileNameA( i );

				// 		if ( ImGui::Selectable( str, selected[ i ], ImGuiSelectableFlags_AllowDoubleClick ) )
				// 		{
				// 			if ( ImGui::IsMouseDoubleClicked( 0 ) )
				// 			{
				// 				Everything_SetSearchA( "infolder:D:" );
				// 				Everything_QueryA( TRUE );
				// 				std::cout << i << std::endl;
				// 			}
				// 			if ( !ImGui::GetIO().KeyCtrl )
				// 			{
				// 				memset( selected, 0, sizeof( selected ) );
				// 			}
				// 			selected[ i ] = !selected[ i ];
				// 		}
				// 	}
				// 	ImGui::EndListBox();
				// }
				ImGui::EndTabItem();
			}
		}
		if ( ImGui::TabItemButton( "+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip ) )
		{
			FSRecordList* fsrc = new FSRecordList( "This PC", 10 );
		}

		ImGui::EndTabBar();
	}
	ImGui::End();
}

void UI_s::PreviewWindow()
{
	ImGui::Begin( "preview_window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
	ImGui::End();
}

void UI_s::PropertiesWindow()
{
	ImGui::Begin( "properties_window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize );
	ImGui::End();
}