/*---------------------------------------------------------------------------
* @file: mffileaccessor.cpp
* @author: T.Nakamichi
* @brief: Define a class that has the function of inputting and outputting file data.
* @create day:
*----------------------------------------------------------------------------*/
/*******************************************************
* include file
********************************************************/
#include "mf/io/mffileaccessor.h"

/*******************************************************
* implement.
********************************************************/

/*!
* @brief Constructer.
* @param filePath: Path of the file to be handled
*/
mf::io::MfFileAccessor::MfFileAccessor(const char* filePath) : 
    mFilePath(filePath)
{
}

/*!
* @brief Read data in a file.
* @param buffer: A buffer for storing the data of the read file.
* @param bufferSize: The size of the buffer that stores the read data.
* @return Number of bytes of data read.
*/
mf::Size_T mf::io::MfFileAccessor::read(char* buffer, const mf::Size_T bufferSize)
{
    static_assert();
    return 0;
}