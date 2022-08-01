// NOTE: Requires SDL 2.0.17+ Docking branch

// TODO:
// * Investigate column width issue with cellpadding.
// * Implement column sorting.
// * Fix properties issues: Doesn't work for volumes, simplify constructing path+filename for each record.
// * Implement browsing history. (prob with a stack).
// * Remember scroll position when navigating to prev folder.
// * Font & UI scaling

#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif

#include "app.cpp"
#include "util.cpp"
#include "ui.cpp"
#include "filesystem.cpp"
#include "settings.cpp"
#include "toolbar.cpp"
#include "file_icons.cpp"

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

		UI.RenderStatusBarWindow();
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
