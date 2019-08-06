/*****************************************************************************/
/* ctype.h V5.11 for TMS3203x/4x                                            */
/* Copyright (c) 1992-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/
/************************************************************************/
/*                                                                      */
/*  CHARACTER TYPING FUNCTIONS AND MACROS                               */
/*                                                                      */
/*  Note that in this implementation, either macros or functions may    */
/*  be used.  Macros are prefixed with an underscore.                   */
/*                                                                      */
/************************************************************************/
#ifndef _CTYPE
#define _CTYPE

extern unsigned char _ctypes_[];

#if defined(_INLINE)
# define __INLINE static inline
#else
# define __INLINE
#endif

/************************************************************************/
/*   FUNCTION DEFINITIONS                                               */
/************************************************************************/
__INLINE int isalnum(int _c);
__INLINE int isalpha(int _c);
__INLINE int iscntrl(int _c);
__INLINE int isdigit(int _c);
__INLINE int isgraph(int _c);
__INLINE int islower(int _c);
__INLINE int isprint(int _c);
__INLINE int ispunct(int _c);
__INLINE int isspace(int _c);
__INLINE int isupper(int _c);
__INLINE int isxdigit(int _c);
__INLINE int isascii(int _c);

__INLINE int toupper(int _c);
__INLINE int tolower(int _c);
__INLINE int toascii(int _c);

/************************************************************************/
/*  MACRO DEFINITIONS                                                   */
/************************************************************************/
#define _UC_   0x01           /* UPPER CASE  */
#define _LC_   0x02           /* LOWER CASE  */
#define _NM_   0x04           /* NUMERICAL   */
#define _SP_   0x08           /* SPACE       */
#define _PU_   0x10           /* PUNCTUATION */
#define _CL_   0x20           /* CONTROL     */
#define _HX_   0x40           /* HEX DIGIT   */
#define _BL_   0x80           /* BLANK       */

#define _isalnum(a)  (_ctypes_[(a)+1] & (_UC_ | _LC_ | _NM_))
#define _isalpha(a)  (_ctypes_[(a)+1] & (_UC_ | _LC_))
#define _iscntrl(a)  (_ctypes_[(a)+1] & _CL_)
#define _isdigit(a)  (_ctypes_[(a)+1] & _NM_)
#define _isgraph(a)  (_ctypes_[(a)+1] & (_UC_ | _LC_ | _NM_ | _PU_))
#define _islower(a)  (_ctypes_[(a)+1] & _LC_)
#define _isprint(a)  (_ctypes_[(a)+1] & (_BL_ | _UC_ | _LC_ | _NM_ | _PU_))
#define _ispunct(a)  (_ctypes_[(a)+1] & _PU_)
#define _isspace(a)  (_ctypes_[(a)+1] & _SP_)
#define _isupper(a)  (_ctypes_[(a)+1] & _UC_)
#define _isxdigit(a) (_ctypes_[(a)+1] & _HX_)
#define _isascii(a)  (((a) & ~0x7F) == 0)

#define _toupper(b)  ((_islower(b)) ? (b) - ('a' - 'A') : (b))
#define _tolower(b)  ((_isupper(b)) ? (b) + ('a' - 'A') : (b))
#define _toascii(a)  ((a) & 0x7F)

#if defined(_INLINE)
static inline int isalnum(int c)  { return(_isalnum(c));  }
static inline int isalpha(int c)  { return(_isalpha(c));  }
static inline int isascii(int c)  { return(_isascii(c));  }
static inline int iscntrl(int c)  { return(_iscntrl(c));  }
static inline int isdigit(int c)  { return(_isdigit(c));  }
static inline int isgraph(int c)  { return(_isgraph(c));  }
static inline int islower(int c)  { return(_islower(c));  }
static inline int isprint(int c)  { return(_isprint(c));  }
static inline int ispunct(int c)  { return(_ispunct(c));  }
static inline int isspace(int c)  { return(_isspace(c));  }
static inline int isupper(int c)  { return(_isupper(c));  }
static inline int isxdigit(int c) { return(_isxdigit(c)); }
static inline int toascii(int c)  { return(_toascii(c));  }

static inline int tolower(int ch)
{
   int ch2 = ch + ('a' - 'A');
   return ( (unsigned int)(ch - 'A') <= (unsigned int)('Z' - 'A')) ? ch2 : ch;
}

static inline int toupper(int ch)
{
   int ch2 = ch + ('A' - 'a');
   return ( (unsigned int)(ch - 'a') <= (unsigned int)('z' - 'a')) ? ch2 : ch;
}

#endif /* _INLINE_ */
#undef __INLINE

#endif /* _CTYPE */
