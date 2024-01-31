/*---------------------------------------------------------------------------
* @file: mffileaccessor.h
* @author: T.Nakamichi
* @brief: Define a class that has the function of inputting and outputting file data.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_IO_FILEACCESSOR_H___
#define ___MF_IO_FILEACCESSOR_H___

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
        * @brief A class that has the function of inputting and outputting file data.
        */
        class MfFileAccessor 
        {
        private:

            /*!
            * @brief Used to hold the path of the file to control.
            */ 
            const char* mFilePath;

        protected:

            /*!
            * @brief Constructer.
            * @param filePath: Path of the file to be handled
            */
            MfFileAccessor(const char* filePath);

        public:

            /*!
            * @brief Read data in a file.
            * @param buffer: A buffer for storing the data of the read file.
            * @param bufferSize: The size of the buffer that stores the read data.
            * @return Number of bytes of data read.
            */
            virtual mf::Size_T read(char* buffer, const mf::Size_T bufferSize);

        protected:

            /*!
            * @brief Get the stored file path.
            * @return The file path it holds.
            */
            inline const char* getFilePath()const
            {
                return this->mFilePath;
            }

        };
    }
}

#endif