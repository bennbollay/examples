.PHONY : all

all :
	${MAKE} -C hello_c
	${MAKE} -C grover_lookup_asm
	${MAKE} -C prototype
	${MAKE} -C grover_asm



