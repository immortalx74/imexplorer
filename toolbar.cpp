#pragma once

#include "app.h"

ToolBarButton::ToolBarButton( const char* btn_char, const char* tooltip, Array<ToolBarButton*>* toolbar, ToolBarButtonID_e ID, bool is_separator )
{
	this->btn_char = btn_char;
	this->tooltip = tooltip;
	this->ID = ID;
	this->is_separator = is_separator;
	toolbar->Push( this );
}

void ToolBarButton::OnClick( ToolBarButtonID_e ID )
{
	if ( ID == ToolBarButtonID_e::MainToolBar_Settings )
	{
		ImGui::OpenPopup( "Settings##settings_window" );
	}
	else if ( ID == ToolBarButtonID_e::NavigationToolBar_Previous )
	{
		// NOTE: This is temp. Prev/Next should navigate on history
		if ( FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder.length == 0 )
		{
			FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveVolume();
		}
		else
		{
			FSTabList.tabs[ FSTabList.active_tab_index ]->PathRemoveFolder( 1 );
		}

	}
	else if ( ID == ToolBarButtonID_e::MainToolBar_Cut )
	{

	}
	else if ( ID == ToolBarButtonID_e::MainToolBar_Properties )
	{
		std::string vol = FSTabList.tabs[ FSTabList.active_tab_index ]->path.volume;
		Array<std::string*> filenames;
		Array<int> indices;
		int file_count = 0;

		int len = FSTabList.tabs[ FSTabList.active_tab_index ]->records.length;
		FSRecord* rec;

		std::string* path;
		std::string* fname;
		std::string* paf;

		for ( int i = 0; i < len; ++i )
		{
			rec = FSTabList.tabs[ FSTabList.active_tab_index ]->records[ i ];
			if ( rec->selected )
			{
				path = new std::string( "\\" );
				fname = new std::string;
				paf = new std::string;

				for ( int j = 0; j < FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder.length; ++j )
				{
					*path += *FSTabList.tabs[ FSTabList.active_tab_index ]->path.folder[ j ];
					*path += "\\";
				}

				*fname = rec->name;
				*paf = vol + *path + *fname;
				filenames.Push( paf );
				indices.Push( i );
				file_count++;

				delete path;
				delete fname;
			}
		}

		// ------------------------------
		// HRESULT hr;
		// CComPtr<IDataObject> pDataObject;

		// Array<PIDLIST_ABSOLUTE> pShellFileAbs;
		// for ( int i = 0; i < file_count; ++i )
		// {
		// 	LPITEMIDLIST lst = ILCreateFromPath( Util.ConvertUtf8ToWide( *filenames[ i ] ).c_str() );
		// 	pShellFileAbs.Push( lst );
		// }

		// PIDLIST_ABSOLUTE pShellParent = ILCloneFull( pShellFileAbs[ 0 ] );
		// ILRemoveLastID( pShellParent );

		// Array<LPCITEMIDLIST> pShellFiles;
		// for ( int i = 0; i < file_count; ++i )
		// {
		// 	LPCITEMIDLIST lst = ILFindChild( pShellParent, pShellFileAbs[ i ] );
		// 	pShellFiles.Push( lst );
		// }

		// hr = CIDLData_CreateFromIDArray( pShellParent, file_count, &pShellFiles[ 0 ], &pDataObject );
		// ILFree( pShellParent );

		// for ( int i = 0; i < file_count; ++i )
		// {
		// 	ILFree( ( LPITEMIDLIST )pShellFileAbs[ i ] );
		// }

		// if ( SUCCEEDED( hr ) )
		// {
		// 	hr = SHMultiFileProperties( pDataObject, 0 );
		// }



		//------------------------------------------------



		LPITEMIDLIST* pidlDrives = ( LPITEMIDLIST* )malloc( sizeof( LPITEMIDLIST ) * file_count );
		IShellFolder* psfDesktop;
		IDataObject* pData;
		HRESULT hr;
		ULONG chEaten = 0, dwAttributes = 0;

		hr = SHGetSpecialFolderLocation( NULL, CSIDL_DRIVES, pidlDrives );
		if ( SUCCEEDED( hr ) )
		{
			hr = SHGetDesktopFolder( &psfDesktop );

			for ( int i = 0; i < file_count; ++i )
			{
				CString currentFilePath = filenames[ i ]->c_str();
				psfDesktop->ParseDisplayName( NULL, NULL, currentFilePath.GetBuffer(), &chEaten, ( LPITEMIDLIST* )&pidlDrives[ i ], &dwAttributes );
			}

			if ( SUCCEEDED( hr ) )
			{
				hr = psfDesktop->GetUIObjectOf( NULL, file_count, ( LPCITEMIDLIST* )pidlDrives, IID_IDataObject, NULL, ( void** )&pData );
				if ( SUCCEEDED( hr ) )
				{
					CoInitialize( NULL );
					hr = SHMultiFileProperties( pData, 0 );
					if ( SUCCEEDED( hr ) )
					{
						pData->Release();
					}
					CoUninitialize();
				}
				if ( psfDesktop != NULL )
				{
					psfDesktop->Release();
				}
			}
			for ( int i = 0; i < file_count; ++i )
			{
				ILFree( pidlDrives[ i ] );
			}
		}

		for ( int i = 0; i < file_count; ++i )
		{
			// delete filenames[ i ];
		}
		// filenames.Destroy();
	}
}