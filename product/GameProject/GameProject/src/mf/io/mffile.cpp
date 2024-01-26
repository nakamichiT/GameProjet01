/*---------------------------------------------------------------------------
* @file: mffile.cpp
* @author: T.Nakamichi
* @brief: Define a class for handling files.
* @create day:
*----------------------------------------------------------------------------*/
/*******************************************************
* include file
********************************************************/
#include "mf/io/mffile.h"
#include "mf/io/mffileaccessor.h"
#include <cstdio>

/*******************************************************
* implements
********************************************************/

class MfFileReader : public mf::io::MfFileAccessor 
{
protected:

    /*!
    * @brief Constructer.
    * @param filePath: Path of the file to be handled
    */
    MfFileReader(const char* filePath) :
        mf::io::MfFileAccessor(filePath)
    {        
    }

protected:

    /*!
    * @brief Read data in a file.
    * @param buffer: A buffer for storing the data of the read file.
    * @param bufferSize: The size of the buffer that stores the read data.
    * @return Number of bytes of data read.
    */
    mf::Size_T read( char* buffer, const mf::Size_T bufferSize, const char* fileMode )
    {
        // Used to store the number of bytes of data read
        mf::Size_T readSize = 0;

        return readSize;
    }

};

class MfTextFileReader : public MfFileReader
{
public:

    /*!
    * @brief Constructer.
    * @param filePath: Path of the file to be handled
    */
    MfTextFileReader(const char* filePath) :
        MfFileReader(filePath)
    {
    }

public:
    /*!
    * @brief Read data in a file.
    * @param buffer: A buffer for storing the data of the read file.
    * @param bufferSize: The size of the buffer that stores the read data.
    * @return Number of bytes of data read.
    */    
    mf::Size_T read( char* buffer, const mf::Size_T bufferSize )
    {
        this->read(buffer, bufferSize, "r");
    }
};

class MfBinFileReader : public MfFileReader
{
public:

    /*!
    * @brief Constructer.
    * @param filePath: Path of the file to be handled
    */
    MfBinFileReader(const char* filePath) :
        MfBinFileReader(filePath)
    {
    }

public:

    /*!
    * @brief Read data in a file.
    * @param buffer: A buffer for storing the data of the read file.
    * @param bufferSize: The size of the buffer that stores the read data.
    * @return Number of bytes of data read.
    */    
    mf::Size_T read( char* buffer, const mf::Size_T bufferSize )
    {
        this->read(buffer, bufferSize, "rb");
    }
};

/*!
* @brief Opens the specified file.
* @param filePath: Path of the file to open.
* @param fileDataType: Data type of file to open.
* @return A class object for handling file data.
*/
mf::io::MfFileStream mf::io::MfFile::OpenRead(const char* filePath, const mf::io::MfFileDataType fileDataType)
{
    // Used to store created file input/output objects.
    mf::io::MfFileAccessor* mfFileAccessor = nullptr;

    // Check if the file to be read exists.
    if(mf::io::MfFile::isExist( ) == true)
    {
        switch(fileDataType)
        {
            case mf::io::MfFileDataType::TEXT:
                mfFileAccessor = mf::MfNew<MfTextFileReader, const char*>(filePath);
                break;
            case mf::io::MfFileDataType::BINARTY:
                mfFileAccessor = mf::MfNew<MfBinFileReader, const char*>(filePath);
                break;
        }
    }

    return mf::io::MfFileAccessor(mffileaccessor);
}

/*!
* @brief Check if the specified file exists.
* @param filePath: Path of the file whose existence is to be verified.
* @return true: The specified file exists./ false: The specified file does not exist.
*/
bool mf::io::MfFile::isExist(const char* filePath)
{
    //Used to store processing results
    bool result = false;

    // Used to open the specified file and check its existence
    FILE* fp = nullptr;

    // Verify whether the file can be opened using the fopen function
    if(fopen_s( &fp, filePath ,"r" )){
        // Since the file is opened with the fopen function, close it once.
        fclose( fp );
        result = true;
    }

    return result;
}

