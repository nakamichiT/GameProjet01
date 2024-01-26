/*---------------------------------------------------------------------------
* @file: mffilehandler.h
* @author: T.Nakamichi
* @brief: Define a class that has a handle to a file object.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_IO_FILEHANDLER_H___
#define ___MF_IO_FILEHANDLER_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mftype.h"

/*******************************************************
* implements
********************************************************/
namespace mf 
{
    namespace io
    {

        /*!
        * @brief A class that has a handle to a file object.
        */
        class MfFileHandler 
        {
        public:

            /*!
            * @brief Used to hold a handle to a file object
            */
            const mf::MfObjectId Handle;

        public:

            /*!
            * @brief Constructer
            */
            inline MfFileHandler() :
                Handle(0)
            {
            }

            /*!
            * @brief Constructer.
            * @param handle:
            */
            inline MfFileHandler(const mf::MfObjectId handle) :
                Handle(handle)
            {
            }

        public:

            inline mf::io::MfFileHandler operator=(const mf::io::MfFileHandler& mfFileHandler)
            {
                return mf::io::MfFileHandler(mfFileHandler.Handle);
            }

        };
    }
}


#endif