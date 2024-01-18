/*---------------------------------------------------------------------------
* @file: mftype.h
* @author: T.Nakamichi
* @brief: Define the data type.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_ARCH_TYPE_H___
#define ___MF_CORE_ARCH_TYPE_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mfarch.h"

/*******************************************************
* macro.
********************************************************/

namespace mf
{

	using Int8 = signed __int8;
	using Int16 = signed __int16;
	using Int32 = signed __int32;
	using Int64 = signed __int64;

	using Uint8 = unsigned __int8;
	using Uint16 = unsigned __int16;
	using Uint32 = unsigned __int32;
	using Uint64 = unsigned __int64;

	class MfObject;

#if defined MF_CPU_64
	using Size_T = mf::Uint64;
#else
	using Size_T = mf::Uint32;
#endif

	using ObjectId = mf::Size_T;

}

#endif