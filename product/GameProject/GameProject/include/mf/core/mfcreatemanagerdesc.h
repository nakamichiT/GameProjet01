/*---------------------------------------------------------------------------
* @file: mfmanager.h
* @author: T.Nakamichi
* @brief: Define a structure that holds parameters for creating managed objects.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_CREATEMANAGERDESC_H___
#define ___MF_CORE_CREATEMANAGERDESC_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/mftypes.h"

/*******************************************************
* implements.
********************************************************/
namespace mf 
{
    /*!
    * @brief A structure that holds parameters for creating managed objects.
    */
    struct MfCreateManagerDesc 
    {
        /*!
        * @brief Number of classes that can be registered.
        */
        mf::Int32 RegisteredClasses = 20;
        /*!
        * @brief Number of objects that can be registered.
        */
        mf::Int32 RegisteredObjects = 20;
    }
}

#endif