/*****************************************************************************/
/* VALUES.H V5.11							     */
/* Copyright (c) 1992-1999 Texas Instruments Incorporated                    */
/*****************************************************************************/

#define BITS	  23               /* There are 23 bits in the mantissa     */
#define MAXX	  88.72283906      /* ln(HUGE_VAL)                          */
#define MAXH	  89.41598624	   /* ln(HUGE_VAL) + ln(2)                  */
#define TWO23	  8388608	   /* 2 ^ BITS                              */
#define XBIG	  8.664339757	   /* (BITS/2 + 1) * ln(2)                  */

/****************************************************************************/
/*  The following macros define constants used throughout the functions.    */
/****************************************************************************/

/* macros used in asin and acos */

#define SQRTWO	  1.4142135623730950
#define ASP1	  0.933935835
#define ASP2	 -0.504400557
#define ASQ0	  0.560363004e1
#define ASQ1	 -0.554846723e1

/* macros used in atan and atan2 */

#define TWO_SQRT3 0.26794919243112270647
#define SQRTTHREE 1.73205080756887729353
#define PI	  3.14159265358979323846
#define ATP0	 -0.4708325141
#define ATP1	 -0.5090958253e-1
#define ATQ0	  0.1412500740e1

/* macros used in sin and cos */

#define INVSPI	  0.31830988618379067154
#define HALFPI	  1.57079632679489661923
#define C1	  3.140625
#define C2	  9.67653589793e-4
#define R1	 -0.1666665668e+0
#define R2	  0.8333025139e-2
#define R3	 -0.1980741872e-3
#define R4	  0.2601903036e-5

/* macros used in exp, cosh, and sinh */

#define LOGe2	  0.6931471805599453094172321
#define LOG102    0.301029995663981198017
#define INVLOGe2  1.4426950408889634074
#define EXP0	  0.24999999950
#define EXP1	  0.41602886268e-2
#define EXQ0	  0.5
#define EXQ1	  0.49987178778e-1
#define SHP0	 -0.713793159e1
#define SHP1	 -0.190333399
#define SHQ0	 -0.428277109e2

/* macros used in log10 and log */

#define SQRTHALF  0.70710678118654752440
#define LOG10e	  0.4342944819032518
#define C3	  0.693359375
#define C4	 -2.121944400546905827679e-4
#define A0	 -0.5527074855
#define B0	 -0.6632718214e1

/* macros used in pow */

#define L1	  2.885390072738
#define L3	  0.961800762286
#define L5	  0.576584342056
#define L7	  0.434259751292
#define T6	  0.0002082045327
#define T5	  0.001266912225
#define T4	  0.009656843287
#define T3	  0.05549288453
#define T2	  0.2402279975
#define T1	  0.6931471019

/* macros used in tan */

#define TWOINVPI  0.63661977236758134308
#define C5	  1.5703125
#define C6	  4.83826794897e-4
#define TAP1	 -0.958017723e-1
#define TAQ1	 -0.429135777e+0
#define TAQ2	  0.971685835e-2

/* macros used in tanh */

#define LOGe3by2  0.54930614433405484570
#define THP0	 -0.8237728127
#define THP1	 -0.3831010665e-2
#define THQ0	  0.2471319654e1
