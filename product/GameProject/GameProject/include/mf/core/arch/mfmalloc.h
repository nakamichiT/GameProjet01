/*---------------------------------------------------------------------------
* @file: mfmalloc.h
* @author: T.Nakamichi
* @brief: Define types and functions related to memory allocation and destruction.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_ARCH_MALLOC_H___
#define ___MF_CORE_ARCH_MALLOC_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mftype.h"

/*******************************************************
* macro.
********************************************************/

/*******************************************************
* implement.
********************************************************/
namespace mf
{

	/*!
	* @brief Type used to hold functions for memory allocation.
	*/
	typedef void* ( *MfMallocProcHandler )( const mf::Size_T size );

	/*!
	* @brief Type used to hold the function for unallocating memory.
	*/
	typedef void ( *MfFreeProcHandler )( void* memory );

	/*!
	* @brief Allocates memory of the specified size.
	* @param size: Size of memory to be allocated.
	* @return Memory of the specified memory size.
	*              (*If allocation fails, nullptr is returned.)
	*/
	void* MfMalloc( const mf::Size_T size );

	/*!
	* @brief Destroy memory allocated using the "MfMalloc" function.
	* @param memory: Memory to be destroyed.
	*/
	void MfFree( void* memory );

	/*!
	* @brief Register memory allocation functions.
	* @param Memory allocation functions.
	*/
	void MfSetMallocProcHandler( mf::MfMallocProcHandler mtMallocProcHandler );

	/*!
	* @brief Register a memory destruction function.
	* @param Memory destruction function.
	*/
	void MfSetFreeProcHandler( mf::MfFreeProcHandler mfFreeProcHandler );

}

#endif