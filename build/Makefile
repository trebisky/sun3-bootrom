# Build the sun3 bootrom
#
# Tom Trebisky  7-30-2025

# These 4 machines are directly supported
# CARRERA is the 3/160
# SIRIUS is the 3/260 3/280
# PRISM is the 3/110
# M25 is the 3/50

IDENT='-DID="Rev 2.1"' -DSUN3 -DCARRERA

# Now this is in bootrom.lds
#RELOC=0FEF0000

COPTS= -Wno-endif-labels -Wno-implicit-function-declaration -Wno-multichar
# CFLAGS = -I../h -I. ${COPTS} ${IDENT} -DMC68000
#CFLAGS = -I../h ${COPTS} ${IDENT} -DMC68000
CFLAGS = -I../h ${COPTS} ${IDENT} -DANSI

#AFLAGS = -m68020 -x assembler-with-cpp -Wno-endif-labels
AFLAGS = -march=68020 -mcpu=68020 -x assembler-with-cpp -Wa,--register-prefix-optional -Wno-endif-labels

# For cross compile to m68k target
CC = m68k-linux-gnu-gcc -m68020 -fno-builtin $(CFLAGS)
AAS = m68k-linux-gnu-as -m68020
AS = m68k-linux-gnu-gcc -DASM $(AFLAGS)
LD = m68k-linux-gnu-ld
SIZE = m68k-linux-gnu-size

DUMP = m68k-linux-gnu-objdump -d

OBJS = romvec.o trap.o mapmem.o reset.o cpu.map.o \
	diag.o banner.o commands.o idprom.o usecmd.o  \
	getline.o printf.o busyio.o \
	keypress.o getkey.o ktab.s2.o \
	boot.o monalloc.o common.o blts.o \
	expand.o finit.o fwritestr.o gallmash.o mem_grab.o \
	if_ie.o \
	sc.o sd.o xxboot.o xxprobe.o \
	scutils.o space.o st.o \
	inet.o tftp.o \
	diagmenus.o machdep.o cmp.o patt.o db.o si.o

# These are devices we never intend to deal with
ALT_OBJS = xy.o tm.o xt.o xd.o

# This defines the link order
ORIG_OBJS = romvec.o trap.o mapmem.o reset.o cpu.map.o diag.o banner.o commands.o \
    idprom.o usecmd.o getline.o printf.o busyio.o keypress.o\
    getkey.o ktab.s2.o boot.o monalloc.o common.o blts.o \
    expand.o finit.o fwritestr.o gallmash.o mem_grab.o if_ie.o \
    xy.o sc.o sd.o xxboot.o xxprobe.o scutils.o space.o st.o tm.o xt.o \
    inet.o tftp.o diagmenus.o machdep.o cmp.o patt.o db.o si.o xd.o


# A short note on Gnu make "automatic variables" that are handy,
# but I often forget how to use -- I only use the first two
#  and there are more than these.
# $< - the first prerequisite
# $@ - the first target
# $? - all prerequisites newer than the target
# $^ - all prerequisites, no duplicates
# $+ - all prerequisites, including duplicates

#all: bootrom
all: $(OBJS)

dump:
#	$(DUMP) trap.o >bootrom.dump
	$(DUMP) machdep.o >bootrom.dump

check: chkalign.c
	$(CC) -c chkalign.c
	$(DUMP) chkalign.o >check.dump

# ---------------------------------------------------

romvec.o: ../sun3/romvec.s
	$(AS) -c $<

trap.o: ../sun3/trap.s
	$(AS) -c $<

mapmem.o: ../sys/mapmem.c
	$(CC) -c $<

reset.o: ../sys/reset.c
	$(CC) -c $<

cpu.map.o: ../sun3/cpu.map.s
	$(AS) -c $<

diag.o: ../diag/diag.s
	$(AS) -c $<

banner.o: ../sys/banner.c
	$(CC) -c $<

commands.o: ../sys/commands.c
	$(CC) -c $<

idprom.o: ../sys/idprom.c
	$(CC) -c $<

usecmd.o: ../sys/usecmd.c
	$(CC) -c $<

getline.o: ../sys/getline.c
	$(CC) -c $<

printf.o: ../sys/printf.c
	$(CC) -c $<

busyio.o: ../sys/busyio.c
	$(CC) -c $<

keypress.o: ../sys/keypress.c
	$(CC) -c $<

getkey.o: ../sys/getkey.c
	$(CC) -c $<

ktab.s2.o: ../sys/ktab.s2.c
	$(CC) -c $<

boot.o: ../sys/boot.c
	$(CC) -c $<

monalloc.o: ../sys/monalloc.c
	$(CC) -c $<

common.o: ../sys/common.c
	$(CC) -c $<

blts.o: ../sun3/blts.s
	$(AS) -c $<

expand.o: ../sys/expand.c
	$(CC) -c $<

finit.o: ../sys/finit.c
	$(CC) -c $<

fwritestr.o: ../sys/fwritestr.c
	$(CC) -c $<

gallmash.o: ../sys/gallmash.c
	$(CC) -c $<

if_ie.o: ../dev/if_ie.c
	$(CC) -c $<

mem_grab.o: ../sys/mem_grab.c
	$(CC) -c $<

sc.o: ../dev/sc.c
	$(CC) -c $<

sd.o: ../dev/sd.c
	$(CC) -c $<

xxboot.o: ../sys/xxboot.c
	$(CC) -c $<

xxprobe.o: ../sys/xxprobe.c
	$(CC) -c $<

# used only by finit.c -- sets up color framebuffer
scutils.o: ../dev/scutils.c
	$(CC) -c $<

space.o: ../sun3/space.s
	$(AS) -c $<

st.o: ../dev/st.c
	$(CC) -c $<

inet.o: ../sys/inet.c
	$(CC) -c $<

tftp.o: ../sys/tftp.c
	$(CC) -c $<

diagmenus.o: ../diag/diagmenus.c
	$(CC) -c $<

machdep.o: ../sun3/machdep.c
	$(CC) -O -c $<
	#make dump

cmp.o: ../sun3/cmp.s
	$(AS) -c $<

patt.o: ../sun3/patt.s
	$(AS) -c $<

db.o: ../sun3/db.s
	$(AS) -c $<

si.o: ../dev/si.c
	$(CC) -c $<


# -----------------------------------------------------

bootrom: Makefile $(OBJS)
	@echo linking bootrom
	@rm -f bootrom
	#$(LD) -o bootrom -T bootrom.lds ${OBJS} ${LDFLAGS}
	#$(SIZE) bootrom
	@echo not yet!!

link: Makefile $(OBJS)
	@echo linking bootrom
	@rm -f bootrom
	$(LD) -o bootrom -T bootrom.lds ${OBJS} ${LDFLAGS}
	$(SIZE) bootrom

clean:
	rm -f $(OBJS)
	rm -f bootrom.dump

# THE END
