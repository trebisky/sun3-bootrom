/* protos.h
 *
 * Tom Trebisky  7-30-2025
 *
 * ANSI prototypes for all the functions in the bootrom
 *  Some functions are static and have their prototypes
 *   in the file where they are both defined and used.
 *
 * These are in "link order" file by file.
 */

typedef int (*vfptr) ( void );

/* in cpu.map.s */
int /*struct pgmapent*/ getpgmap ( char * );
void                    setpgmap( char *, int );

segnum_t	getsegmap ( char * );
void        setsegmap ( char *, int );

int getcontext ( void );		// never used
void setcontext ( int );

void setcxsegmap ( int, char *, int);
void setcxsegmap_noint ( int, char *, int);

/* in trap.s */
vfptr set_evec ( int, vfptr );

/* in usecmd.c */
void reset_uart ( unsigned char *, int );

/* THE END */
