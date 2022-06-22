#include "app.cpp"
#include "util.cpp"
#include "ui.cpp"
#include "filesystem.cpp"
#include "settings.cpp"
#include "toolbar.cpp"
#include "file_icons.cpp"

// NOTE: Requires SDL 2.0.17+

int main( int, char** )
{
	App.Init();

	while ( App.running )
	{
		App.ProcessEvents();
		App.BeginFrame();

		UI.BeginDockSpace();
		UI.RenderFSWindow();
		if ( Settings.show_preview_pane )
		{
			UI.RenderPreviewWindow();
		}
		if ( App.debug )
		{
			UI.RenderDebugWindow();
		}

		UI.RenderPropertiesWindow();
		UI.EndDockSpace();

		if ( App.demo )
		{
			ImGui::ShowDemoWindow();
		}

		App.Render();
	}

	App.ShutDown();

	return 0;
}
