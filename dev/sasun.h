/*      @(#)sasun.h 1.1 86/09/27 SMI    */

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

/*
 * Constants for standalone I/O (bootstrap) code
 * FIXME:  This is duplicated and places that use it have to undef things.
 */
#include "../sun3/cpu.addrs.h"

#define DEF_MBMEM_VA    MBMEM_BASE
#define DEF_MBIO_VA     MBIO_BASE

#define LOADADDR        0x4000
#define BBSIZE          8192            /* boot block size (from fs.h) */
#define DEV_BSIZE       512             /* manifest */
#define MAX(a,b)        (((a)>(b))? (a): (b))

#ifdef notdef
// tjt - we also have a different DELAY in saio.h (by the same name)
// the code compiles fine without this, so why have the confusion.
// 8-18-2025

/* FIXME: This DELAY() macro doesn't match the kernel's for non-68010 */
#define DELAY(n)        { register int N = (n)>>1; while (--N > 0) asm volatile("": : :"memory"); }
#endif
