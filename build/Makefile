# Build the sun3 bootrom

# CARRERA is the 3/160
# SIRIUS is the 3/260 3/280
# PRISM is the 
IDENT='-DID="Rev 2.1"' -DSUN3 -DCARRERA

# Now this is in bootrom.lds
#RELOC=0FEF0000

# CFLAGS = -I../h -I. ${COPTS} ${IDENT} -DMC68000
# COPTS= -Wno-endif-labels -Wno-implicit-function-declaration

#AFLAGS = -m68020 -x assembler-with-cpp -Wno-endif-labels
AFLAGS = -march=68020 -mcpu=68020 -x assembler-with-cpp -Wa,--register-prefix-optional -Wno-endif-labels

# For cross compile to m68k target
CC = m68k-linux-gnu-gcc -m68020 -fno-builtin
AAS = m68k-linux-gnu-as -m68020
AS = m68k-linux-gnu-gcc -DASM $(AFLAGS)
LD = m68k-linux-gnu-ld

all: bootrom

OBJS = romvec.o trap.o

# This defines the link order
ORIG_OBJS=romvec.o trap.o mapmem.o reset.o cpu.map.o diag.o banner.o commands.o \
    idprom.o usecmd.o getline.o printf.o busyio.o keypress.o\
    getkey.o ktab.s2.o boot.o monalloc.o common.o blts.o \
    expand.o finit.o fwritestr.o gallmash.o mem_grab.o if_ie.o \
    xy.o sc.o sd.o xxboot.o xxprobe.o scutils.o space.o st.o tm.o xt.o \
    inet.o tftp.o diagmenus.o machdep.o cmp.o patt.o db.o si.o xd.o

romvec.o: ../sun3/romvec.s
	$(AS) -c ../sun3/romvec.s

trap.o: ../sun3/trap.s
	$(AS) -c ../sun3/trap.s


bootrom: Makefile $(OBJS)
	@echo linking bootrom
	@rm -f bootrom
	$(LD) -o bootrom -T bootrom.lds ${OBJS} ${LDFLAGS}
	size bootrom

# THE END



