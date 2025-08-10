# Makefile to build genassym and possibly other tools
# TJT  7-30-2025

# For compile to run on local host
HCC = gcc -m32
# HCFLAGS= -Wno-endif-labels -Wno-implicit-function-declaration
HCFLAGS= -Wno-endif-labels -Wno-implicit-function-declaration -Wno-implicit-int -Wno-pointer-to-int-cast

all:	genassym

build:
		./genassym >../sun3/assym.h

# ===================================
# assym.h contains assembler defns of structure members.  It's made by
# genassym.c, which just printf's their values.  make depend keeps it all OK.
# structconst.h contains hex values of constant structs like page map entries.
# This hack is used to get around C's refusal to initialize local structs
# and inability to define structure constants.

genassym: genassym.c Makefile
	${HCC} ${HCFLAGS} genassym.c -o genassym

# THE END
