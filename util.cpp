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

std::string Util_s::FileSizeToStringKB( LARGE_INTEGER n)
{
	std::string sz;
	unsigned long long sz_num;

	sz_num = ( unsigned long long )ceil( ( long double )n.QuadPart / 1024 );
	sz = std::to_string( sz_num );
	int len = sz.length();

	for ( int i = len; i >= 0; --i )
	{
		if ( i != len && i != 0 && ( len - i ) % 3 == 0 )
		{
			sz.insert( i, 1, ',' );
		}
	}

	sz += " KB";

	return sz;
}

std::string Util_s::FileSizeToString( LARGE_INTEGER n )
{
	std::string size_units[ 4 ] = { " bytes", " KB", " MB", " GB" };
	std::string sz;
	long double sz_num;
	std::ostringstream oss;
	int idx = 0;

	if ( n.QuadPart < 1024 )
	{
		sz_num = n.QuadPart;
	}
	else if ( n.QuadPart >= 1024 && n.QuadPart < 1048576 )
	{
		sz_num = ( long double )n.QuadPart / 1024;
		idx = 1;
	}
	else if ( n.QuadPart >= 1048576 && n.QuadPart < 1073741824 )
	{
		sz_num = ( long double )n.QuadPart / 1048576;
		idx = 2;
	}
	else
	{
		sz_num = ( long double )n.QuadPart / 1073741824;
		idx = 3;
	}

	oss << std::setprecision( 3 ) << sz_num;
	sz = oss.str();
	sz += size_units[ idx ];

	return sz;
}

std::string Util_s::SystemTimeToString( SYSTEMTIME st )
{
	std::string dt = std::to_string( st.wDay ) + "/" + std::to_string( st.wMonth ) + "/" + std::to_string( st.wYear ) + " " + std::to_string( st.wHour ) + ":" + std::to_string( st.wMinute );

	return dt;
}