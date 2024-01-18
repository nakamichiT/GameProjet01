/*---------------------------------------------------------------------------
* @file: mfallocator.h
* @author: T.Nakamichi
* @brief: Define the basic memory allocator class used in Collections.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_COLLECTIONS_MEMORIES_ALLOCATOR_H___
#define ___MF_CORE_COLLECTIONS_MEMORIES_ALLOCATOR_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mftype.h"

/*******************************************************
* implements.
********************************************************/
namespace mf
{
	namespace collections
	{
		namespace memories
		{
			/*!
			* @brief Basic memory allocator class used in Collections.
			*/
			class MfAllocator
			{
			public:

				/*!
				* @brief Allocates memory of the specified size.
				*           (*If allocation fails, nullptr is returned.)
				* @param size: Size of memory to be allocated.
				* @return Memory for the specified size or nullptr.
				*/
				virtual void* allocate( const mf::Size_T size );

				/*!
				* @brief Destruction of memory allocated by allocate method.
				* @param memory: Memory allocated by allocate method.
				*/
				virtual void deallocate( void* memory );

			};
		}
	}
}

#endif