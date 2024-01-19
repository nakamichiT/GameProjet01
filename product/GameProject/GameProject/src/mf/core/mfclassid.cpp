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
#include "mf/core/arch/mfmalloc.h"
#include "mf/core/mfmanager.h"

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
* @brief Create an object. If creation fails, return nullptr.
* @param mfFromObject: The class that called the instance creation process.
* @param placement: Address to use when creating.
*                   If omitted, MfMalloc will be used to generate the memory required for instantiation.
* @return Created object or nullptr.
*/
mf::MfObject* mf::MfClassId::createInstance( const mf::MfObject* mfFromObject, void* placement ) 
{
	// Used to store the created instance.
	mf::MfObject* instance = nullptr;

	// Memory used when creating an instance.
	void* memory = placement;

	// Check whether you are ready to create an instance.
	if( this->isValid() )
	{
		// If the memory required for instance creation is not specified, create the required memory.
		if(memory == nullptr){
			memory = mf::MfMalloc( this->mClassInfo->InstanceSize );
		}

		// If memory for instance creation cannot be secured, do nothing further.
		if( memory ){
			this->mClassInfo->CreateObjectProc(mfFromObject, placement);
		}
	}

	return instance;
}

/*!
* @brief Create an object. If creation fails, return nullptr.s
*        After creation, register the created object with mfmanager.
*        (*Abort object creation if the same name is already in use)
* @param mfManager: Managed object.
* @param objectName: The name used when registering the object.
* @param mfFromObject: The class that called the instance creation process.
* @param placement: Address to use when creating.
*                   If omitted, MfMalloc will be used to generate the memory required for instantiation.
* @return Created object or nullptr.
*/
mf::MfObject* mf::MfClassId::createInstance( mf::MfManager* mfManager, const char* name, const mf::MfObject* mfFromObject, void* placement )
{
	// Used to store the created instance.
	mf::MfObject* instance = nullptr;

	// Check whether objects are registered using the same name.
	if ( mfManager && mfManager->findMfObject( name ) == nullptr )
	{
		// Create an object only if it is not registered.
		instance = this->createInstance( mfFromObject, placement );
		if ( instance )
		{
			// Register with the managed object only if the instance creation is successful.
			mfManager->registerMfObject( name, instance );
		}
	}

	return instance;
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
