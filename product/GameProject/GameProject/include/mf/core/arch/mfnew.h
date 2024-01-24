/*---------------------------------------------------------------------------
* @file: mfnew.h
* @author: T.Nakamichi
* @brief: 
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_ARCH_NEW_H___
#define ___MF_CORE_ARCH_NEW_H___

/*******************************************************
* include file
********************************************************/
#include <new>
#include "mf/core/arch/mfmalloc.h"

namespace mf
{

	/*!
	* @brief Instance Creation.
	* @return Instances created. If creation fails, nullptr is returned.
	*/
	template < class T >
	T* MfNew( )
	{
		// Used to hold the created instance
		T* instance = nullptr;
		// Allocate memory necessary for instance creation.
		// (*Create an instance only if the allocation is successful.)
		if ( void* memory = mf::MfMalloc( sizeof( T ) ) )
		{
			instance = new ( memory ) T( );
		}
		return instance;
	}

	/*!
	* @brief Instance Creation.
	* @param arg1: Constructer argument.
	* @return Instances created. If creation fails, nullptr is returned.
	*/
	template < class T, class Arg1>
	T* MfNew( Arg1 arg1 )
	{
		// Used to hold the created instance
		T* instance = nullptr;
		// Allocate memory necessary for instance creation.
		// (*Create an instance only if the allocation is successful.)
		if ( void* memory = mf::MfMalloc( sizeof( T ) ) )
		{
			instance = new ( memory ) T( arg1 );
		}
		return instance;
	}

	/*!
	* @brief Instance Creation.
	* @param arg1: Constructer argument.
	* @param arg2: Constructer argument.
	* @return Instances created. If creation fails, nullptr is returned.
	*/
	template < class T, class Arg1, class Arg2>
	T* MfNew( Arg1 arg1, Arg2 arg2 )
	{
		// Used to hold the created instance
		T* instance = nullptr;
		// Allocate memory necessary for instance creation.
		// (*Create an instance only if the allocation is successful.)
		if ( void* memory = mf::MfMalloc( sizeof( T ) ) )
		{
			instance = new ( memory ) T( arg1, arg2 );
		}
		return instance;
	}

	/*!
	* @brief Instance Creation.
	* @param arg1: Constructer argument.
	* @param arg2: Constructer argument.
	* @param arg3: Constructer argument.
	* @return Instances created. If creation fails, nullptr is returned.
	*/
	template < class T, class Arg1, class Arg2, class Arg3>
	T* MfNew( Arg1 arg1, Arg2 arg2, Arg3 arg3 )
	{
		// Used to hold the created instance
		T* instance = nullptr;
		// Allocate memory necessary for instance creation.
		// (*Create an instance only if the allocation is successful.)
		if ( void* memory = mf::MfMalloc( sizeof( T ) ) )
		{
			instance = new ( memory ) T( arg1, arg2, arg3 );
		}
		return instance;
	}

	/*!
	* @brief Release instances created using MfNew function.
	* @param instance: Instances created using MfNew function.
	*/
	template < class T >
	void MfDelete( T*& instance )
	{
		// Check if the specified instance is not nullptr
		if ( instance )
		{
			// Destructor Calls
			instance->~T( );
			// Deallocation of memory used to create the instance
			mf::MfFree( instance );
			instance = nullptr;
		}
	}

}

/*******************************************************
* macro.
********************************************************/
#define MF_FRIEND_NEW() \
template < class T >\
friend T* mf::MfNew();\
template < class T, class Arg1>\
friend T* mf::MfNew(Arg1 arg1);\
template < class T, class Arg1, class Arg2>\
friend T* mf::MfNew(Arg1 arg1, Arg2 arg2);\
template < class T, class Arg1, class Arg2, class Arg3>\
friend T* mf::MfNew(Arg1 arg1, Arg2 arg2, Arg3 arg3);\
template < class T >\
friend void mf::MfDelete(T*& instance);\

#endif