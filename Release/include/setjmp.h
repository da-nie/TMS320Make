/*****************************************************************************/
/* setjmp.h V5.11 for TMS3203x/4x                                           */
/* Copyright (c) 1992-1999 Texas Instruments Inc.                            */
/*****************************************************************************/
#ifndef _SETJMP
#define _SETJMP

typedef long jmp_buf[12];

#define setjmp(_x) _setjmp(_x)
void longjmp(jmp_buf _env, int _returnval); 

#endif
