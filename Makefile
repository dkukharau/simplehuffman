BP=bin
SP=src
CFLAGS=-std=c99 -g

all : $(BP)/huff

$(BP)/huff : $(BP)/main.o $(BP)/tree.o $(BP)/heap.o
	gcc $(LDFLAGS) $^ -o $@

$(BP)/%.o : $(SP)/%.c $(SP)/tree.h $(SP)/heap.h
	gcc $(CFLAGS) $< -c -o $@
