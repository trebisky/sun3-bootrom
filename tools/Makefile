# Makefile to build genassym and possibly other tools
# TJT  7-30-2025

# For compile to run on local host
HCC = gcc
# HCFLAGS= -Wno-endif-labels -Wno-implicit-function-declaration
HCFLAGS= -Wno-endif-labels -Wno-implicit-function-declaration -Wno-implicit-int -Wno-pointer-to-int-cast

all:	genassym sun3_checksum

build:
		./genassym >../sun3/assym.h

# ===================================
# assym.h contains assembler defns of structure members.  It's made by
# genassym.c, which just printf's their values.  make depend keeps it all OK.
# structconst.h contains hex values of constant structs like page map entries.
# This hack is used to get around C's refusal to initialize local structs
# and inability to define structure constants.
# it needs to be on a 32-bits architecture to get 4-bytes pointer
genassym: genassym.c Makefile
	${HCC} -m32 ${HCFLAGS} genassym.c -o genassym

sun3_checksum: sun3_checksum.c Makefile
	${HCC} ${HCFLAGS} $< -o $@


# THE END
