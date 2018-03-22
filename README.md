VM6502Q Examples: [![VM6502Q Examples Build Status](https://api.travis-ci.org/vm6502q/examples.svg?branch=master)](https://travis-ci.org/vm6502q/examples/builds)

A small collection of cc65-compat projects to be used with the vm65 target.

# Usage Guide

This project assumes the following directory structure based off a `root/` directory:

```
root/vm6502q
root/cc65
root/examples
root/qrack
symlink root/vm6502q/qrack -> root/qrack
```

Run using the following sequence:
```
root/ $ make -C vm6502q
root/ $ make -C cc65
root/ $ cd examples/grover_asm
grover_asm/ $ make run
```

Additionally, `make asm` will generate an `out/grover_asm.s` file for
inspection, or just `make` to build the desired `out/grover_asm.dat` file.

# Creating a new example

* Copy the `prototype/` directory to your example name, renaming the `.cfg` file to match the source file.
* Change `prototype` in `Makefile` to be the basename of your cfg and source file.
* Adjust the `project.cfg` file as necessary for memory sizing.

