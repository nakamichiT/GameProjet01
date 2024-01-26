/*---------------------------------------------------------------------------
* @file: mffileaccess.h
* @author: T.Nakamichi
* @brief: Define file access types.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_IO_FILEACCESS_H___
#define ___MF_IO_FILEACCESS_H___

/*******************************************************
* include file
********************************************************/
#include "mf/io/mffiledatatype.h"
#include "mf/io/mffilestream.h"

/*******************************************************
* implements
********************************************************/
namespace mf 
{
    namespace io 
    {
        /*!
        * @brief File access types.
        */
        enum class MfFileAccess 
        {
            Write,
            Read
        }
    }
}


#endif