/*****************************************************************************/
/* stdarg.h V5.11 for TMS3203x/4x                                           */
/* Copyright (c) 1992-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/
#ifndef _STDARG
#define _STDARG

typedef char *va_list;

#define va_start(_ap, _parmN) (_ap = (char *)&_parmN)
#define va_end(_ap)
#define va_arg(_ap, _type)    ((_ap -= (sizeof(_type) > sizeof(int)) ? \
				        sizeof(_type) : sizeof(int)),  \
				        (*(_type *)(_ap)))
#endif
