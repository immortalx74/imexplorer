#pragma once

#include "app.h"

void Settings_s::Read()
{
	char filename[] = "settings.cfg";
	FILE* f = NULL;

	if ( ( f = fopen( filename, "rb" ) ) == NULL )
	{
		printf( "%s\n", "Error opening settings file.\nSaving defaults." );
		Settings.SetDefaults();
		Settings.Write();
	}
	else
	{
		fread( &Settings, sizeof( Settings ), 1, f );

		fclose( f );
		f = NULL;
	}
}

void Settings_s::Write()
{
	char filename[] = "settings.cfg";
	FILE* f = NULL;

	if ( ( f = fopen( filename, "wb" ) ) == NULL )
	{
		printf( "%s\n", "Error writting settings file. Aborting" );
		exit( 11 );
	}
	else
	{
		fwrite( &Settings, sizeof( Settings ), 1, f );

		fclose( f );
		f = NULL;
	}
}

void Settings_s::SetDefaults()
{
	Settings.show_menubar = true;
	Settings.show_toolbar = true;
	Settings.show_navigation_bar = true;
	Settings.show_preview_pane = true;

	Settings.Write();
}