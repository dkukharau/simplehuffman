#ifndef HUFF_H
#define HUFF_H


#include <stdio.h>


void compress_file(FILE* input_file, FILE* output_file);
void decompress_file(FILE* input_file, FILE* output_file);


#endif // HUFF_H
