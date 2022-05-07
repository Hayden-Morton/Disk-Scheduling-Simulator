Program Name: Disk Scheduling Simulator
Author: Hayden Morton 19750938
Description: Calculates the total movement distance a write-head would move based on different scheduling algorithms from an input file, the program will requery for files until terminated.

There are two implementations:
	scheduler.c - without multithreading
	simulator.c - with multithreading

DEPENDENCIES
	stdio.h
	stdlib.h
	string.h
	libgen.h
	pthread.h

COMPILING
(in top directory)
> make

USAGE
(in "dest" directory) (<program> is either "scheduler or "simulator")
> ./<program>

Then enter the file name (with respective reference path)
	will only accept files of name length less than 10

or "QUIT" to exit the program.

There are sample files within directory "dest" by the name of input*.txt

FILE STRUCTURE:
	directory "dest" - destination directory, holds the finished executables when compiled and ideally input files
	directory "build" - build directory, holds all object files required for compilation
	directory "src" - source file directory, holds all source files.
		"algorithms.c" - the different scheduling implementations.
		"assumptions.h" - any numerical assumptions required by the program
		"buffer1.c" - management of buffer1, which holds the input file data
		"linkedlist.c" - linkedlist implementation used bu buffer1
		"readFile.c" - input file reading
		"scheduler.c" - threadless implementation of the program
		"simulator.c" -threaded implementation of the program
