/*---------------------------------------------------------------------------
* @file: mffixedsizeblocks.h
* @author: T.Nakamichi
* @brief: Defines a class that creates a specified number of fixed-length memory blocks.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_COLLECTIONS_FIXEDSIZEBLOCKS_H___
#define ___MF_CORE_COLLECTIONS_FIXEDSIZEBLOCKS_H___ 

/*******************************************************
* include file
********************************************************/
#include "mf/core/collections/memories/mtallocator.h"

/*******************************************************
* implement.
********************************************************/

namespace mf
{
	namespace collections
	{
		/*!
		* @brief An object pool class with the specified memory size.
		*/
		template < class Allocator = mf::collections::memories::MfAllocator > 
		class MfFixedSizeBlock
		{
		private:

			/*!
			* @brief Used to hold memory allocated through allocate.
			*/
			void* mAllocatedMemory;

			/*!
			* @brief Used as a list for managing unused addresses.
			*/
			void** mFreeBlockList;

			/*!
			* @brief Used to hold the allocator for allocating memory for the pool.
			*/
			Allocator mAllocator;

			/*!
			* @brief Used to hold the memory size per block.
			*/
			mf::Size_T mBlockMemorySize;

			/*!
			* @brief Used to hold the number of blocks created.
			*/
			mf::Int32 mBlockCount;

		public:

			/*!
			* @brief Constructer.
			*/
			MfFixedSizeBlock( ) :
				mAllocatedMemory( nullptr ),
				mFreeBlockList( nullptr ),
				mAllocator( ),
				mBlockMemorySize( 0 ),
				mBlockCount( 0 )
			{
			}

			/*!
			* @brief Constructer.
			* @param blockMemorySize: Size of one block of memory.
			* @param blockCount: Number of blocks to be created.
			* */
			MfFixedSizeBlock( const mf::Size_T blockMemorySize, const mf::Int32 blockCount ) :
				mAllocatedMemory( nullptr ),
				mFreeBlockList( nullptr ),
				mAllocator( ),
				mBlockMemorySize( blockMemorySize ),
				mBlockCount( blockCount )
			{
				// Creates the specified number of blocks of the specified memory size and creates a list of unused blocks.
				this->createFreeBlockList( );
			}

			/*!
			* @brief Constructer.
			* @param blockMemorySize: Size of one block of memory.
			* @param blockCount: Number of blocks to be created.
			* */
			MfFixedSizeBlock( const mf::Size_T blockMemorySize, const mf::Int32 blockCount, Allocator allocator ) :
				mAllocatedMemory( nullptr ),
				mFreeBlockList( nullptr ),
				mAllocator( allocator ),
				mBlockMemorySize( blockMemorySize ),
				mBlockCount( blockCount )
			{
				// Creates the specified number of blocks of the specified memory size and creates a list of unused blocks.
				this->createFreeBlockList( );
			}

			/*!
			* @brief Destructer.
			*/
			~MfFixedSizeBlock( )
			{
				// Release the allocated memory from the allocator.
				this->mAllocator.deallocate( this->mAllocatedMemory );
			}

		private:

			/*!
			* @brief Allocate memory for the total number of blocks and create a list of unused blocks.
			*/
			void createFreeBlockList( )
			{
				// Allocate memory in which all blocks can be created.
				this->mAllocatedMemory = this->mAllocator.allocate( this->mBlockMemorySize * this->mBlockCount );
				// Address to the first free block.
				this->mFreeBlockList = (void**)this->mAllocatedMemory;
				// Define a variable for work to be used temporarily to create a free block and set the first address.
				void** temp = this->mFreeBlockList;
				// Creation of a free block list.
				for ( mf::Int32 i = 0; i < this->mBlockCount - 1; i++ )
				{
					*temp = (void*)( (const mf::Int8*)temp + this->mBlockMemorySize );
					temp = (void**)*temp;
				}
				// Set the element to be the terminating element.
				*temp = nullptr;
			}

		public:

			/*!
			* @brief Find and retrieve allocatable blocks from unused blocks.
			* @return Allocatable memory. Return nullptr if allocation fails.
			*/
			void* allocate( )
			{
				// Used to store memory to be allocated.
				void* memory = nullptr;
				// Verify whether unused blocks exist.
				if ( this->mFreeBlockList )
				{
					// Allocate unused blocks.
					memory = (void*)this->mFreeBlockList;
					// Update unused blocks.
					this->mFreeBlockList = (void**)*this->mFreeBlockList;
				}
				return memory;
			}

		public:

			/*!
			* @brief Deallocate memory so that it can be reused as unused blocks.
			* @param memory: Memory to be deallocated.
			*/
			void deallocate( void* memory )
			{
				// Variable to temporarily hold the address of the first block registered in the unused block list.
				void* temp = (void*)this->mFreeBlockList;
				// Unallocated memory is set to the first block.
				this->mFreeBlockList = (void**)memory;
				// Concatenate the block that was evacuated behind the latest first block.
				*this->mFreeBlockList = temp;
			}

		public:

			/*!
			* @brief Deep copy and make a copy of the specified object.
			* @param mfFixedSizeBlocks: Source object.
			*/
			inline mf::collections::MfFixedSizeBlock< Allocator >& operator=( const mf::collections::MfFixedSizeBlock<Allocator>& mfFixedSizeBlocks )
			{
				// If the block has already been created, the memory that had been acquired is discarded and then the block is recreated.
				if ( this->mAllocatedMemory )
				{
					// Release the allocated memory from the allocator.
					this->mAllocator.deallocate( this->mAllocatedMemory );
				}

				// Copy information to create a block identical to the specified object.
				this->mAllocator = mfFixedSizeBlocks.mAllocator;
				this->mBlockCount = mfFixedSizeBlocks.mBlockCount;
				this->mBlockMemorySize = mfFixedSizeBlocks.mBlockMemorySize;

				// Creates the specified number of blocks of the specified memory size and creates a list of unused blocks.
				this->createFreeBlockList( );

				return *this;
			}

		};
	}
}

#endif