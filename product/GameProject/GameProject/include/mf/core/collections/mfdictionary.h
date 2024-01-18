/*---------------------------------------------------------------------------
* @file: mfdictionary.h
* @author: T.Nakamichi
* @brief: Define a list class.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_COLLECTIONS_DICTIONARY_H___
#define ___MF_CORE_COLLECTIONS_DICTIONARY_H___

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

		template < class Key, class Val, class Allocator = mf::collections::memories::MfAllocator >
		class MfDictionary
		{
		private:

			/*!
			* @brief A structure for holding information on a single node.
			*/ 
			struct MfDictionaryNode
			{
				/*!
				* @brief Used to hold a pointer to the left node.
				*/
				MfDictionaryNode* leftNode = nullptr;

				/*!
				* @brief Used to hold a pointer to the right node.
				*/
				MfDictionaryNode* rightNode = nullptr;

				/*!
				* @brief Node used for iteration.
				*/
				MfDictionaryNode* previousNode = nullptr;

				/*!
				* @brief Node used for iteration.
				*/
				MfDictionaryNode* nextNode = nullptr;

				/*!
				* @brief Key to access the node.
				*/
				Key key;

				/*!
				* @brief value.
				*/
				Val value;

			};

		public:

			/*!
			* @brief  A structure that holds the specified value type and key type and allows the user simplified access to the target node when using the iterator.
			*/
			struct MfDictionarySet
			{
				/*!
				* @brief A reference to the value held by the node.
				*/
				Val& value;

				/*!
				* @brief Key of the node.
				*/
				const Key& key;
			};

			/*!
			* @brief 
			*/
			struct MfDictionaryIterator
			{

				friend MfDictionary;

			private:

				/*!
				* @brief  Used to hold a node.
				*/
				MfDictionaryNode* mNode = nullptr;

			public:

				/*!
				* @brief Constructer
				*/
				MfDictionaryIterator( MfDictionaryNode* node ) :
					mNode( node )
				{
				}

			public:

				bool operator == ( const MfDictionaryIterator& iterator )const
				{
					return this->mNode == iterator.mNode;
				}

				bool operator!=( const MfDictionaryIterator& iterator )const
				{
					return !( *this == iterator );
				}

				MfDictionaryIterator& operator++( )
				{
					this->mNode = this->mNode->nextNode;
					return *this;
				}

				MfDictionaryIterator operator++( int )
				{
					MfDictionaryIterator iterator = *this;
					++*this;
					return iterator;
				}

				MfDictionaryIterator& operator--( )
				{
					this->mNode = this->mNode->previousNode;
					return *this;
				}

				MfDictionaryIterator operator--( int )
				{
					MfDictionaryIterator iterator = *this;
					--*this;
					return iterator;
				}

				MfDictionarySet operator *( )
				{
					return { this->mNode->value, this->mNode->key };
				}

			};

		private:


			/*!
			* @brief Object pool used for node creation. Used to create a node or destroy a node.
			*/
			mf::collections::MfObjectPooler<MfDictionaryNode, Allocator> mDictionaryNodePooler;

			/*!
			* @brief Number of nodes managed by the container.
			*/
			mf::Int32 mCount;

			/*!
			* @brief Maximum number of elements in a node.
			*/
			mf::Int32 mCapacity;
			
			/*!
			* @brief Tree root node.
			*/
			MfDictionaryNode* mRootNode;
			 
			/*!
			* @brief The first node in the iteration list.
			*/
			MfDictionaryNode* mHeadNode;
			
			/*!
			* @brief The end node of the iteration list.
			*/
			MfDictionaryNode* mLastNode;

		public:

			/*!
			* @brief Constructer
			*/
			MfDictionary( ) :
				mDictionaryNodePooler( ),
				mCount( 0 ),
				mCapacity( 0 ),
				mRootNode( nullptr ),
				mHeadNode( nullptr ),
				mLastNode( nullptr )
			{
			}

			/*!
			* @brief Constructer
			* @param capacity: Maximum number of elements
			*/
			MfDictionary( mf::Int32 capacity ) :
				mDictionaryNodePooler( capacity + 1 ),
				mCount( 0 ),
				mCapacity( capacity ),
				mRootNode( nullptr ),
				mHeadNode( nullptr ),
				mLastNode( nullptr )
			{
				this->initialize( );
			}

			/*!
			* @brief Constructer
			* @param capacity: Maximum number of elements
			* @param allocator: Allocator used to create nodes.
			*                                 Must retain at least the specified 'capacity + 1' memory size.
			*/
			MfDictionary( mf::Int32 capacity, const Allocator& allocator ) :
				mDictionaryNodePooler( capacity + 1, allocator ),
				mCount( 0 ),
				mCapacity( capacity ),
				mRootNode( nullptr ),
				mHeadNode( nullptr ),
				mLastNode( nullptr )
			{
				this->initialize( );
			}

			/*!
			* @brief Copy constructer.
			* @param dictionary:
			*/
			MfDictionary( const mf::collections::MfDictionary< Key, Val, Allocator >& dictionary ) :
				mDictionaryNodePooler( dictionary.getCapacity( ) ),
				mCount( 0 ),
				mCapacity( dictionary.getCapacity( ) ),
				mRootNode( nullptr ),
				mHeadNode( nullptr ),
				mLastNode( nullptr )
			{
				this->initialize( );
				this->merge( dictionary );
			}

		private:

			/*!
			* @brief Create a dummy (terminal) node.
			*/
			void initialize( )
			{
				// Allocate the memory needed to create the node.
				if ( void* memory = this->mDictionaryNodePooler.allocate( ) )
				{
					// Creation of terminal nodes.
					MfDictionaryNode* node = new ( memory ) MfDictionaryNode;
					// The created node is set as the first and last node for the iteration list.
					this->mHeadNode = this->mLastNode = node;
				}
			}

			/*!
			* @brief A new node is created and added to the node specified by the argument. If the specified node is nullptr, the created node is assumed to be the root node.
			* @param key: Key of the node.
			* @param previousNode: Parent node to which the new node will be added.
			* @return Pointer to the created node. If creation fails, nullptr is returned.
			*/
			MfDictionaryNode* internalCreateNode( const Key& key, MfDictionaryNode* previousNode )
			{
				// Used to hold the created node.
				MfDictionaryNode* node = nullptr;

				// Allocate the memory needed to create the node.
				if ( void* memory = this->mDictionaryNodePooler.allocate( ) )
				{
					// Creates a node to hold the specified value and key.
					node = new ( memory )MfDictionaryNode( );

					// If no parent node is specified, it is created as the root node.
					// If a parent node is specified, it is created as a child node.
					if ( previousNode == nullptr )
					{
						// Root node configuration.
						this->mRootNode = node;
						// Set as the first node in the iteration list.
						this->mHeadNode = node;
						// Iteration list node concatenation.
						this->mHeadNode->nextNode = this->mLastNode;
						this->mLastNode->previousNode = this->mHeadNode;
					}
					else
					{
						// Check the destination of the node to be added and concatenate the created node with the specified parent node.
						if ( previousNode->key > key )
						{
							previousNode->leftNode = node;
						}
						else
						{
							previousNode->rightNode = node;
						}

						// Iteration list node concatenation.
						node->previousNode = this->mLastNode->previousNode;
						this->mLastNode->previousNode->next = node;

						node->nextNode = this->mLastNode;
						this->mLastNode->previousNode = node;

					}
					// Set the key of the node.
					node->key = key;
					// Count up the nodes created.
					this->mCount++;
				}
				return node;
			}

			/*!
			* @brief  Verifies whether there is a node with the same value as the specified key.
			* @param key: Key used for verification.
			* @param searchEndNode: Used to hold the final verification node.
			* @param A node with the same value as the specified key. If not found, nullptr is returned.
			*/
			MfDictionaryNode* internalIsExistKey( const Key& key, MfDictionaryNode*& searchEndNode )const
			{
				// Used to hold nodes with the same key.
				MfDictionaryNode* node = nullptr;
				// Used to search for nodes.
				MfDictionaryNode* temp = this->mRootNode;

				// Finds a node with the same key as the specified key from the root node.
				while ( temp )
				{
					if ( temp->key > key )
					{
						if ( temp->leftNode == nullptr )
						{
							break;
						}
						else
						{
							temp = temp->leftNode;
						}
					}
					else if ( temp->key < key )
					{
						if ( temp->rightNode == nullptr )
						{
							break;
						}
						else
						{
							temp = temp->rightNode;
						}
					}
					else
					{
						node = temp;
						break;
					}
				}

				// Set the final search node.
				searchEndNode = temp;

				return node;
			}

		public:

			/*!
			* @brief Insert element.
			* @param key:
			* @param val:
			*/
			void insert( const Key& key, const Val& val )
			{
				// Used to hold the parent node to which the node will be added.
				MfDictionaryNode* position = nullptr;

				// Search for a parent node and check for a node with the same name.
				if ( this->internalIsExistKey( key, position ) == nullptr )
				{
					// Create a new node.
					if ( MfDictionaryNode* node = this->internalCreateNode( key, position ) )
					{
						// Set the value of the node.
						node->value = val;
					}
				}
			}

			/*!
			* @brief Obtains the value registered in the node corresponding to the specified key.
			* @param key: Key of the node to be retrieved
			* @param val: Used to store values obtained from nodes.
			*/
			void containts( const Key& key, Val* val )
			{
				// 要素の挿入場所を格納するために使用する
				// （※今回は使用しない）
				MfDictionaryNode* position = nullptr;

				// 同じキー名のノードを取得する
				if ( MfDictionaryNode* node = this->internalIsExistKey( key, position ) )
				{
					val = &node->value;
				}
			}

			/*!
			* @brief 
			*/
			void remove( const Key& key )
			{
			}

			/*!
			* @brief 
			*/
			void clear( )
			{
			}

			/*!
			* @brief Verifies whether the specified key exists.
			* @param key: Key to verify.
			* @return true: exists / false: does not exist 
			*/
			bool isKeyExist( const Key& key )const
			{
				MfDictionaryNode* node = nullptr;
				return this->internalIsExistKey( key, node ) ? true : false;
			}

			/*!
			* @brief Combines each node in the specified hash map.
			*           If a key with the same name already exists, no node registration is performed.
			* @param dictionary:
			*/
			void merge( const mf::collections::MfDictionary<Key, Val, Allocator>& dictionary )
			{
				for ( auto itr = dictionary.begin( ); itr != dictionary.end( ); itr++ )
				{
					this->insert( ( *itr ).key, ( *itr ).value );
				}
			}

		public:

			/*!
			* @brief Get the maximum number of nodes that can be created
			* @return Maximum number of nodes that can be created.
			*/
			mf::Int32 getCapacity( )const
			{
				return this->mCapacity;
			}

			MfDictionaryIterator begin( )const
			{
				return { this->mHeadNode };
			}

			MfDictionaryNode end( )const
			{
				return { this->mLastNode };
			}

		public:

			/*!
			* @brief operator=
			*/
			mf::collections::MfDictionary< Key, Val, Allocator >& operator= ( const mf::collections::MfDictionary< Key, Val, Allocator >& dictionary )
			{
				// Set the maximum number of elements to be copied from.
				this->mCapacity = dictionary.mCapacity;
				// Re-creation of object pool.
				this->mDictionaryNodePooler = mf::collections::MfObjectPooler<MfDictionaryNode, Allocator>( this->mCapacity + 1 );

				// Create a termination node.
				this->initialize( );
				this->merge( dictionary );

				return *this;
			}

		};
	}
}

#endif