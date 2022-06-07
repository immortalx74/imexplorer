#pragma once

#include "app.h"

void UI_s::BeginDockSpace()
{
	ImGuiDockNodeFlags_AutoHideTabBar;
	ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(App.win_w, App.win_h));
	ImGui::Begin("dock_space", NULL, flags);
	ImGui::DockSpace(ImGui::GetID("dock_space"));
}

void UI_s::EndDockSpace()
{
	ImGui::End();
}

void UI_s::FileListWindow()
{
	ImGui::Begin("file_list_window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	if (ImGui::BeginTabBar("main_tabbar", ImGuiTabBarFlags_Reorderable))
	{
		for (int i = 0; i < FSRCTabs.tabs.length; i++)
		{
			ImGui::PushID(i);

			if (ImGui::BeginTabItem(FSRCTabs.tabs[i]->label.c_str(), &FSRCTabs.tabs[i]->opened))
			{
				if (ImGui::Button("Up"))
				{
				}
				ImGui::SameLine();
				if (ImGui::Button("Prev"))
				{
				}
				ImGui::SameLine();
				if (ImGui::Button("Next"))
				{
				}

				char buf[100] = "type some text";
				ImGui::PushItemWidth(ImGui::GetWindowWidth());
				ImGui::InputText("type here", buf, 100);

				if (ImGui::BeginListBox("###listbox", ImVec2(0.0f, ImGui::GetContentRegionAvail().y)))
				{
					ImGui::EndListBox();
				}

				ImGui::PopItemWidth();
				ImGui::EndTabItem();
			}

			ImGui::PopID();
		}
		if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip))
		{
			FSRecordCollection *fsrc = new FSRecordCollection("This PC", 10);
		}


		// 	if (ImGui::BeginListBox("###listbox", ImVec2(0.0f, ImGui::GetContentRegionAvail().y)))
		// 	{
		// 		DWORD result_len = Everything_GetNumResults();
		// 		static bool selected[100];

		// 		for (DWORD i = 0; i < result_len; i++)
		// 		{
		// 			LPCSTR str = Everything_GetResultFileNameA(i);

		// 			if (ImGui::Selectable(str, selected[i]))
		// 			{
		// 				if (!ImGui::GetIO().KeyCtrl)
		// 				{
		// 					memset(selected, 0, sizeof(selected));
		// 				}
		// 				selected[i] = !selected[i];
		// 			}
		// 		}
		// 		ImGui::EndListBox();
		// 	}
		// 	ImGui::EndTabItem();


		ImGui::EndTabBar();
	}
	ImGui::End();
}

void UI_s::PreviewWindow()
{
	ImGui::Begin("preview_window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::End();
}

void UI_s::PropertiesWindow()
{
	ImGui::Begin("properties_window", NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
	ImGui::End();
}