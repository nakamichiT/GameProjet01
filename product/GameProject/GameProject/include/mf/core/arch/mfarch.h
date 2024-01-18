/*---------------------------------------------------------------------------
* @file: mfarch.h
* @author: T.Nakamichi
* @brief: Define the architecture to be supported.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_ARCH_H___
#define ___MF_CORE_ARCH_H___

/*******************************************************
* include file
********************************************************/

/*******************************************************
* macro.
********************************************************/

/* Windows. */
#if defined(_WIN32) || defined(_WIN64)
/* Supported architecture */
#if defined (_M_X64)
#define MF_CPU_64 (1)
#elif defined (_M_IX86)
#define MT_CPU_32 (1)
#elif defined (_M_ARM)
#define MT_CPU_32 (1)
#else
#error Unsupported architecture!
#endif
#endif

#endif