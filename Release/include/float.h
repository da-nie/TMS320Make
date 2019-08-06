/*****************************************************************************/
/* float.h V5.11 for TMS3203x/4x                                            */
/* Copyright (c) 1992-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/
#ifndef _FLOAT
#define _FLOAT

#define FLT_RADIX                   2   /* RADIX OF EXPONENT                 */
#define FLT_ROUNDS                 -1   /* INDETERMINATE, SINCE # BITS VARIES*/

#define FLT_DIG                     6   /* DECIMAL PRECISION                 */
#define FLT_MANT_DIG               24   /* BITS IN MANTISSA                  */
#define FLT_MIN_EXP              -126   /* MIN E SO 2 ** E-1 FITS            */
#define FLT_MAX_EXP               128   /* MAX E SO 2 ** E   FITS            */
#define FLT_EPSILON     1.1920929E-07   /* SMALLEST X WHERE 1+X != 1         */
		    	                /*    0xE9000000 (2 ^ -23)           */
#define FLT_MIN         5.8774718E-39   /* SMALLEST POSITIVE VALUE           */
                                        /*    0x81000000                     */
#define FLT_MAX         3.4028235E+38   /* LARGEST POSITIVE VALUE            */
			        	/*    0x7f7fffff                     */
#define FLT_MIN_10_EXP            -39   /* MIN POWER OF 10                   */
#define FLT_MAX_10_EXP             38   /* MAX POWER OF 10                   */

#define DBL_DIG                     6   /* DECIMAL PRECISION                 */
#define DBL_MANT_DIG               24   /* BITS IN MANTISSA                  */
#define DBL_MIN_EXP              -126   /* MIN E SO 2 ** E-1 FITS            */
#define DBL_MAX_EXP               128   /* MAX E SO 2 ** E   FITS            */
#define DBL_EPSILON     1.1920929E-07   /* SMALLEST X WHERE 1+X != 1         */
#define DBL_MIN         5.8774718E-39   /* SMALLEST POSITIVE VALUE           */
#define DBL_MAX         3.4028235E+38   /* LARGEST POSITIVE VALUE            */
#define DBL_MIN_10_EXP            -39   /* MIN POWER OF 10                   */
#define DBL_MAX_10_EXP             38   /* MAX POWER OF 10                   */

#define LDBL_DIG                    8   /* DECIMAL PRECISION                 */
#define LDBL_MANT_DIG              32   /* BITS IN MANTISSA                  */
#define LDBL_MIN_EXP             -126   /* MIN E SO 2 ** E-1 FITS            */
#define LDBL_MAX_EXP              128   /* MAX E SO 2 ** E   FITS            */
#define LDBL_EPSILON   1.19209287E-07L  /* SMALLEST X WHERE 1+X != 1         */
#define LDBL_MIN     5.8774717535E-39L  /* SMALLEST POSITIVE VALUE           */
#define LDBL_MAX     3.4028236688E+38L  /* LARGEST POSITIVE VALUE            */
#define LDBL_MIN_10_EXP           -39   /* MIN POWER OF 10                   */
#define LDBL_MAX_10_EXP            38   /* MAX POWER OF 10                   */
#endif
