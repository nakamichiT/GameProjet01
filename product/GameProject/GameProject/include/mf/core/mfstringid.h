/*---------------------------------------------------------------------------
* @file: mfstringid.h
* @author: T.Nakamichi
* @brief: Define a class that creates and holds hash values from strings.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_STRINGID_H___
#define ___MF_CORE_STRINGID_H___

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
	* @brief A class that creates and holds a hash value from a string.
	*/
	class MfStringId
	{
	private:

		/*!
		* @brief Used to hold the id created from the specified string.
		*/
		mf::Int64 mStringId;

	public:

		/*!
		* @brief Constructer.
		*/
		MfStringId( );

		/*!
		* @brief Constructer.
		* @param string: String used to create the id.
		*/
		MfStringId( const char* string );

		/*!
		* @brief Constructer.
		* @param string: String used to create the id.
		*/
		MfStringId( const wchar_t* string );

	public:

		inline bool operator >( const mf::MfStringId& mfStringId )const
		{
			return this->mStringId > mfStringId.mStringId;
		}

		inline bool operator <( const mf::MfStringId& mfStringId )const
		{
			return this->mStringId < mfStringId.mStringId;
		}

		inline bool operator ==( const mf::MfStringId& mfStringId )const
		{
			return this->mStringId == mfStringId.mStringId;
		}

		inline bool operator !=( const mf::MfStringId& mfStringId )const
		{
			return !( *this == mfStringId );
		}

	};

}

#endif