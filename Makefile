#--------------
# Makefile for 8080 Processor
# Author : Antony Toron
#--------------

# Macros
CC = gcc
CPP = g++
CFLAGS = 
#CFLAGS = -g -D CPU_DIAGNOSTIC
#CFLAGS = -D INSTRUCTION_DEBUGGING
#CFLAGS = -pg
#CFLAGS = -D DEBUG
# CFLAGS = -g
# CFLAGS = -D NDEBUG
# CFLAGS = -D NDEBUG -O
CPPFLAGS = -std=c++11
# -lGLEW -lglut-lGLEW -lglut
LIBS = -lglfw3 -lm -lGL -lGLEW -lglut -lGLU -lpthread -lX11 -lXxf86vm -lXrandr -lXi -ldl -lXinerama -lXcursor -lSDL2 -lSDL2_mixer

# Pattern rule, any .o file with .c file of same name will assume it
# %.o: %.c
#       $ (CC) $ (CFLAGS) -c $<

# Dependency rules for non-file targets
all: disassemble c_arcade arcade playground test

# clean directory
clobber: clean
	rm -f *~ \#*\#
clean:
	rm -f disassemble *.o

# Dependency rules for file targets
# include all files ncessary for building in -o shortcut case
c_arcade: 8080Arcade.o CPU.o Utils.o Drivers.o
	$(CC) $(CFLAGS) $< CPU.o Utils.o Drivers.o -o $@ $(LIBS)
disassemble: disassemble.o disassembler.o
	$(CC) $(CFLAGS) $< disassembler.o -o $@

test: cpu_test.o CPU.o Utils.o Drivers.o
	$(CC) $(CFLAGS) -g $< CPU.o Utils.o Drivers.o -o $@ $(LIBS)

playground: playground.o
	$(CPP) $(CFLAGS) $< -o $@ $(LIBS)
arcade: arcade_machine.o CPU.o Utils.o Drivers.o
	$(CPP) $(CFLAGS) $< CPU.o Utils.o Drivers.o -o $@ $(LIBS)


# object file dependencies in recipes for all binary files
8080Arcade.o: 8080Arcade.c CPU.h Utils.h Drivers.h
	$(CC) $(CFLAGS) -c $<
CPU.o: CPU.c CPU.h
	$(CC) $(CFLAGS) -c $<
Utils.o: Utils.c Utils.h
	$(CC) $(CFLAGS) -c $<
Drivers.o: Drivers.c Drivers.h
	$(CC) $(CFLAGS) -c $<

cpu_test.o: cpu_test.c CPU.h Utils.h Drivers.h
	$(CC) $(CFLAGS) -c $<

playground.o: playground.cpp
	$(CPP) $(CFLAGS) -c $< $(LIBS)
arcade_machine.o: arcade_machine.cpp
	$(CPP) $(CPPFLAGS) -c $< $(LIBS)


disassemble.o: disassemble.c disassembler.h
	$(CC) $(CFLAGS) -c $<
disassembler.o: disassembler.c disassembler.h
	$(CC) $(CFLAGS) -c $<
