/*---------------------------------------------------------------------------
* @file: mffile.h
* @author: T.Nakamichi
* @brief: Define a class for handling files.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_IO_FILE_H___
#define ___MF_IO_FILE_H___

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
        * @brief A class for handling files.
        */
        class MfFile
        {
        private:

            /*!
            * @brief Constructer.
            */
            MfFile() = delete;

            /*!
            * @brief Destructer.
            */
            ~MfFile() = delete;

        public:

            /*!
            * @brief Opens the specified file.
            * @param filePath: Path of the file to open.
            * @param fileDataType: Data type of file to open.
            * @return A class object for handling file data.
            */
            static mf::io::MfFileStream OpenWrite(const char* filePath, const mf::io::MfFileDataType fileDataType);

            /*!
            * @brief Opens the specified file.
            * @param filePath: Path of the file to open.
            * @param fileDataType: Data type of file to open.
            * @return A class object for handling file data.
            */
            static mf::io::MfFileStream OpenRead(const char* filePath, const mf::io::MfFileDataType fileDataType);

            /*!
            * @brief Check if the specified file exists.
            * @param filePath: Path of the file whose existence is to be verified.
            * @return true: The specified file exists./ false: The specified file does not exist.
            */
            static bool isExist(const char* filePath);

        };
    }
}


#endif