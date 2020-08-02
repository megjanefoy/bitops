# this will compile bitops.c files and create an executible called bitops. It also has the option to clean the executable and object files.
all: 
	gcc bitops.c -o bitops
clean: 
	rm -f *.exe *.o bitops