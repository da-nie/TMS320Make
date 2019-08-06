/*****************************************************************************/
/*  FILE.H V5.11                                                            */
/*  Copyright (c) 1995-1999 Texas Instruments Incorporated                   */
/*****************************************************************************/

/*****************************************************************************/
/* Macros and declarations used in lowlevel I/O functions.                   */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* constants for file manipulations                                          */
/*---------------------------------------------------------------------------*/
#define  O_RDONLY    (0x0000) /* open for reading      */
#define  O_WRONLY    (0x0001) /* open for writing      */
#define  O_RDWR      (0x0002) /* open for read & write */
#define  O_APPEND    (0x0008) /* append on each write  */
#define  O_CREAT     (0x0200) /* open with file create */
#define  O_TRUNC     (0x0400) /* open with truncation  */
#define  O_BINARY    (0x8000) /* open in binary mode   */

/*---------------------------------------------------------------------------*/
/* lowlevel I/O declarations                                                 */
/*---------------------------------------------------------------------------*/
extern int  open(const char *path, unsigned flags, int mode);
extern int  read(int fildes, char *bufptr, unsigned cnt);
extern int  write(int fildes, const char *bufptr, unsigned cnt);
extern long lseek(int fildes, long offset, int origin);
extern int  close(int fildes);
extern int  unlink(const char *path);
extern int  rename(const char *old_name, const char *new_name);

