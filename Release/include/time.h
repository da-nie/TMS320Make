/*****************************************************************************/
/* time.h V5.11 for TMS3203x/4x                                             */
/* Copyright (c) 1992-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/
#ifndef _TIME
#define _TIME

#define CLOCKS_PER_SEC 1000

#ifndef NULL
#define NULL           0
#endif

typedef unsigned long clock_t;
typedef unsigned long time_t;

#ifndef _SIZE_T
#define _SIZE_T
typedef unsigned size_t;
#endif

/*************************************************************************/
/* STRUCTURE DEFINITION FOR BROKEN-SOWN_TIME                             */
/*************************************************************************/
struct tm {
	    int          tm_sec;    /* seconds after the minute   - [0,59]  */
	    int          tm_min;    /* minutes after the hour     - [0,59]  */
	    int          tm_hour;   /* hours after the midnight   - [0,23]  */
	    int          tm_mday;   /* day of the month           - [1,31]  */
	    int          tm_mon;    /* months since January       - [0,11]  */
	    int          tm_year;   /* years since 1900                     */
	    int          tm_wday;   /* days since Sunday          - [0,6]   */
	    int          tm_yday;   /* days since Jan 1st         - [0,365] */
	    int          tm_isdst;  /* Daylight Savings Time flag           */
	  };

/*************************************************************************/
/* TIME ZONE STRUCTURE DEFINITION                                        */
/*************************************************************************/
struct tmzone
	  {
            short        daylight;  /* True if daylight savings time        */
	    long         timezone;  /* Number of seconds behind GMT         */
	    char         tzname[4]; /* Name of timezone, e.g. CST           */
	    char         dstname[4];/* Name when daylight true, e.g. EDT    */
          };

extern struct tmzone _tz;

clock_t    clock(void);
double     difftime(time_t _time1, time_t _time0);
time_t     mktime(struct tm *_tptr);
time_t     time(time_t *_timer);
char      *asctime(const struct tm *_timeptr);
char      *ctime(const time_t *_timer);
struct tm *gmtime(const time_t *_timer);
struct tm *localtime(const time_t *_timer);
size_t     strftime(char *_out, size_t _maxsize, const char *_format, 
		    const struct tm *_timeptr);

#endif

