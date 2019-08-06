/*****************************************************************************/
/* string.h V5.11 for TMS3203x/4x                                           */
/* Copyright (c) 1992-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/
#ifndef _STRING
#define _STRING

#ifndef NULL
#define NULL 0
#endif

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

#if defined(_INLINE)
# define __INLINE static inline
#else
# define __INLINE
#endif

/****************************************************************************/
/* FUNCTION DEFINITIONS                                                     */
/****************************************************************************/
__INLINE void   *memchr(const void *_mem, int _ch, size_t _length);
__INLINE int     memcmp(const void *_mem1, const void *_mem2, size_t _length);
__INLINE void   *memcpy(void *_s1, const void *_s2, size_t _n);
         void   *memmove(void *_s1, const void *_s2, size_t _n);
__INLINE void   *memset(void *_s, int _c, size_t _n);

__INLINE char   *strcat(char *_string1, const char *_string2);
__INLINE char   *strchr(const char *_string, int _ch);
__INLINE int     strcmp(const char *_string1, const char *_string2);
__INLINE char   *strcpy(char *_to, const char *_from);
         int     strcoll(const char *_string1, const char *_string2);
         size_t  strcspn(const char *_string, const char *_chs);
         char   *strerror(int _errno);
__INLINE size_t  strlen(const char *_string);
         char   *strncat(char *_to, const char *_from, size_t _n);
         int     strncmp(const char *_string1, const char *_string2, size_t _n);
         char   *strncpy(char *_to, const char *_from, size_t _n);
         char   *strpbrk(const char *_string, const char *_chs);
__INLINE char   *strrchr(const char *_string, int _ch);
         size_t  strspn(const char *_string, const char *_chs);
         char   *strstr(const char *_string1, const char *_string2);
         char   *strtok(char *_str1, const char *_str2);
         size_t  strxfrm(char *_to, const char *_from, size_t _n);

#if  defined(_INLINE)
/****************************************************************************/
/*  memchr()                                                                */
/****************************************************************************/
static inline void *memchr(const void *cs, int c, size_t n)
{
   size_t length;

   if ( (length=n) > 0 )
   {
      const unsigned char *mem = cs;   
      unsigned char       ch   = c;

      do if ( *mem++ == ch ) return (void *)(mem - 1);
      while (--length != 0);
   }
   
   return (void *)NULL;
}

/****************************************************************************/
/*  memcmp()       				                            */
/****************************************************************************/
static inline int memcmp(const void *mem1, const void *mem2, size_t length)
{
   const char *r1 = (char *)mem1 - 1;
   const char *r2 = (char *)mem2 - 1;

   for(;;)
     if      ( --length == -1 ) break;
     else if ( *++r1 != *++r2 ) return *r1 - *r2;

   return 0;
}

/****************************************************************************/
/*  memcpy()         						            */
/****************************************************************************/
static inline void *memcpy(void *s, const void *ct, size_t n)
{
   char   *from, *to;
   size_t length;

   if ( (length=n) > 0 )
   {
      from = (char *)ct;  
      to   = (char *)s;
      do *to++ = *from++; while (--length != 0);
   }

   return (void *)s;
}

/****************************************************************************/
/*  memset()                                                                */
/****************************************************************************/
static inline void *memset(void *s, int c, size_t n)
{
   size_t length;

   if ( (length=n) > 0 )
   {
      char          *mem = s;
      unsigned char ch   = c;

      do *mem++ = ch; while (--length != 0);
   }

   return (void *)s;
}

/****************************************************************************/
/*  strcat()                                                                */
/****************************************************************************/
static inline char *strcat(char *dest, const char *src)
{
   char *r1 = dest - 1;

   while (*++r1);		     /* FIND END OF STRING   */
   while ((*r1++ = *src++) != 0);    /* APPEND SECOND STRING */
   return dest;
}

/****************************************************************************/
/*  strchr()                                                                */
/****************************************************************************/
static inline char *strchr(const char *string, int ch)
{
   char *str = (char *)string - 1;
   int   tch;

   for (;;)
     if      ( (tch = *++str) == ch ) return str;
     else if ( tch == 0 ) return NULL;
}

/****************************************************************************/
/*  strcmp()                                                                */
/****************************************************************************/
static inline int strcmp(const char *string1, const char *string2)
{
   char *r1 = (char *)string1 - 1;
   char *r2 = (char *)string2 - 1;
   char cp;

   while ( (*++r2 == (cp = *++r1)) && cp );

   return *r1 - *r2;
}

/****************************************************************************/
/*  strcpy()                                                                */
/****************************************************************************/
static inline char *strcpy(char *dest, const char *src)
{
   char *result = dest;

   while ((*dest++ = *src++) != 0);
   return result;
}

/****************************************************************************/
/*  strlen()                                                                */
/****************************************************************************/
static inline size_t strlen(const char *string)
{
   const char *r1 = string - 1;
   while (*++r1);
   return r1 - string;
}

/****************************************************************************/
/*  strrchr()                                                               */
/****************************************************************************/
static inline char *strrchr(const char *string, int c)
{
   char tch, ch;
   char *result;

   --string;
   ch     = c;
   result = (char *)0;

   for (;;)
   {
      if ((tch = *++string) == ch) result = (char*)string;
      if (tch == 0) break;
   }

   return result;
}
#endif /* _INLINE */
#undef __INLINE

#endif /* _STRING */
