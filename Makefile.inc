# Put all of the generated artifacts in ${DESTDIR}
DESTDIR = out

# Location of this directory in relation to example directories
BASEDIR = ..

# Allow to be overridden by the environment
CC65_DIR ?= ${BASEDIR}/../cc65
VM6502Q_DIR ?= ${BASEDIR}/../vm6502q

# CPU Override
TARGET_CPU ?= 6502q
ifeq (,${TARGET_CPU})
SET_CC65_CPU =
else
SET_CC65_CPU = --cpu ${TARGET_CPU}
endif

# Tool paths - assumes that 'bin' has been symlink'ed to the cc65/bin
# directory, and that the 'bin2hex' tool from the vm6502q/ project is present
# somewhere.
CL65 = ${CC65_DIR}/bin/cl65
CC65 = ${CC65_DIR}/bin/cc65
BIN2HEX = ${VM6502Q_DIR}/bin2hex
VM65 = ${VM6502Q_DIR}/vm65

# Originating from a C file
ifneq (,$(wildcard ${BASE}.c))
EXAMPLE_INPUT=${BASE}.c
else ifneq (,$(wildcard ${BASE}.s))
EXAMPLE_INPUT=${BASE}.s
else ifneq (,$(wildcard ${BASE}.asm))
EXAMPLE_INPUT=${BASE}.asm
else
$(error Source file not found in ${BASE}.c, ${BASE}.asm, or ${BASE}.s)
endif

# Include default commons if specified
ifeq (true,${INCLUDE_COMMONS})
CFLAGS += -I ${BASEDIR}/common
COMMON += ${BASEDIR}/common/kern.s ${BASEDIR}/common/incsp2.s
endif

# Create the VM65-compat image by default
all : ${DESTDIR}/${BASE}.dat

# Make sure the destination directory exists
${DESTDIR} :
	mkdir ${DESTDIR}

# Compile the source file, and include the additional required assembly files
${DESTDIR}/${BASE}.bin : ${EXAMPLE_INPUT} ${COMMON} ${DESTDIR}
	${CL65} ${CFLAGS} -C ${BASE}.cfg -l ${DESTDIR}/${BASE}.lst -m ${DESTDIR}/${BASE}.map --start-addr 1024 -t none ${SET_CC65_CPU} -o $@ $< ${COMMON}
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
	${CC65} ${CFLAGS} ${BASE}.c -t none ${SET_CC65_CPU} -o ${DESTDIR}/${BASE}.s

# Run the generated .dat in the vm65 emulator
run : ${DESTDIR}/${BASE}.dat
	ln -sf ${VM6502Q_DIR}/dummy.rom .
	# Ignore errors returned from the vm
	-${VM65} -r ${DESTDIR}/${BASE}.dat

# Remove the entire destination directory to clean the project
clean :
	rm -rf ${DESTDIR}
	rm -rf dummy.rom

.PHONY : all run clean asm

# vi:filetype=make
