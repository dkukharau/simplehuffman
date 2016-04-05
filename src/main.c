/**
 *  @file main.c
 *  @brief This file contains the entry point of the SimpleHuffman project
 *  @author Daniel Kukharau
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "huff.h"


/**
 *  @brief Entry point for the project
 *
 *  Usage:
 *
 *  huff input_file [ -c|-x ] output_file
 *
 */
int main(int argc, char *argv[]) {

     if (argc != 4 || !(strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "-x") == 0)) {
          fprintf(stderr, "%s\n\n%s\n%s\n", "Incorrect Usage", "Usage:",
                  "huff input_file [ -c|-x ] output_file");
          exit(1);
     }

     FILE* input = fopen(argv[1], "rb");
     FILE* output = fopen(argv[3], "wb");

     if (!input) {
          perror(argv[1]);
          exit(1);
     }

     if (!output) {
          perror(argv[3]);
          exit(1);
     }


     if (strcmp(argv[2], "-c") == 0) {
          compress_file(input, output);
     }
     else {
          decompress_file(input, output);
     }


     if (fclose(input)) {
          perror(argv[1]);
          exit(1);
     }

     if (fclose(output)) {
          perror(argv[3]);
          exit(1);
     }

     return 0;
}
