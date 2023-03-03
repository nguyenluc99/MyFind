GCCFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla
SRCFOLD = src
OBJ = $(SRCFOLD)/AST.o  $(SRCFOLD)/node.o $(SRCFOLD)/stack_tree.o
GCC = gcc
OUTPUT = myfind

all: AST node stack target

AST:
	$(GCC) $(GCCFLAGS) $(SRCFOLD)/AST.c -c -o $(SRCFOLD)/AST.o

node:
	$(GCC) $(GCCFLAGS)  $(SRCFOLD)/node.c -c -o $(SRCFOLD)/node.o

stack:
	$(GCC) $(GCCFLAGS)  $(SRCFOLD)/stack_tree.c -c -o $(SRCFOLD)/stack_tree.o

target:
	$(GCC) $(GCCFLAGS) $(OBJ) $(SRCFOLD)/myfind.c -o $(OUTPUT)

clean:
	rm -rf myfind $(SRCFOLD)/*.o
