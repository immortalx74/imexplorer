#pragma once

#include "app.h"

FSTab::FSTab()
{
	this->Populate();
	FSTabList.tabs.Push( this );
}

void FSTab::Populate()
{
	std::string final_path;
	if ( this->path_composed.volume == "" )
	{
		final_path = "infolder:";
		this->label = "This PC";
	}
	else
	{
		final_path = "infolder:" + this->path_composed.volume;

		int len = this->path_composed.folder.length;
		for ( int i = 0; i < len; ++i )
		{
			final_path += "\\" + *this->path_composed.folder[ i ];
		}

		if ( len == 0 )
		{
			this->label = this->path_composed.volume;
		}
		else
		{
			this->label = *this->path_composed.folder[ this->path_composed.folder.length - 1 ];
		}
	}

	Everything_SetRequestFlags( EVERYTHING_REQUEST_FILE_NAME | EVERYTHING_REQUEST_PATH | EVERYTHING_REQUEST_SIZE | EVERYTHING_REQUEST_FULL_PATH_AND_FILE_NAME );
	Everything_SetSearchW( Util.ConvertUtf8ToWide( final_path ).c_str() );
	Everything_QueryW( TRUE );
	DWORD record_count = Everything_GetNumResults();


	if ( this->records.capacity == 0 )
	{
		this->records.Reserve( record_count );
	}
	else
	{
		this->records.Clear();
		this->records.Destroy();
		this->records.Reserve( record_count );
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
		}
		else if ( Everything_IsFolderResult( i ) )
		{
			rec->type = FSRecordType_e::Folder;
		}
		else
		{
			rec->type = FSRecordType_e::File;
		}

		// size
		Everything_GetResultSize( i, &rec->size );

		this->records.Push( rec );
	}
}

void FSTab::PathAddVolume( std::string volume_name )
{
	this->path_composed.volume = volume_name;
	this->Populate();
}
void FSTab::PathAddFolder( std::string* folder_name )
{
	this->path_composed.folder.Push( folder_name );
	this->Populate();
}