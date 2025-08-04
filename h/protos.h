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
int trap ( void );
int nmi ( void );
int addr_error ( void );
int bus_error ( void );

void exit_to_mon ( void );

void set_leds ( int );
void set_enable ( int );
int get_enable ( void );

void menureset ( void );
void bootreset ( void );
void k2reset ( void );
void softreset ( void );


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

/* in sys/idprom.c */
int idprom ( unsigned char, struct idprom * );

/* in sys/usecmd.c */
void usecmd ( void );
void reset_uart ( unsigned char *, int );

/* in sys/getline.c */
void getline ( int );
unsigned char getone ( void );
unsigned char peekchar ( void );
int getnum ( void );
void skipblanks ( void );
int ishex ( unsigned char );

/* in sys/busyio.c */
void putchar ( unsigned char );
int mayput ( unsigned char );

/* in sys/printf.c */
void printf ( char *, ...);
void printhex ( int, int );

/* ... */

/* in sun3/space.s */
int getsb ( int, int );
int getsw ( int, int );
int getsl ( int, int );

int putsb ( int, int, int );
int putsw ( int, int, int );
int putsl ( int, int, int );

void vac_flush_all ( void );
void vac_ctxflush ( int );
void vac_pageflush ( int, int );
void vac_segflush ( int, int );
void cache_dei ( int );


/* THE END */
