/*
 * Memory raster put routine.
 *
 * Rewritten in C based on the assembly code, source headers, and the source of the prom_mem_grab function.
 */

#include "../h/types.h"
#include "../h/pixrect.h"
#include "../sun3/memreg.h"
#include "../h/memvar.h"
#include "../h/pr_util.h"

void
prom_mem_batchrop ( struct pr_prpos dst, int op, struct pr_prpos *src, short count )
{
        char *sp;
        char *dp;
        int sizex, sizey;
        int vert, dskew;
        struct mpr_data *dprd;
        struct pixrect *spr;
        struct mpr_data *sprd;
        
        while (count--) {
        
                // this is in the binary function, but src->pos.{x,y} are hardwired to 0
                dst.pos.x = (src->pos).x + dst.pos.x;
                dst.pos.y = (src->pos).y + dst.pos.y;
    
                dprd = ((struct mpr_data *)(dst.pr)->pr_data);
		vert = dprd->md_linebytes;
                dp = (char*)mprd_addr(dprd, dst.pos.x, dst.pos.y); /* see h/memvar.h */
                dskew = mprd_skew(dprd, dst.pos.x, dst.pos.y); /* see h/memvar.h */

                spr = src->pr;

                if (spr) {
			sizex = spr->pr_size.x; /* hardwired to 12 ? */
			sizey = spr->pr_size.y; /* hardwired to 22 ? */
			if (!sizey) continue;
			
			sprd = ((struct mpr_data *)(spr)->pr_data);
			sp = (char *)sprd->md_image;

                        /* in the binary version...
                           only 0x0, 0x3, 0x5, 0xC and 0xF are implemented with the loop.
                           0x3 and 0xC increment sp (0x0, 0x5 and 0xF don't) [they use PIX_SRC]
                           0x0 and 0xC use a ~/& combo for the first line    [they clear first?]
                           0x3 and 0xF use no ~ and | for the first line     [???]
                           0x5 use no ~ and ^ for the first line             [???]
                           0x3 use (sp) with ^                               [???]
                           0xC use (sp) with |                               [set to src]
                           everything else is implemented as nop.

                           0x0 == (PIX_CLEAR >> 1)
                           0xC == (PIX_SRC >> 1)
                           0xF == (PIX_SET >> 1)
                           0x3 == PIX_NOT(PIX_SRC) >> 1
                           0x5 == PIX_NOT(PIX_DST) >> 1
                        */

#define CLEAR_DEST_us  *(u_short*)dp = ~((u_short)((int)0xFFFF8000 >> (sizex - 1)) >> dskew) & *(u_short*)dp
#define SET_DEST_us    *(u_short*)dp =  ((u_short)((int)0xFFFF8000 >> (sizex - 1)) >> dskew) | *(u_short*)dp
#define XOR_DEST_us    *(u_short*)dp =  ((u_short)((int)0xFFFF8000 >> (sizex - 1)) >> dskew) ^ *(u_short*)dp

#define SET_SRC_us     *(u_short*)dp =  (*(u_short *)sp >> dskew) | *(u_short*)dp; sp += 2
#define XOR_SRC_us     *(u_short*)dp =  (*(u_short *)sp >> dskew) ^ *(u_short*)dp; sp += 2
        
#define NOTHING        /* */

#define CLEAR_DEST_ui  *(u_int*)dp = ~((u_int)((int)0x80000000 >> (sizex - 1)) >> dskew) & *(u_int*)dp
#define SET_DEST_ui    *(u_int*)dp =  ((u_int)((int)0x80000000 >> (sizex - 1)) >> dskew) | *(u_int*)dp
#define XOR_DEST_ui    *(u_int*)dp =  ((u_int)((int)0x80000000 >> (sizex - 1)) >> dskew) ^ *(u_int*)dp

#define SET_SRC_ui     *(u_int*)dp = (u_int)*(u_short *)sp << (16 - dskew) | *(u_int*)dp; sp += 2
#define XOR_SRC_ui     *(u_int*)dp = (u_int)*(u_short *)sp << (16 - dskew) ^ *(u_int*)dp; sp += 2

#define LOOP(DEST, SRC)				\
                        do {			\
                                DEST;		\
                                SRC;		\
                                dp += vert;	\
			} while (--sizey != 0)
			
                        switch ((op >> 1) & 0xF) {
                        case 0x0:
                                if (dskew + sizex <= 16) {
                                        LOOP(CLEAR_DEST_us, NOTHING);
				} else {
                                        LOOP(CLEAR_DEST_ui, NOTHING);
				}
                                break;
                        case 0x3:
                                if (dskew + sizex <= 16) {
                                        LOOP(SET_DEST_us, XOR_SRC_us);
				} else {
                                        LOOP(SET_DEST_ui, XOR_SRC_ui);
				}
                                break;
                        case 0x5:
                                if (dskew + sizex <= 16) {
                                        LOOP(XOR_DEST_us, NOTHING);
				} else {
                                        LOOP(XOR_DEST_ui, NOTHING);
				}
                                break;
                        case 0xC: // PIX_SRC
                                if (dskew + sizex <= 16) {
                                        LOOP(CLEAR_DEST_us, SET_SRC_us);
				} else {
                                        LOOP(CLEAR_DEST_ui, SET_SRC_ui);
				}
                                break;
                        case 0xF:
                                if (dskew + sizex <= 16) {
                                        LOOP(SET_DEST_us, NOTHING);
				} else {
                                        LOOP(SET_DEST_ui, NOTHING);
				}
                                break;
                        default:
                                break;
                        } // switch
                } // if (spr)
                src++;
        } // while (count--)
}
