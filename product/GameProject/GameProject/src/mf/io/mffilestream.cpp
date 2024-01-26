/*---------------------------------------------------------------------------
* @file: mffilestream.cpp
* @author: T.Nakamichi
* @brief: Deffine a class for reading and writing data from files.
* @create day:
*----------------------------------------------------------------------------*/
/*******************************************************
* include file
********************************************************/
#include "mf/io/mffilestream.h"


/*******************************************************
* implements
********************************************************/

/*!
* @brief Constructer.
*/
mf::io::MfFileStream::MfFileStream() : 
    mFileAccessor(nullptr)
{
}

/*!
* @brief Constructer.
* @param mfFileAccessor: File control object.
*/
mf::io::MfFileStream::MfFileStream(mf::io::MfFileAccessor* mfFileAccessor) : 
    mFileAccessor(mfFileAccessor)
{
}

/*!
* @brief Read file data while synchronizing.
* @param buffer: Buffer for storing data
* @param bufferSize: The size of the buffer used to store data.
* @return Read data size.
*/
mf::Size_T mf::io::MfFileStream::read(char* buffer ,const f::Size_T bufferSize)
{
    // Used to store the number of bytes of data read from the file.
    mf::Size_T readSize = 0;

    // If an object that can control files is set, data is read from the target file.
    if( this->mFileAccessor )
    {
        readSize = this->mFileAccessor.read(buffer, bufferSize);
    }

    return readSize;
}

/*!
* @brief Destroy the file object.
*/
void mf::io::MfFileStream::close()
{
    if(this->mFileAccessor)
    {
        mf::MfDelete<mf::io::MfFileStream>( &this->mFileAccessor );
    }    
}