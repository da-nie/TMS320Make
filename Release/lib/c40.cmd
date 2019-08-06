/****************************************************************************/
/* C40.CMD -  v4.60   COMMAND FILE FOR LINKING C40 C PROGRAMS               */
/*                                                                          */
/*    Usage:       lnk30 <obj files...> -o <out file> -m <map file> c40.cmd */
/*                                                                          */
/*    Description: This file is a sample command file that can be used      */
/*                 for linking programs built with the TMS320C40 C          */
/*                 Compiler.   Use it a guideline; you may want to change   */
/*                 the allocation scheme according to the size of your      */
/*                 program and the memory layout of your target system.     */
/*                                                                          */
/*    Notes: (1)   Be sure to use the right library!  Use a library that    */
/*                 matches the runtime model you are using.                 */
/*                                                                          */
/*           (2)   You must specify the directory in which rts.lib is       */
/*                 located.  Either add a "-i<directory>" line to this      */
/*                 file, or use the system environment variable C_DIR to    */
/*                 specify a search path for libraries.                     */
/*                                                                          */
/*           (3)   When using the small (default) memory model, be sure     */
/*                 that the ENTIRE .bss section fits within a single page.  */
/*                 To satisfy this, .bss must be smaller than 64K words and */
/*                 must not cross any 64K boundaries.                       */
/****************************************************************************/
-c                                         /* LINK USING C CONVENTIONS      */
-stack 0x400                               /* 1K STACK                      */
-heap  0x400                               /* 1K HEAP                       */

/* SPECIFY THE SYSTEM MEMORY MAP */

MEMORY
{
   ROM:    org = 0x000000  len = 0x1000     /* INTERNAL ROM                 */
   RAM0:   org = 0x2FF800  len = 0x400      /* RAM BLOCK 0                  */
   RAM1:   org = 0x2FFC00  len = 0x400      /* RAM BLOCK 1                  */
   LOCAL:  org = 0x300000  len = 0x7D00000  /* LOCAL BUS                    */
   GLOBAL: org = 0x8000000 len = 0x8000000  /* GLOBAL BUS                   */
}

/* SPECIFY THE SECTIONS ALLOCATION INTO MEMORY */

SECTIONS
{
   .text:   > LOCAL                  /* CODE                                */
   .cinit:  > LOCAL                  /* INITIALIZATION TABLES               */
   .const:  > LOCAL                  /* CONSTANTS                           */
   .stack:  > RAM0                   /* SYSTEM STACK                        */
   .sysmem: > RAM1                   /* DYNAMIC MEMORY (HEAP)               */
   .bss:    > LOCAL, block 0x10000   /* VARIABLES                           */
}
