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

/* in sun3/romvec.s */
/* nada */

/* in sun3/trap.s */
vfptr set_evec ( int, vfptr );
int nmi ( void );
void set_enable ( int );
int get_enable ( void );

/* in sys/mapmem.c */
/* ?? */

/* in sys/reset.c */
/* ?? */

/* in sun3/cpu.map.s */
int /*struct pgmapent*/ getpgmap ( char * );
void                    setpgmap( char *, int );

segnum_t	getsegmap ( char * );
void        setsegmap ( char *, int );

int getcontext ( void );		// never used
void setcontext ( int );

void setcxsegmap ( int, char *, int);
void setcxsegmap_noint ( int, char *, int);

/* in diag/diag.s */
/* -- never called from C code */
void selftest ( void );
void diag_berr ( void );

/* in sys/banner.c */
void banner ( void );
void help ( void );

/* in sys/commands.c */
void vector_default ( char *, char * );

/* ... */

/* in printf.c */
void printf ( char *, ...);
void printhex ( int, int );

/* in usecmd.c */
void reset_uart ( unsigned char *, int );

/* THE END */
