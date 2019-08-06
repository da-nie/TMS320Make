/*****************************************************************************/
/* assert.h V5.11 for TMS3203x/4x                                           */
/* Copyright (c) 1992-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/
#ifndef _ASSERT
#define _ASSERT

void _nassert(int), _assert(int, char *);
void _abort_msg(char*);
void abort(void);

#define _STR(x)  __STR(x)
#define __STR(x) #x

#if defined(NDEBUG)
#define assert(_ignore) ((void)0)

#elif defined(NASSERT)
#define assert(_expr)	_nassert(_expr)

#else
#include <stdio.h>
#include <stdlib.h>

#define assert(_expr)	((_expr) ? (void)0 :                             \
(fprintf(stderr, \
	"Assertion failed, (%s), file %s, line %d\n", _STR(_expr), \
	__FILE__, __LINE__), \
(void)abort())\
)

#endif
#endif
