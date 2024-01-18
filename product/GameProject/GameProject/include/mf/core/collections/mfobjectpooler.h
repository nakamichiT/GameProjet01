/*---------------------------------------------------------------------------
* @file: mffixedsizeblocks.h
* @author: T.Nakamichi
* @brief: Defines a class that creates a specified number of fixed-length memory blocks.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_COLLECTIONS_OBJECTPOOLER_H___
#define ___MF_CORE_COLLECTIONS_OBJECTPOOLER_H___ 

/*******************************************************
* include file
********************************************************/
#include "mf/core/collections/mffixedsizeblocks.h"

namespace mf
{
	namespace collections
	{

		/*!
		* @brief Creates a memory pool of the specified class type.
		*/
		template < class T, class Allocator = mf::collections::memories::MfAllocator >
		class MfObjectPooler : public mf::collections::MfFixedSizeBlock< Allocator >
		{
		public:

			/*!
			* @brief Constructer.
			*/
			MfObjectPooler( ) :
				mf::collections::MfFixedSizeBlock< Allocator >( )
			{
			}

			/*!
			* @brief Constructer.
			* @param count: Number of blocks to be created.
			*/
			MfObjectPooler( const mf::Int32 count ) :
				mf::collections::MfFixedSizeBlock< Allocator >( sizeof( T ), count )
			{
			}

			/*!
			* @brief Constructer.
			* @param count: Number of blocks to be created.
			* @param allocator: Allocator for object pool memory allocation.
			*/
			MfObjectPooler( const mf::Int32 count, const Allocator& allocator ) :
				mf::collections::MfFixedSizeBlock< Allocator >( sizeof( T ), count, allocator )
			{
			}

		};

	}
}

#endif