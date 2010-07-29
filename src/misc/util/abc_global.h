/**CFile****************************************************************

  FileName    [abc_global.h]

  SystemName  [ABC: Logic synthesis and verification system.]

  PackageName [Global declarations.]

  Synopsis    [Global declarations.]

  Author      [Alan Mishchenko]
  
  Affiliation [UC Berkeley]

  Date        [Ver. 1.0. Started - Jan 30, 2009.]

  Revision    [$Id: abc_global.h,v 1.00 2009/01/30 00:00:00 alanmi Exp $]

***********************************************************************/
 
#ifndef __ABC_GLOBAL_H__
#define __ABC_GLOBAL_H__

////////////////////////////////////////////////////////////////////////
///                          INCLUDES                                ///
////////////////////////////////////////////////////////////////////////
 
#ifdef _WIN32
#define inline __inline // compatible with MS VS 6.0
#pragma warning(disable : 4152) // warning C4152: nonstandard extension, function/data pointer conversion in expression
#pragma warning(disable : 4244) // warning C4244: '+=' : conversion from 'int ' to 'unsigned short ', possible loss of data
#pragma warning(disable : 4514) // warning C4514: 'Vec_StrPop' : unreferenced inline function has been removed
#pragma warning(disable : 4710) // warning C4710: function 'Vec_PtrGrow' not inlined
//#pragma warning( disable : 4273 )
#endif

#ifdef WIN32
#define ABC_DLLEXPORT __declspec(dllexport)
#define ABC_DLLIMPORT __declspec(dllimport)
#else  /* defined(WIN32) */
#define ABC_DLLIMPORT
#endif /* defined(WIN32) */

#ifndef ABC_DLL
#define ABC_DLL ABC_DLLIMPORT
#endif

// catch memory leaks in Visual Studio
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#if !defined(___unused)
#if defined(__GNUC__)
#define ___unused __attribute__ ((__unused__))
#else
#define ___unused
#endif
#endif

#include <time.h>
#include <stdarg.h>

////////////////////////////////////////////////////////////////////////
///                         PARAMETERS                               ///
////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////
///                         BASIC TYPES                              ///
////////////////////////////////////////////////////////////////////////

/**
 * Pointer difference type; replacement for ptrdiff_t.
 * This is a signed integral type that is the same size as a pointer.
 * NOTE: This type may be different sizes on different platforms.
 */
#if       defined(__ccdoc__)
typedef platform_dependent_type ABC_PTRDIFF_T;
#elif     defined(LIN64)
typedef long ABC_PTRDIFF_T;
#elif     defined(NT64)
typedef long long ABC_PTRDIFF_T;
#elif     defined(NT) || defined(LIN) || defined(WIN32)
typedef int ABC_PTRDIFF_T;
#else
   #error unknown platform
#endif /* defined(PLATFORM) */

/**
 * Unsigned integral type that can contain a pointer.
 * This is an unsigned integral type that is the same size as a pointer.
 * NOTE: This type may be different sizes on different platforms.
 */
#if       defined(__ccdoc__)
typedef platform_dependent_type ABC_PTRUINT_T;
#elif     defined(LIN64)
typedef unsigned long ABC_PTRUINT_T;
#elif     defined(NT64)
typedef unsigned long long ABC_PTRUINT_T;
#elif     defined(NT) || defined(LIN) || defined(WIN32)
typedef unsigned int ABC_PTRUINT_T;
#else
   #error unknown platform
#endif /* defined(PLATFORM) */

/**
 * Signed integral type that can contain a pointer.
 * This is a signed integral type that is the same size as a pointer.
 * NOTE: This type may be different sizes on different platforms.
 */
#if       defined(__ccdoc__)
typedef platform_dependent_type ABC_PTRINT_T;
#elif     defined(LIN64)
typedef long ABC_PTRINT_T;
#elif     defined(NT64)
typedef long long ABC_PTRINT_T;
#elif     defined(NT) || defined(LIN) || defined(WIN32)
typedef int ABC_PTRINT_T;
#else
   #error unknown platform
#endif /* defined(PLATFORM) */

/**
 * 64-bit signed integral type.
 */
#if       defined(__ccdoc__)
typedef platform_dependent_type ABC_INT64_T;
#elif     defined(LIN64)
typedef long ABC_INT64_T;
#elif     defined(NT64) || defined(LIN)
typedef long long ABC_INT64_T;
#elif     defined(WIN32) || defined(NT)
typedef signed __int64 ABC_INT64_T;
#else
   #error unknown platform
#endif /* defined(PLATFORM) */

/**
 * 64-bit unsigned integral type.
 */
#if       defined(__ccdoc__)
typedef platform_dependent_type ABC_UINT64_T;
#elif     defined(LIN64)
typedef unsigned long ABC_UINT64_T;
#elif     defined(NT64) || defined(LIN)
typedef unsigned long long ABC_UINT64_T;
#elif     defined(WIN32) || defined(NT)
typedef unsigned __int64 ABC_UINT64_T;
#else
   #error unknown platform
#endif /* defined(PLATFORM) */

typedef ABC_UINT64_T word;

////////////////////////////////////////////////////////////////////////
///                      MACRO DEFINITIONS                           ///
////////////////////////////////////////////////////////////////////////


#define ABC_ABS(a)			((a) < 0 ? -(a) : (a))
#define ABC_MAX(a,b)		((a) > (b) ? (a) : (b))
#define ABC_MIN(a,b)		((a) < (b) ? (a) : (b))
#define ABC_INFINITY        (100000000)

#define ABC_PRT(a,t)    (printf("%s = ", (a)), printf("%7.2f sec\n", (float)(t)/(float)(CLOCKS_PER_SEC)))
#define ABC_PRTr(a,t)   (printf("%s = ", (a)), printf("%7.2f sec\r", (float)(t)/(float)(CLOCKS_PER_SEC)))
#define ABC_PRTn(a,t)   (printf("%s = ", (a)), printf("%6.2f sec  ", (float)(t)/(float)(CLOCKS_PER_SEC)))
#define ABC_PRTP(a,t,T) (printf("%s = ", (a)), printf("%7.2f sec (%6.2f %%)\n", (float)(t)/(float)(CLOCKS_PER_SEC), (T)? 100.0*(t)/(T) : 0.0))
#define ABC_PRM(a,f)    (printf("%s = ", (a)), printf("%7.3f Mb  ",    1.0*(f)/(1<<20)))
#define ABC_PRMP(a,f,F) (printf("%s = ", (a)), printf("%7.3f Mb (%6.2f %%)  ",  (1.0*(f)/(1<<20)), ((F)? 100.0*(f)/(F) : 0.0) ) )

//#define ABC_USE_MEM_REC 1

#ifndef ABC_USE_MEM_REC
#define ABC_ALLOC(type, num)	 ((type *) malloc(sizeof(type) * (num)))
#define ABC_CALLOC(type, num)	 ((type *) calloc((num), sizeof(type)))
#define ABC_FALLOC(type, num)	 ((type *) memset(malloc(sizeof(type) * (num)), 0xff, sizeof(type) * (num)))
#define ABC_FREE(obj)		     ((obj) ? (free((char *) (obj)), (obj) = 0) : 0)
#define ABC_REALLOC(type, obj, num)	\
        ((obj) ? ((type *) realloc((char *)(obj), sizeof(type) * (num))) : \
	     ((type *) malloc(sizeof(type) * (num))))
#else
#include "utilMem.h"
#define ABC_ALLOC(type, num)	 ((type *) Util_MemRecAlloc(malloc(sizeof(type) * (num))))
#define ABC_CALLOC(type, num)	 ((type *) Util_MemRecAlloc(calloc((num), sizeof(type))))
#define ABC_FALLOC(type, num)	 ((type *) memset(Util_MemRecAlloc(malloc(sizeof(type) * (num))), 0xff, sizeof(type) * (num)))
#define ABC_FREE(obj)		     ((obj) ?  (free((char *) Util_MemRecFree(obj)), (obj) = 0) : 0)
#define ABC_REALLOC(type, obj, num)	\
        ((obj) ? ((type *) Util_MemRecAlloc(realloc((char *)(Util_MemRecFree(obj)), sizeof(type) * (num)))) : \
	     ((type *) Util_MemRecAlloc(malloc(sizeof(type) * (num)))))
#endif


enum Abc_VerbLevel 
{
    ABC_PROMPT   = -2, 
    ABC_ERROR    = -1, 
    ABC_WARNING  =  0, 
    ABC_STANDARD =  1, 
    ABC_VERBOSE  =  2 
}; 

static inline void Abc_Print( int level, char * format, ... ) 
{
    va_list args;
//    if ( level > -2 )
//        return;
    if ( level == ABC_ERROR ) 
        printf( "Error: " );
    else if ( level == ABC_WARNING ) 
        printf( "Warning: " );
    va_start( args, format );
    vprintf( format, args );
    va_end( args );
} 

static inline void Abc_PrintTime( int level, char * pStr, int time ) 
{
    if ( level == ABC_ERROR ) 
        printf( "Error: " );
    else if ( level == ABC_WARNING ) 
        printf( "Warning: " );
    ABC_PRT( pStr, time );
}

static inline void Abc_PrintTimeP( int level, char * pStr, int time, int Time ) 
{
    if ( level == ABC_ERROR ) 
        printf( "Error: " );
    else if ( level == ABC_WARNING ) 
        printf( "Warning: " );
    ABC_PRTP( pStr, time, Time );
}

static inline void Abc_PrintMemoryP( int level, char * pStr, int time, int Time ) 
{
    if ( level == ABC_ERROR ) 
        printf( "Error: " );
    else if ( level == ABC_WARNING ) 
        printf( "Warning: " );
    ABC_PRMP( pStr, time, Time );
}


// sequential counter-example
typedef struct Abc_Cex_t_   Abc_Cex_t;
struct Abc_Cex_t_
{
    int              iPo;               // the zero-based number of PO, for which verification failed
    int              iFrame;            // the zero-based number of the time-frame, for which verificaiton failed
    int              nRegs;             // the number of registers in the miter 
    int              nPis;              // the number of primary inputs in the miter
    int              nBits;             // the number of words of bit data used
    unsigned         pData[0];          // the cex bit data (the number of bits: nRegs + (iFrame+1) * nPis)
};

#ifdef __cplusplus
}
#endif

#endif

////////////////////////////////////////////////////////////////////////
///                       END OF FILE                                ///
////////////////////////////////////////////////////////////////////////

