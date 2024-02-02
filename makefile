# general commands
all: connections dynamic_programming

clean:
	rm -f *.o *.a connections dynamic_programming
	
# .o files
main.o: main.c
	gcc -Wall -c main.c

my_mat.o: my_mat.c
	gcc -Wall -c my_mat.c

main_DP.o: main_DP.c
	gcc -Wall -c main_DP.c

# libraries
my_mat.a: my_mat.o 
	ar -r my_mat.a my_mat.o

# executables
connections: main.o my_mat.a
	gcc -Wall main.o -l:my_mat.a -L. -o connections

dynamic_programming: main_DP.o
	gcc -Wall main_DP.o -o dynamic_programming
