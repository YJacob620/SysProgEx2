# .o files
main.o: main.c
	gcc -Wall -c main.c

my_mat.o: my_mat.c
	gcc -Wall -c my_mat.c

# libraries
my_mat.a: my_mat.o 
	ar -r my_mat.a my_mat.o

# executables
main: main.o my_mat.a
	gcc -Wall main.o -l:my_mat.a -L. -o main

# general commands
clean:
	rm -f *.o *.a main