#pragma once

#include "app.h"

FSTab::FSTab()
{
	this->Populate();
	FSTabList.tabs.Push( this );
}

void FSTab::Populate()
{
	std::string search_query;

	if ( this->path.volume == "" )
	{
		search_query = "infolder:";
		this->label = "This PC";
	}
	else
	{
		search_query = "infolder:\"" + this->path.volume;

		int len = this->path.folder.length;

		for ( int i = 0; i < len; ++i )
		{
			search_query += "\\" + *this->path.folder[ i ];
		}

		if ( len == 0 )
		{
			this->label = this->path.volume;
		}
		else
		{
			this->label = *this->path.folder[ this->path.folder.length - 1 ];
		}

		search_query += "\"";
	}

	Everything_SetRequestFlags( Everything.request_flags );
	Everything_SetSearchW( Util.ConvertUtf8ToWide( search_query ).c_str() );
	Everything_QueryW( TRUE );
	DWORD record_count = Everything_GetNumResults();

	if ( record_count > 0 )
	{
		if ( this->records.capacity == 0 )
		{
			this->records.Reserve( record_count );
		}
		else
		{
			this->records.Clear();
			// this->records.Destroy();
			this->records.Reserve( record_count );
		}
	}
	else
	{
		this->records.Clear();
		this->records.Destroy();
	}

	// populate records
	for ( int i = 0; i < record_count; ++i )
	{
		FSRecord* rec = new FSRecord();

		// name
		std::string name = Util.ConvertWideToUtf8( Everything_GetResultFileNameW( i ) );
		rec->name = new char[ name.size() + 1 ];

		for ( int j = 0; j < name.size(); ++j )
		{
			rec->name[ j ] = name[ j ];
		}

		rec->name[ name.size() ] = '\0';

		// type
		if ( Everything_IsVolumeResult( i ) )
		{
			rec->type = FSRecordType_e::Volume;
			rec->icon_idx = 405; // NOTE volume icon idx
		}
		else if ( Everything_IsFolderResult( i ) )
		{
			rec->type = FSRecordType_e::Folder;
			rec->icon_idx = 129; // NOTE folder icon idx
		}
		else // file
		{
			rec->type = FSRecordType_e::File;
			LPCWSTR e = Everything_GetResultExtensionW( i );

			if ( e != NULL )
			{
				std::string temp = Util.ConvertWideToUtf8( e );
				std::map<std::string, int>::iterator it;
				it = FileIcons.extensions.find( temp );

				if ( it != FileIcons.extensions.end() )
				{
					rec->icon_idx = it->second;
				}
				else
				{
					rec->icon_idx = 91; // NOTE default icon idx
				}
			}
			else
			{
				std::map<std::string, int>::iterator it;
				it = FileIcons.extensions.find( "default" );
				rec->icon_idx = it->second; //NOTE replace this with actual default icon idx
				std::cout << "no extension" << std::endl;
			}

		}

		// size
		Everything_GetResultSize( i, &rec->size.li );
		Util.FileSizeToString( rec->size.li, &rec->size.text );

		// date
		FILETIME filetime;
		Everything_GetResultDateCreated( i, &filetime );
		FileTimeToSystemTime( &filetime, &rec->date_created.systemtime );
		Util.SystemTimeToString( rec->date_created.systemtime, &rec->date_created.text );

		this->records.Push( rec );
	}
}

void FSTab::PathAddVolume( std::string volume_name )
{
	this->path.volume = volume_name;
	this->Populate();
}
void FSTab::PathAddFolder( std::string* folder_name )
{
	this->path.folder.Push( folder_name );
	this->Populate();
}

void FSTab::PathRemoveFolder( int count )
{
	for ( int i = 0; i < count; ++i )
	{
		this->path.folder.Pop();
	}

	this->Populate();
}

void FSTab::PathRemoveVolume()
{
	this->path.volume = "";
	this->Populate();
}