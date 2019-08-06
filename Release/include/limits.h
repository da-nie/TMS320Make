/*****************************************************************************/
/* limits.h V5.11 for TMS3203x/4x                                           */
/* Copyright (c) 1992-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/
#ifndef _LIMITS
#define _LIMITS

#define CHAR_BIT    32
#define SCHAR_MAX   2147483647
#define SCHAR_MIN   (-SCHAR_MAX-1)
#define CHAR_MAX    2147483647
#define CHAR_MIN    (-CHAR_MAX-1)
#define UCHAR_MAX   4294967295u
 
#define SHRT_MAX    2147483647
#define SHRT_MIN    (-SHRT_MAX-1)
#define USHRT_MAX   4294967295u

#define INT_MAX     2147483647
#define INT_MIN     (-INT_MAX-1)
#define UINT_MAX    4294967295u

#define LONG_MAX    2147483647L
#define LONG_MIN    (-LONG_MAX-1)
#define ULONG_MAX   4294967295uL

#define  MB_LEN_MAX (1)

#endif
