/*---------------------------------------------------------------------------
* @file: mfstringid.cpp
* @author: T.Nakamichi
* @brief: Define a class that creates and holds hash values from strings.
* @create day:
*----------------------------------------------------------------------------*/
/*******************************************************
* include file
********************************************************/
#include "mf/core/mfstringid.h"

/*******************************************************
* implement.
********************************************************/

/*!
* @brief Helper function to create an id from a given string.
* @param string: String used to create the id.
* @return id created from string.
*/
template < class T >
static mf::Int64 MfCreateStringIdFromString( T string )
{
	// Used to store an id created from a string.
	mf::Int64 stringId = 0;

	// Creates an id from a specified string.
	while ( *string )
	{
		stringId += *string++ * 101;
	}

	return stringId;
}

/*!
* @brief Constructer.
*/
mf::MfStringId::MfStringId( ) :
	mStringId( 0 )
{
}

/*!
* @brief Constructer.
* @param string: String used to create the id.
*/
mf::MfStringId::MfStringId( const char* string ) : 
	mStringId( MfCreateStringIdFromString<const char*>( string ) )
{
}

/*!
* @brief Constructer.
* @param string: String used to create the id.
*/
mf::MfStringId::MfStringId( const wchar_t* string ) :
	mStringId( MfCreateStringIdFromString<const wchar_t*>( string ) )
{
}
