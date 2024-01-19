/*---------------------------------------------------------------------------
* @file: mfclassid.h
* @author: T.Nakamichi
* @brief: Define class to identify the class type.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_CLASSID_H___
#define ___MF_CORE_CLASSID_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mftype.h"	
#include "mf/core/mfstringid.h"

/*******************************************************
* Forward declaration.
********************************************************/
namespace mf
{
	class MfManager;
	struct MfClassInfo;
}

/*******************************************************
* macro.
********************************************************/

/*!
* @brief A macro that defines the parameters to be used when creating an object.
*/
#define MF_CREATE_OBJECT_PROC_PARAMETERS\
	const mf::MfObject* mfFromObject, void* placement\

/*******************************************************
* types.
********************************************************/

namespace mf
{
	/*!
	* @brief Type of the object creation function.
	*/
	typedef mf::MfObject* ( *MfCreateObjectProc )( MF_CREATE_OBJECT_PROC_PARAMETERS );
}

/*******************************************************
* implement.
********************************************************/
namespace mf
{

	/*!
	* @brief  A Class to identify the type of the class.
	*/
	class MfClassId
	{
	private:

		/*!
		* @brief Used to hold class information.
		*/
		const mf::MfClassInfo* mClassInfo;

	public:

		/*!
		* @brief Constructer.
		*/
		MfClassId( );

		/*!
		* @brief Constructer.
		* @param mfClassInfo: Class information.
		*/
		MfClassId( const mf::MfClassInfo* mfClassInfo );

	public:

		/*!
		* @brief Create an object. If creation fails, return nullptr.
		* @param mfFromObject: The class that called the instance creation process.
		* @param placement: Address to use when creating.
        *                   If omitted, MfMalloc will be used to generate the memory required for instantiation.
		* @return Created object or nullptr.
		*/
		mf::MfObject* createInstance( const mf::MfObject* mfFromObject = nullptr, void* placement = nullptr );

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
		mf::MfObject* createInstance( mf::MfManager* mfManager, const char* name, const mf::MfObject* mfFromObject = nullptr, void* placement = nullptr );

	public:

		/*!
		* @brief Verify that the specified class is the same or an inherited class
		* @param mfClassId: Class id used for verification
		* @return true: Same or inherited class / false: Different class
		*/
		bool is( const mf::MfClassId& mfClassId )const;

		/*!
		* @brief Verify that the specified class is the same class
		* @param mfClassId: Class id used for verification
		* @return true: same class / false: different class
		*/
		bool isEqual( const mf::MfClassId& mfClassId )const;

		/*!
		* @brief Verify that it is a valid class id object.
		* @return true: valid object / false: invalid object
		*/
		bool isValid( )const;

	};

}

#endif