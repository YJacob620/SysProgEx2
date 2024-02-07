# general commands
all: my_graph my_Knapsack

clean:
	rm -f *.o *.a connections dynamic_programming
	
# .o files
my_graph.o: my_graph.c
	gcc -Wall -c my_graph.c

my_mat.o: my_mat.c
	gcc -Wall -c my_mat.c

my_Knapsack.o: my_Knapsack.c
	gcc -Wall -c my_Knapsack.c

# libraries
my_mat.a: my_mat.o 
	ar -r my_mat.a my_mat.o

# executables
my_graph: my_graph.o my_mat.a
	gcc -Wall my_graph.o -l:my_mat.a -L. -o my_graph

my_Knapsack: my_Knapsack.o
	gcc -Wall my_Knapsack.o -o my_Knapsack
