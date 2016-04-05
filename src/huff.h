/**
 *  @file huff.h
 *  @brief This header file contains all function declarations needed
 *         to compress/decompress files using Huffman coding
 *  @author Daniel Kukharau
 */
#ifndef HUFF_H
#define HUFF_H


#include <stdio.h>

/**
 *  @brief Compress a file using Huffman coding
 *  @param input_file Pointer to the file to compress
 *  @param output_file Pointer to a file to write compressed data to
 */
Void compress_file(FILE* input_file, FILE* output_file);
void decompress_file(FILE* input_file, FILE* output_file);


#endif // HUFF_H
