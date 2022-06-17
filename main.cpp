// #ifndef UNICODE
// #define UNICODE
// #endif
// #ifndef _UNICODE
// #define _UNICODE
// #endif
#include "app.cpp"
#include "util.cpp"
#include "ui.cpp"
#include "filesystem.cpp"
#include "settings.cpp"

// NOTE: Requires SDL 2.0.17+

int main( int, char** )
{
	App.Init();

	// char* ttt = "ΓΔΛ";
	// std::cout << ttt << std::endl;
	// std::string test_str = ConvertWideToUtf8( L"ΩΦΔΛ" );
	// std::string test_str =  "ΩΦΔΛ";
	// std::cout << test_str << std::endl;
	// MessageBox(NULL, L"ΓΔΩΛ", L"ffdffd", MB_OK);


	// Everything_SetMatchWholeWord( true );
	// Everything_SetRequestFlags( EVERYTHING_REQUEST_FILE_NAME | EVERYTHING_REQUEST_PATH | EVERYTHING_REQUEST_SIZE | EVERYTHING_REQUEST_FULL_PATH_AND_FILE_NAME );
	// Everything_SetSearchW( L"infolder:" );
	// Everything_QueryW( TRUE );


	while ( App.running )
	{
		App.ProcessEvents();
		App.BeginFrame();

		UI.BeginDockSpace();
		UI.RenderFSWindow();
		UI.RenderPreviewWindow();
		UI.RenderPropertiesWindow();
		UI.EndDockSpace();
		ImGui::ShowDemoWindow();

		App.Render();
	}

	App.ShutDown();

	return 0;
}
