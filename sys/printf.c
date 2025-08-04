
/*
 * @(#)printf.c 1.1 86/09/27
 * Copyright (c) 1986 by Sun Microsystems, Inc.
 */

// referenced in diag.s
char chardigs[]="0123456789ABCDEF";

// This would be a very different game ...
// #include <stdarg.h>

static void printn (unsigned long, int );

/*
 * Scaled down version of C Library printf.
 * Only %s %d %x %c are recognized.
 */
/*VARARGS0*/
void
printf ( char *fmt, unsigned x1 )
//register unsigned char *fmt;
//unsigned x1;
{
        register unsigned c;
        register unsigned int *adx;
        register unsigned char *s;

        adx = &x1;
        while ((c = *fmt++) != '\0') {
                if (c != '%')
                        putchar(c);
                else {
                        c = *fmt++;
                        switch (c) {

                        case 'c':
                                c = (unsigned char)*adx;
                                putchar(c);
                                break;

                        case 's':
                                s = (unsigned char *)*adx;
                                while (c = *s++)
                                        putchar(c);
                                break;

                        case 'd':
                                printn((unsigned long)*adx, 10);
                                break;

                        case 'x':
                                printn((unsigned long)*adx, 16);
                                break;

                        }
                        adx++;
                }
        }
}

/*
 * Print an unsigned integer in base b.
 */
static void
printn (unsigned long n, int b)
{
        unsigned long a;

        if(a = n/b) {
                printn(a, b);
                /*
                 * The following 4 lines are a kludge which cause inline
                 * multiplies to be used.  Compiler won't generate inline
                 * multiply except by constants (hack) even though it's
                 * exxactly the same to multiply by a random unsigned short.
                 * When there's no need to kludge, replace by:
                 *      n -= a * (unsigned short)b;
                 */
                if (16 == (char) b) 
                        n -= a * 16;
                else
                        n -= a * 10;
        }
/* MJC 5-16-86  I cant find a reason to use this with chardigs there 
        putchar((unsigned char)"0123456789ABCDEF"[n]);
*/
        putchar(chardigs[n]);
}

/*
 * printhex() prints rightmost <digs> hex digits of <val>
 */
void
printhex ( int val, int digs )
{
        digs = ((digs-1)&7)<<2;         /* digs == 0 => print 8 digits */
        for (; digs >= 0; digs-=4)
                putchar(chardigs[(val>>digs)&0xF]);
}

/* THE END */
