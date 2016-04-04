BP=bin
SP=src
CFLAGS=-std=c99 -g -O3

all : $(BP)/huff

$(BP)/huff : $(BP)/main.o $(BP)/tree.o $(BP)/heap.o $(BP)/huff.o
	gcc $(LDFLAGS) $^ -o $@

$(BP)/%.o : $(SP)/%.c $(SP)/tree.h $(SP)/heap.h $(SP)/params.h $(SP)/huff.h
	gcc $(CFLAGS) $< -c -o $@

clean :
	rm -f $(BP)/*
