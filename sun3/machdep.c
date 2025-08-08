
/*
 * @(#)machdep.c 1.1 86/09/27
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

#include "../h/systypes.h"
#include "../sun3/machdep.h"

/*
 *      these are the routines in machdep
 *      addr is usually a u_long
 *      entry is a ??_size
 *      routines for mapping and registers return ??_size
 *      most of the set* routines return what was there before
 *      %'ed routines return nothing
                cx_size         getcxreg()
                cx_size         setcxreg(entry)
                sm_size         getsmreg(addr)
                sm_size         setsmreg(addr,entry)
                pg_size         getpgreg(addr)
                pg_size         setpgreg(addr,entry)
                berr_size       getberrreg()
                int  %          map(virt, size, phys, space)
 */

/* tjt
 * The original code here is interesting.
 * apparently they knew the Sun compiler well
 * enough to be sure that the a5 register
 * would get the value of the "addr" variable.
 * I would have just written these in assembler
 * and put them in some other file.
 * Perhaps in "space.s"
 * Interestingly, I looked at the disassembly of the
 * sun 3/80 bootrom and there is only one reference
 * to the "%sfc" and "%dfc" registers.
 * The 3/60 bootrom has plenty of references to these
 * registers, but I don't find these routines.
 * It is also curious that this routine does not
 * save (then restore) the original sfc value
 */

#ifdef ORIGINAL
// tjt -- moved here from machdep.h
#define MOVC(from, to)  asm("   movc    from, to")
#define MOVL(from, to)  asm("   movl    from, to")
#define MOVSB(from, to) asm("   movsb   from, to")
#define MOVSW(from, to) asm("   movsw   from, to")
#define MOVSL(from, to) asm("   movsl   from, to")


/*
 * get/set fc3 are to eliminate the assembly all over the place,
 * and to let users do their own self abuse
 */
u_long
getfc3(size,addr)
register u_long                 size, *addr;
{
        MOVL(#3, d0);
        MOVC(d0, sfc);
        if (size == sizeof(u_char))
                MOVSB(a5@, d7);
        else if (size == sizeof(u_short))
                MOVSW(a5@, d7);
        else if (size == sizeof(u_long))
                MOVSL(a5@, d7);
        return(size);
}

u_long
setfc3(size,addr,entry)
register u_long                 size, *addr,entry;
{
        MOVL(#3, d0);
        MOVC(d0, dfc);
        if (size == sizeof(u_char))
                MOVSB(d6, a5@);
        else if (size == sizeof(u_short))
                MOVSW(d6, a5@);
        else if (size == sizeof(u_long))
                MOVSL(d6, a5@);
}
#endif /* ORIGINAL */

u_long
getfc3 ( u_long size, char *addr )
{
		u_long rv;
		asm volatile ( "moveq #3, %d0" );
		asm volatile ( "movec %d0, %dfc" );
		// MOVSB(a5@, d7);
		// A O I C
		// asm volatile("movq %%cr8,%0" : "=r" (val));
		// asm volatile("movq %0,%%cr8" :: "r" (val) : "memory");
		asm volatile ( "movel #5, %0" : "=d" (rv) );
		// asm ( "movesb %0, %1@" : "=r" (rv) : "r" (addr) );
		return rv;
}

/* Never used */
cx_size
getcxreg ( void )
{
        return (cx_size) getfc3 ( sizeof(cx_size), (char *)CX_OFF);
}

/* Never used */
cx_size
setcxreg ( cx_size entry)
{
        register cx_size ret = getcxreg();

        setfc3(sizeof(cx_size), CX_OFF, entry);

        return(ret);
}

/* Never used */
sm_size
getsmreg ( u_long addr )
{
        addr = ((addr & ~SEGMASK) + SM_OFF) & ADDRMASK;
        return (sm_size) getfc3(sizeof(sm_size), (char *) addr);
}

/* Used in diagmenus.c */
sm_size
setsmreg ( u_long addr, sm_size entry)
{
        register sm_size ret = getsmreg(addr);

        addr = ((addr & ~SEGMASK) + SM_OFF) & ADDRMASK;
        setfc3(sizeof(sm_size), addr, entry);

        return(ret);
}

/* Never used */
pg_size
getpgreg ( u_long addr )
{
        addr = ((addr & ~PAGEMASK) + PG_OFF) & ADDRMASK;
        return (pg_size) getfc3(sizeof(pg_size), (char *) addr);
}

/* Used below in map() */
pg_size
setpgreg ( u_long addr, pg_size entry )
{
        register pg_size ret = getpgreg(addr);

        addr = ((addr & ~PAGEMASK) + PG_OFF) & ADDRMASK;
        setfc3(sizeof(pg_size), addr, entry);

        return(ret);
}

/* Used in diagmenus.c */
void
map ( u_long virt,  u_long size, u_long phys, enum pm_type space )
{
        pg_t                            page;
        register struct pg_field        *pgp = &page.pg_field;
        register int                    i;

        pgp->pg_valid = 1;
        pgp->pg_permission = PMP_ALL;
        pgp->pg_space = space;

        phys = BTOP(phys);
        size = BTOP(size);

        for (i = 0; i < size; i++){             /* for each page, */
                pgp->pg_pagenum = phys++;
                setpgreg(virt + PTOB(i), page.pg_whole);
        }
}

#ifdef notdef
// tjt - never used
berr_size
getberrreg()
{
        return (berr_size) getfc3(sizeof(berr_size), (char * )BERR_OFF);
}
#endif

/* THE END */
