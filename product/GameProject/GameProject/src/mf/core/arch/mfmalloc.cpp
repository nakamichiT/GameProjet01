/*---------------------------------------------------------------------------
* @file: mfmalloc.h
* @author: T.Nakamichi
* @brief: Define types and functions related to memory allocation and destruction.
* @create day:
*----------------------------------------------------------------------------*/
/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mfmalloc.h"

/*******************************************************
* staic.
********************************************************/

/*!
* @brief Used to hold the memory allocation function specified in MfSetMallocProcHandler.
*/
static mf::MfMallocProcHandler gMallocProcHandler = nullptr;

/*!
* @brief Used to hold the memory destruction function specified in MfSetFreeProcHandler.
*/
static mf::MfFreeProcHandler gFreeProcHandler = nullptr;

/*******************************************************
* implement.
********************************************************/

/*!
* @brief Allocates memory of the specified size.
* @param size: Size of memory to be allocated.
* @return Memory of the specified memory size.
*              (*If allocation fails, nullptr is returned.)
*/
void* mf::MfMalloc( const mf::Size_T size )
{
	return gMallocProcHandler ? gMallocProcHandler( size ) : nullptr;
}

/*!
* @brief Destroy memory allocated using the "MfMalloc" function.
* @param memory: Memory to be destroyed.
*/
void mf::MfFree( void* memory )
{
	if ( gFreeProcHandler ) gFreeProcHandler( memory );
}

/*!
* @brief Register memory allocation functions.
* @param Memory allocation functions.
*/
void mf::MfSetMallocProcHandler( mf::MfMallocProcHandler mtMallocProcHandler )
{
	gMallocProcHandler = mtMallocProcHandler;
}

/*!
* @brief Register a memory destruction function.
* @param Memory destruction function.
*/
void mf::MfSetFreeProcHandler( mf::MfFreeProcHandler mfFreeProcHandler )
{
	gFreeProcHandler = mfFreeProcHandler;
}

/*!
* @brief Calculate the memory size with alignment adjustment.
* @param size: Memory size.
* @param alignment: Aligmnet.
* @return Memory size after alignment adjustment.
*/
mf::Size_T mf::MfAdjustmentAlignment(const mf::Size_T size, const mf::Size_T alignment)
{
	return ( adjustmentMemorySize + ( alignment - 1 ) ) & ( ~ ( alignment - 1 ) );
}