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

int sendtokbd ( int );
int peek ( int );
int pokec ( int, int );
void resetinstr ( void );

int setbus ( void * );
void unsetbus ( void * );
void getidprom ( int, int );

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
// int idprom ( unsigned char, struct idprom * );
int idprom ( unsigned char, void * );

/* in sys/usecmd.c */
void usecmd ( void );
void reset_uart ( volatile unsigned char *, int );

/* in sys/getline.c */
void getline ( int );
unsigned char getone ( void );
unsigned char peekchar ( void );
int getnum ( void );
void skipblanks ( void );
int ishex ( unsigned char );

/* in sys/printf.c */
void printf ( char *, ...);
void printhex ( int, int );

/* in sys/busyio.c */
void putchar ( unsigned char );
int mayput ( unsigned char );

/* in sys/keypress.c */
int keypress ( unsigned char );

/* in sys/getkey.c */
void initgetkey ( void );
void abortfix ( void );
int getkey ( void );

/* in sys/boot.c */
int boot ( char * );
int nullsys ( void * );

/* in sys/monalloc.c */
// char * resalloc ( enum RESOURCES type, unsigned bytes);
char * resalloc ( int, unsigned int );
// char * devalloc ( enum MAPTYPES devtype, char *physaddr, unsigned bytes );
char * devalloc ( int, char *, unsigned int );
void reset_alloc ( void );

/* in sys/common.c */
void bzero ( char *, int );
void bcopy ( char *, char *, int );
int chklabel ( void * );
int isspinning ( int (*isready)(char *, int), char *, int );

/* in sun3/blts.s */
void bltshort ( int a0, int a1, int a2 );
void setshort ( int lo, int hi, unsigned short fillval );

/* in sys/expand.c */
/* used in finit.c */
void fexpand ( unsigned short *, unsigned char *, int ,
        unsigned char *, unsigned char *, unsigned char * );

/* in sys/finit.c */
void finit ( unsigned int, unsigned int );

/* in sys/fwritestr.c */
void fwritechar ( unsigned char );
void fwritestr ( unsigned char *, int );
void pos ( int, int );

/* in sys/mem_grab.c */
void prom_mem_grab ( struct pr_prpos dst, int op, struct pr_prpos *src, short count );

/* in dev/sc.c */
void sc_error ( char * );
// only st.c and sd.c use this, they keep their own prototype
// int scdoit ( struct scsi_cdb *cdb, struct scsi_scb *scb, struct saioreq *sip );

/* in sys/xxboot.c */
int xxboot ( struct bootparam * );
int ttboot ( struct bootparam * );
int devopen ( struct saioreq * );
int devclose ( struct saioreq * );
int tftpboot ( struct bootparam * );

/* in sys/xxprobe.c */
int xxprobe ( struct saioreq * );

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

/* in sys/inet.c */
// all prototypes in tftp.c

/* in sys/tftp.c */
int etheropen ( struct saioreq * );
int etherstrategy ( struct saioreq *, int );
int tftpload ( struct saioreq * );

/* in diag/diagmenus.c */
void display_opt ( char *, char * );
int memory_test ( int, int );
void keybd_test ( void );
int ports_test ( int );
int ether_test ( void );
int amd_ether_test ( void );
int boot_test ( char * );
int get_cmd ( void );

/* in dev/si.c */
int siprobe ( struct saioreq * );
// int sidoit ( struct scsi_cdb *, struct scsi_scb *, struct saioreq * );

/* in sys/rop.s */
void prom_mem_batchrop ( struct pr_prpos, int, struct pr_prpos *, short );



/* THE END */
