/*---------------------------------------------------------------------------
* @file: mffilestream.h
* @author: T.Nakamichi
* @brief: Deffine a class for reading and writing data from files.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_IO_FILESTREAM_H___
#define ___MF_IO_FILESTREAM_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mftype.h"
#include "mf/io/mffileaccessor.h"

/*******************************************************
* Forward declaration.
********************************************************/
namespace mf
{
	namespace io
	{
        class MfFile;
	}
}

/*******************************************************
* implements
********************************************************/
namespace mf 
{
    namespace io 
    {

        /*!
        * @brief A class for reading and writing data from files.
        */
        class MfFileStream 
        {
        private:

            friend MfFile;

        private:

            /*!
            * @brief Used to hold file control objects.
            */
            mf::io::MfFileAccessor* mFileAccessor;

        private:

            /*!
            * @brief Constructer.
            * @param mfFileAccessor: File control object.
            */
            MfFileStream( mf::io::MfFileAccessor* mfFileAccessor );

        public:

            /*!
            * @brief Constructer.
            */
            MfFileStream();

        public:

            /*!
            * @brief Read file data while synchronizing.
            * @param buffer: Buffer for storing data
            * @param bufferSize: The size of the buffer used to store data.
            * @return Read data size.
            */
            mf::Size_T read(char* buffer ,const f::Size_T bufferSize);

        public:

            /*!
            * @brief Destroy the file object.
            */
            void close();

        };
    }
}


#endif