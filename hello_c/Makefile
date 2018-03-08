BASE = hello_c
COMMON = kern.asm incsp2.s
DESTDIR = out
# Tool paths
CL65 = ./cl65
CC65 = ./cc65
BIN2HEX = ./bin2hex
VM65 = ./vm65

# Create the VM65-compat image by default
all : ${DESTDIR}/${BASE}.dat

# Make sure the destination directory exists
${DESTDIR} :
	mkdir ${DESTDIR}

# Compile the source file, and include the additional required assembly files
${DESTDIR}/${BASE}.bin : ${BASE}.c ${COMMON} ${DESTDIR}
	${CL65} -C ${BASE}.cfg -l ${DESTDIR}/${BASE}.lst -m ${DESTDIR}/${BASE}.map --start-addr 1024 -t none -o $@ $< ${COMMON}
	mv *.o ${DESTDIR}

# Convert the generated binary to the vm65 expected format
${DESTDIR}/${BASE}.dat : ${DESTDIR}/${BASE}.bin ${DESTDIR}
	${BIN2HEX} -f $< -o $@ -w 0 -x 1024 -z
	# Add the IO mapping for the screen
	echo IOADDR >> $@
	echo "\$$E000" >> $@
	echo ENIO >> $@

# Utility command to create an asm version of the source file
asm : ${DESTDIR}
	${CC65} ${BASE}.c -o ${DESTDIR}/${BASE}.s

# Run the generated .dat in the vm65 emulator
run : ${DESTDIR}/${BASE}.dat
	${VM65} -r ${DESTDIR}/${BASE}.dat

# Remove the entire destination directory to clean the project
clean :
	rm -rf ${DESTDIR}

.PHONY : all run clean asm


