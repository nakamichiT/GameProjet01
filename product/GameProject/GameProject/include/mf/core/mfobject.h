/*---------------------------------------------------------------------------
* @file: mfobject.h
* @author: T.Nakamichi
* @brief: Define a base class.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_OBJECT_H___
#define ___MF_CORE_OBJECT_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/mftype.h"
#include "mf/core/mfclassid.h"

/*******************************************************
* implement.
********************************************************/

namespace mf 
{
    /*!
    * @brief Base object class.
    */
    class MfObject
    {
    public:
        
        /*!
        * @brief Used to hold an ID that identifies the type of object.
        */
        static mf::MfClassid ClassId;

    public:

        /*!
        * @brief Get the id that identifies the type of the class.
        * @return An id that identifies the type of the class.
        */
        virtual mf::MfClassId getClassId()const;

    }
}

#endif