/*****************************************************************************/
/* stddef.h V5.11 for TMS3203x/4x                                           */
/* Copyright (c) 1992-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/
#ifndef _STDDEF 
#define _STDDEF 

typedef int ptrdiff_t;

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#ifndef _WCHAR_T
#define _WCHAR_T
typedef char wchar_t;
#endif

#define offsetof(_type, _ident) ((size_t)(&((_type *)0)->_ident))

#ifndef NULL
#define NULL 0
#endif

#endif
