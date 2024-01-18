/*---------------------------------------------------------------------------
* @file: mfallocator.cpp
* @author: T.Nakamichi
* @brief: Define the basic memory allocator class used in Collections.
* @create day:
*----------------------------------------------------------------------------*/
/*******************************************************
* include file
********************************************************/
#include "mf/core/collections/memories/mtallocator.h"
#include "mf/core/arch/mfmalloc.h"

/*******************************************************
* implements
********************************************************/

/*!
* @brief Allocates memory of the specified size.
*           (*If allocation fails, nullptr is returned.)
* @param size: Size of memory to be allocated.
* @return Memory for the specified size or nullptr.
*/
void* mf::collections::memories::MfAllocator::allocate( const mf::Size_T size )
{
	return mf::MfMalloc( size );
}

/*!
* @brief Destruction of memory allocated by allocate method.
* @param memory: Memory allocated by allocate method.
*/
void mf::collections::memories::MfAllocator::deallocate( void* memory )
{
	mf::MfFree( memory );
}