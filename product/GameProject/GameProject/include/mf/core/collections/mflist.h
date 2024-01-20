/*---------------------------------------------------------------------------
* @file: mflist.h
* @author: T.Nakamichi
* @brief: Define a list class.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_COLLECTIONS_LIST_H___
#define ___MF_CORE_COLLECTIONS_LIST_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mfnew.h"
#include "mf/core/collections/mfobjectpooler.h"

/*******************************************************
* implement.
********************************************************/

namespace mf
{
	namespace collections
	{
		/*!
		* @brief Bidirectional list class.
		*/
		template < class T, class Allocator = mf::collections::memories::MfAllocator >
		class MfList
		{
		private:

			/*!
			* @brief List node.
			*/
			struct MfListNode
			{
				/*!
				* @brief Used to hold a node connected to the front.
				*/
				MfListNode* previousNode = nullptr;

				/*!
				* @brief Used to hold a node connected to the back.
				*/
				MfListNode* nextNode = nullptr;

				/*!
				* @brief Used to store the specified value.
				*/
				T value;
			};

		public:

			struct MfListIterator
			{

				friend MfList;

			private:

				/*!
				* @brief Used to hold the node to be referenced.
				*/
				MfListNode* mNode = nullptr;

			public:

				/*!
				* @brief Constructer.
				* @param node: Node to be referenced.
				*/
				MfListIterator( MfListNode* node ) :
					mNode( node )
				{
				}

			public:

				MfListIterator& operator++( )
				{
					this->mNode = this->mNode->nextNode;
					return *this;
				}

				MfListIterator operator++( int )
				{
					MfListIterator itr = *this;
					++*this;
					return itr;
				}

				MfListIterator& operator--( )
				{
					this->mNode = this->mNode->previousNode;
				}

				MfListIterator operator--( int )
				{
					MfListIterator itr = *this;
					--*this;
					return itr;
				}

				bool operator ==( const MfListIterator& iterator )const
				{
					return this->mNode == iterator.mNode;
				}

				bool operator !=( const MfListIterator& iterator )const
				{
					return !( *this == iterator );
				}

				operator T( )const
				{
					return this->mNode->value;
				}

				T& operator*( )
				{
					return this->mNode->value;
				}

			};

		private:

			/*!
			* @brief The object pool used to create the listing node.
			*/
			mf::collections::MfObjectPooler< MfListNode, Allocator > mListNodePooler;

			/*!
			* @brief Used to store the number of nodes.
			*/
			mf::Int32 mCount;

			/*!
			* @brief Used to store the number of nodes that can be created.
			*/
			mf::Int32 mCapacity;

			/*!
			* @brief Used to store the first node of the list.
			*/
			MfListNode* mHeadNode;

			/*!
			* @brief Used to store the end node of a listing.
			*/
			MfListNode* mLastNode;

		public:

			/*!
			* @brief Constructer.
			*/
			inline MfList( ) :
				mListNodePooler( ),
				mCount( 0 ),
				mCapacity( 0 ),
				mHeadNode( nullptr ),
				mLastNode( nullptr )
			{
			}

			/*!
			* @brief Constructer.
			* @param capacity: Maximum number of nodes that can be created.
			*/
			inline MfList( const mf::Int32 capacity ) :
				mListNodePooler( capacity + 1 ),
				mCount( 0 ),
				mCapacity( capacity ),
				mHeadNode( nullptr ),
				mLastNode( nullptr )
			{
				// Create a termination node.
				this->initialize( );
			}

			/*!
			* @brief Constructer.
			* @param capacity: Maximum number of nodes that can be created.
			* @param allocator: Memory allocator used to create list nodes.
			*/
			inline MfList( const mf::Int32 capacity, const Allocator& allocator ) :
				mListNodePooler( capacity + 1, allocator ),
				mCount( 0 ),
				mCapacity( capacity ),
				mHeadNode( nullptr ),
				mLastNode( nullptr )
			{
				// Create a termination node.
				this->initialize( );
			}

			/*!
			* @brief Constructer. (*Make a copy of the listing specified in deep copy.)
			* @param list: Source list.
			*/
			inline MfList( const mf::collections::MfList<T, Allocator>& list ) :
				mListNodePooler( list.getCapacity( ) + 1 ),
				mCount( 0 ),
				mCapacity( list.getCapacity( ) ),
				mHeadNode( nullptr ),
				mLastNode( nullptr )
			{
				// Create a termination node.
				this->initialize( );
				// Make a copy of the node.
				this->merge( list );
			}

		private:

			/*!
			* @brief Initialize the listing so that it can be used.
			*/
			void initialize( )
			{				
				// A terminating node is created only when memory is available to create the node.
				if ( void* nodeMemory = this->mListNodePooler.allocate( ) )
				{
					// Create an end node for the list.
					MfListNode* node = new ( nodeMemory ) MfListNode;
					// Set the created node as the leading node and the ending node.
					this->mHeadNode = this->mLastNode = node;
				}
			}

		public:

			/*!
			* @brief Creates a node at the specified position and stores the value.
			* @param position: Position of insertion.
			* @param value: Value to be stored in the node.
			*/
			inline void insert( const MfListIterator& position, const T& value )
			{
				// Allocate memory to create the node to be inserted.
				// If allocation fails, nothing is done.
				if ( void* nodeMemory = this->mListNodePooler.allocate( ) )
				{
					// Creation of the node to be inserted.
					MfListNode* insertNode = new ( nodeMemory ) MfListNode;
					insertNode->value = value;

					// Update the connection of the node to be inserted.
					insertNode->previousNode = position.mNode->previousNode;
					insertNode->nextNode = position.mNode;

					// The node that was originally in that position is shifted back one position.
					position.mNode->previousNode = insertNode;

					// The created node is connected to the node that originally existed at that location.
					// If the previous node was a nullptr, the inserted node is assumed to be the first node.
					if ( insertNode->previousNode )
					{
						insertNode->previousNode->nextNode = insertNode;
					}
					else
					{
						this->mHeadNode = insertNode;
					}
					
					// Count up as nodes are created.
					this->mCount++;
				}
			}

			/*!
			* @brief Insert as the first node.
			* @param value: Value to be stored in the node.
			*/
			inline void pushFront( const T& value )
			{
				this->insert( { this->mHeadNode }, value );
			}

			/*!
			* @brief Insert a node at the end of the list.
			* @param value: Value to be stored in the node.
			*/
			inline void pushBack( const T& value )
			{
				this->insert( { this->mLastNode }, value );
			}

			/*!
			* @brief Deletes the node at the specified position.
			* @param position
			*/
			inline void remove( const MfListIterator& position )
			{

				// Used to keep the node before the node to be deleted.
				MfListNode* previousNode = position.mNode->previousNode;
				// Used to hold the node next to the node to be deleted.
				MfListNode* nextNode = position.mNode->nextNode;

				// The concatenation of the node before the one to be deleted with the next node.
				nextNode->previousNode = previousNode;
				if ( previousNode )
				{
					previousNode->nextNode = previousNode;
				}
				else
				{
					// If the node before the one to be deleted is nullptr, the node to be deleted is the first node.
					// Therefore, the node following the node to be deleted is the first node.
					this->mHeadNode = nextNode;
				}

				// Release the memory allocated to the node.
				position.mNode->~MfListNode( );
				this->mListNodePooler.deallocate( position.mNode );

				// Decrease the counter by the number of nodes deleted
				this->mCount--;

			}

			/*!
			* @brief Join list nodes.
			* @param list: A list containing the nodes to be combined.
			*/
			inline void merge( const mf::collections::MfList<T, Allocator>& list )
			{
				for ( auto itr = list.begin( ); itr != list.end( ); itr++ )
				{
					this->pushBack( ( *itr ) );
				}
			}

			/*!
			* @brief Delete all nodes.
			*/
			inline void clear( )
			{
				// Used to store the node to be deleted.
				MfListNode* listNode = this->mHeadNode;

				// Scan all nodes except the terminating node.
				while ( !( listNode == this->mLastNode ) )
				{
					// Used to temporarily store the node next to the node to be deleted.
					MfListNode* nextNode = listNode->nextNode;

					// Release the memory allocated to the node.
					listNode->~MtListNode( );
					this->mListNodePooler( listNode );

					// Replace to delete the next node.
					listNode = nextNode;
				}

				// The terminal node is assumed to be the first node.
				this->mHeadNode = this->mLastNode;

			}

			inline MfListIterator begin( )const
			{
				return { this->mHeadNode };
			}

			inline MfListIterator end( )const
			{
				return { this->mLastNode };
			}

		public:

			/*!
			* @brief Get the number of nodes being created.
			* @return Number of nodes being created.
			*/
			inline const mf::Int32 getCount( )const
			{
				return this->mCount;
			}

			/*!
			* @brief Get the maximum number of nodes to be created.
			* @return Maximum number of nodes that can be created.
			*/
			inline const mf::Int32 getCapacity( )const
			{
				return this->mCapacity;
			}

		public:

			inline mf::collections::MfList<T, Allocator>& operator=( const mf::collections::MfList<T, Allocator>& list )
			{
				// Set the maximum number of elements to be copied from.
				this->mCapacity = list.mCapacity;
				// Re-creation of object pool.
				this->mListNodePooler = mf::collections::MfObjectPooler< MfListNode, Allocator >( this->mCapacity + 1 );
				// Create a termination node.
				this->initialize( );
				// Make a copy of the node.
				this->merge( list );

				return *this;
			}

		};
	}
}

#endif