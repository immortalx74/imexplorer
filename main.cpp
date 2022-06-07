#include "app.cpp"
#include "ui.cpp"
#include "filesystem.cpp"

// NOTE: Requires SDL 2.0.17+

int main(int, char **)
{
	App.Init();

	Everything_SetMatchWholeWord(true);
	Everything_SetSearchA("parent:");
	Everything_QueryA(TRUE);

	while (App.running)
	{
		App.ProcessEvents();
		App.BeginFrame();

		UI.BeginDockSpace();
		UI.FileListWindow();
		UI.PreviewWindow();
		UI.PropertiesWindow();
		UI.EndDockSpace();
		// ImGui::ShowDemoWindow();

		App.Render();
	}

	App.ShutDown();

	return 0;
}
