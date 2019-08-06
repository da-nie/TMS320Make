/*****************************************************************************/
/* intrin.h V5.11 for TMS3203x/4x                                           */
/* Copyright (c) 1997-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/
#ifndef _INTRIN_H
#define _INTRIN_H 1

/*---------------------------------------------------------------------------*/
/* This file defines the intrinsic functions available on the C3x/C4x tools  */
/*---------------------------------------------------------------------------*/
extern int    abs(int);           /* Integer Absolute                        */
extern long   labs(long);         /* Long Integer Absolute                   */
extern double fabs(double);       /* Floating Point Absolute                 */

extern int    fast_ftoi(float);   /* Fast Float-to-Int Conversion            */
extern int    ansi_ftoi(float);   /* ANSI Float-to-Int Conversion            */

#if defined(_C3x)
extern int    fast_imult(int,int); /* Fast 24-bit multiplication via MPYI     */
#endif

#if defined(_C4x)
extern double toieee(double);     /* Float to IEEE conversion                */
extern double frieee(double);     /* IEEE to float conversion                */
extern int    fast_invf(float);   /* Fast 16-bit reciprocal via RCPF         */
#endif

#endif
