# Makefile for Quantum Harmonic Oscillator FEM Approximator
# Amelia Nishimura 6/11/19
#
# Use:
# 	make all		-- Generates executable file by compiling
#	make oscillator 	-- Same as "make all"
#	make oscillator.o	-- (Re)generates oscillator.o by compiling
#	make geometry.o		-- (Re)generates geometry.o by compiling
#
#	make clean		-- Removes object files, executable, and docs
#
#	make docs		-- Generates documentation

# Set CFLAGS to activate all warnings and enable debugger
CFLAGS = -Wall -g

# Default Rule: Build oscillator executable
all: oscillator

# Rule for building the executable
oscillator: oscillator.o geometry.o
	gcc $(CFLAGS) oscillator.o geometry.o -o oscillator

# Rules for building each object file
oscillator.o: oscillator.c geometry.h
	gcc $(CFLAGS) -c oscillator.c

geometry.o: geometry.c geometry.h
	gcc $(CFLAGS) -c geometry.c

# Command "make clean": Remove object files, executable, and documentation
clean:
	rm -f *.o oscillator
	rm -f -r html latex

# Command "make docs": Create documentation
docs:
	doxygen
