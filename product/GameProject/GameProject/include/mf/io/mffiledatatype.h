/*---------------------------------------------------------------------------
* @file: mffiledatatype.h
* @author: T.Nakamichi
* @brief: 
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_IO_FILEDATATYPE_H___
#define ___MF_IO_FILEDATATYPE_H___

/*******************************************************
* include file
********************************************************/

/*******************************************************
* implements
********************************************************/

namespace mf 
{
    namespace io 
    {
        enum class MfFileDataType 
        {
            /*!
            * @brief When controlling a file, treat the file to be controlled as a text file.
            */
            TEXT,

            /*!
            * @brief When controlling a file, treat the file to be controlled as a binary file.
            */
            BINARTY
        };
    }
}


#endif