#pragma once

#include "app.h"

std::string Util_s::ConvertWideToANSI( const std::wstring& wstr )
{
	int count = WideCharToMultiByte( CP_ACP, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL );
	std::string str( count, 0 );
	WideCharToMultiByte( CP_ACP, 0, wstr.c_str(), -1, &str[ 0 ], count, NULL, NULL );
	return str;
}

std::wstring Util_s::ConvertAnsiToWide( const std::string& str )
{
	int count = MultiByteToWideChar( CP_ACP, 0, str.c_str(), str.length(), NULL, 0 );
	std::wstring wstr( count, 0 );
	MultiByteToWideChar( CP_ACP, 0, str.c_str(), str.length(), &wstr[ 0 ], count );
	return wstr;
}

std::string Util_s::ConvertWideToUtf8( const std::wstring& wstr )
{
	int count = WideCharToMultiByte( CP_UTF8, 0, wstr.c_str(), wstr.length(), NULL, 0, NULL, NULL );
	std::string str( count, 0 );
	WideCharToMultiByte( CP_UTF8, 0, wstr.c_str(), -1, &str[ 0 ], count, NULL, NULL );
	return str;
}

std::wstring Util_s::ConvertUtf8ToWide( const std::string& str )
{
	int count = MultiByteToWideChar( CP_UTF8, 0, str.c_str(), str.length(), NULL, 0 );
	std::wstring wstr( count, 0 );
	MultiByteToWideChar( CP_UTF8, 0, str.c_str(), str.length(), &wstr[ 0 ], count );
	return wstr;
}

void Util_s::FileSizeToString( LARGE_INTEGER n, char** output )
{
	std::string sz = std::to_string( ( unsigned long long )ceil( ( double )n.QuadPart / 1024 ) );
	int len = sz.length();

	for ( int i = len; i >= 0; --i )
	{
		if ( i != len && i != 0 && ( len - i ) % 3 == 0 )
		{
			sz.insert( i, 1, ',' );
		}
	}
	sz += " KB";

	int str_len = sz.length();
	*output = ( char* )malloc( str_len + 1 );
	strcpy( *output, sz.c_str() );
}

void Util_s::SystemTimeToString( SYSTEMTIME st, char** output )
{
	std::string dt = std::to_string( st.wDay ) + "/" + std::to_string( st.wMonth ) + "/" + std::to_string( st.wYear ) + " " + std::to_string( st.wHour ) + ":" + std::to_string( st.wMinute );

	int str_len = dt.length();
	*output = ( char* )malloc( str_len + 1 );
	strcpy( *output, dt.c_str() );
}