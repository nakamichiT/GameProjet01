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
	mf::MfManager* mfManager, const mf::MfObject* fromMfObject, void* placement\

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

	public:

		/*!
		* @brief Verify that it is a valid class id object.
		* @return true: valid object / false: invalid object
		*/
		bool isValid( )const;

	};

}

#endif