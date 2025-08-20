/*      @(#)if_obie.h 1.1 86/09/27 SMI  */

/*
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

/*
 * Register definitions for the Sun-2 On-board version of the
 * Intel EDLC based Ethernet interface.
 * FYI: Reset: write zeros to register
 *      Must poll to check for obie_buserr
 */
// tjt - this was u_char
struct obie_device {
        vu_8  obie_noreset    : 1;    /* R/W: Ethernet chips reset */
        vu_8  obie_noloop     : 1;    /* R/W: loopback */
        vu_8  obie_ca         : 1;    /* R/W: channel attention */
        vu_8  obie_ie         : 1;    /* R/W: interrupt enable */
        vu_8                  : 1;    /* R/O: unused */
        vu_8  obie_level2     : 1;    /* R/O: 0=Level 1 xcvr, 1=Level 2 */
        vu_8  obie_buserr     : 1;    /* R/O: Ether DMA got bus error */
        vu_8  obie_intr       : 1;    /* R/O: interrupt request */
};

// The 3-160 does not implement the level2 bit

/* tjt
 *     See page 31 of the Sun 3 Tech manual for this.
 * It is at address OxOOOCOOOO
 * This is NOT part of the 82586, but is a register on the sun3 board.
 * It is 8 bits wide.
 * reset and loopback bits are active low.
 */

/* THE END */
