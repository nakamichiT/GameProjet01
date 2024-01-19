/*---------------------------------------------------------------------------
* @file: mfobject.cpp
* @author: T.Nakamichi
* @brief: Define a base class.
* @create day:
*----------------------------------------------------------------------------*/
/*******************************************************
* include file
********************************************************/
#include "mf/core/mfobject.h"

/*******************************************************
* static.
********************************************************/

/*!
* @brief Used to hold an ID that identifies the type of object.
*/
mf::MfClassId mf::MfObject::ClassId;

/*******************************************************
* implement.
********************************************************/

/*!
* @brief Constructer.
* @param mfFromObject: The object from which the instance is created.
*/
mf::MfObject::MfObject(const mf::MfObject* fromMfObject)
{
    // Nothing.
}

/*!
* @brief Get the id that identifies the type of the class.
* @return An id that identifies the type of the class.
*/
mf::MfClassId mf::MfObject::getClassId()const
{
    return mf::MfObject::ClassId;
}