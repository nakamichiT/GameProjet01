/*---------------------------------------------------------------------------
* @file: mfclassid.cpp
* @author: T.Nakamichi
* @brief: Define class to identify the class type.
* @create day:
*----------------------------------------------------------------------------*/
/*******************************************************
* include file
********************************************************/
#include "mf/core/mfclassid.h"
#include "mf/core/mfclassinfo.h"

/*******************************************************
* implement.
********************************************************/

/*!
* @brief Constructer.
*/
mf::MfClassId::MfClassId( ) : 
	mClassInfo( nullptr )
{
}

/*!
* @brief Constructer.
* @param mfClassInfo: Class information.
*/
mf::MfClassId::MfClassId( const mf::MfClassInfo* mfClassInfo ) : 
	mClassInfo( mfClassInfo )
{
}

/*!
* @brief Verify that the specified class is the same or an inherited class
* @param mfClassId: Class id used for verification
* @return true: Same or inherited class / false: Different class
*/
bool mf::MfClassId::is( const mf::MfClassId& mfClassId ) const
{
	// Variables used to store processing results.
	bool result = false;

	// Verifies that the specified class id and its own class id are valid objects.
	if ( this->isValid( ) && mfClassId.isValid( ) )
	{
		// Verify that they are of the same class.
		result = this->mClassInfo->ClassNameId == mfClassId.mClassInfo->ClassNameId;
		// If not, verify that the class id of the parent of the own class and the class id to be verified are the same.
		if ( result == false )
		{
			result = this->mClassInfo->ParentClassId.is( mfClassId );
		}
	}

	return result;
}

/*!
* @brief Verify that the specified class is the same class
* @param mfClassId: Class id used for verification
* @return true: same class / false: different class
*/
bool mf::MfClassId::isEqual( const mf::MfClassId& mfClassId ) const
{
	return this->isValid( ) && mfClassId.isValid( ) ? this->mClassInfo->ClassNameId == mfClassId.mClassInfo->ClassNameId : false;;
}

/*!
* @brief Verify that it is a valid class id object.
* @return true: valid object / false: invalid object
*/
bool mf::MfClassId::isValid( ) const
{
	return this->mClassInfo;
}
