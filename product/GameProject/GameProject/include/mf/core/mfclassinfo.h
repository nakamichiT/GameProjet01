/*---------------------------------------------------------------------------
* @file: mfclassinfo.h
* @author: T.Nakamichi
* @brief: Defines a structure to hold class information.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_CLASSINFO_H___
#define ___MF_CORE_CLASSINFO_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mftype.h"	
#include "mf/core/mfstringid.h"
#include "mf/core/mfclassid.h"

/*******************************************************
* implement.
********************************************************/

namespace mf
{

	/*!
	* @brief  A structure for holding class names and other class information.
	*/
	struct MfClassInfo
	{
		/*!
		* @brief Memory size required to create an instance.
		*/
		const mf::Size_T InstanceSize = 0;

		/*!
		* @brief  Class-specific id created from the class name.
		*/
		const mf::MfStringId ClassNameId = "Undefined";

		/*!
		* @brief Used to hold the class id of the parent class.
		*/
		mf::MfClassId ParentClassId;

		/*!
		* @brief Used to hold the function that creates the object.
		*/
		mf::MfCreateObjectProc CreateObjectProc = nullptr;

	};

}

#endif