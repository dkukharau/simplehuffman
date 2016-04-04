#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include <time.h>
#include "tree.h"
#include "heap.h"
#include "params.h"


int main(int argc, char *argv[]) {

     if (argc != 4 || !(strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "-x") == 0)) {
          fprintf(stderr, "%s\n\n%s\n%s\n", "Incorrect Usage", "Usage:",
                  "huff input_file [ -c|-x ] output_file");
          exit(1);
     }

     FILE* input = fopen(argv[1], "rb");
     FILE* output = fopen(argv[3], "wb");

     if (input == NULL) {
          perror(argv[1]);
          exit(1);
     }

     if (output == NULL) {
          perror(argv[3]);
          exit(1);
     }

     uint8_t input_buffer[BUFFER_SIZE] = {};
     uint8_t output_buffer[BUFFER_SIZE] = {};
     uint32_t char_freq[CHARACTERS_NUM] = {};

     if (strcmp(argv[2], "-c") == 0) {

          uint32_t huff_code[CHARACTERS_NUM] = {};
          uint8_t huff_code_length[CHARACTERS_NUM] = {};
          uint32_t file_size = 0;

          while(!feof(input)) {
               size_t bytes_num = fread(input_buffer, sizeof(uint8_t), BUFFER_SIZE, input);
               file_size += bytes_num;
               for(size_t i = 0; i < bytes_num; ++i) {
                    ++char_freq[input_buffer[i]];
               }
          }

          struct node* root = construct_huffman_tree(char_freq);
          count_huffman_codes(root, huff_code, huff_code_length);

          fseek(input, 0, SEEK_SET);

          size_t in_buffer_pos = 0;
          uint8_t in_byte_pos = 0;

          fwrite(&file_size, sizeof(file_size), 1, output);
          fwrite(char_freq, sizeof(uint32_t), sizeof(char_freq) / sizeof(uint32_t), output);

          while(!feof(input)) {
               size_t bytes_num = fread(input_buffer, sizeof(uint8_t), BUFFER_SIZE, input);
               for(size_t i = 0; i < bytes_num; ++i) {
                    output_buffer[in_buffer_pos] |= ((~(~0 << (8 - in_byte_pos)) & huff_code[input_buffer[i]]) << in_byte_pos);

                    if (huff_code_length[input_buffer[i]] >= 8 - in_byte_pos) {
                         if (++in_buffer_pos == BUFFER_SIZE - 1) {
                              fwrite(output_buffer, sizeof(uint8_t), BUFFER_SIZE - 1, output);
                              memset(output_buffer, 0, BUFFER_SIZE);
                              in_buffer_pos = 0;
                         }
                         output_buffer[in_buffer_pos] |= huff_code[input_buffer[i]] >> (8 - in_byte_pos);
                         in_byte_pos = huff_code_length[input_buffer[i]] - (8 - in_byte_pos);
                    }
                    else {
                         in_byte_pos += huff_code_length[input_buffer[i]];
                    }
               }
          }

          fwrite(output_buffer, sizeof(uint8_t), in_byte_pos ? in_buffer_pos + 1 : in_buffer_pos, output);
     }

     else {

          uint32_t former_file_size;
          uint32_t cur_file_size = 0;

          fread(&former_file_size, sizeof(former_file_size), 1, input);
          fread(char_freq, sizeof(uint32_t), sizeof(char_freq) / sizeof(uint32_t), input);

          struct node* root = construct_huffman_tree(char_freq);
          struct node* cur_node = root;

          size_t in_buffer_pos = 0;

          while(!feof(input)) {
               size_t bytes_num = fread(input_buffer, sizeof(uint8_t), BUFFER_SIZE, input);

               for(size_t i = 0; i < bytes_num; ++i) {
                    for(uint8_t in_byte_pos = 0; in_byte_pos <= 7; ++in_byte_pos) {
                         if (!(cur_node->left_son)) {
                              output_buffer[in_buffer_pos] = cur_node->value;

                              if (++cur_file_size == former_file_size) {
                                   fwrite(output_buffer, sizeof(uint8_t), in_buffer_pos + 1, output);
                                   break;
                              }
                              if (++in_buffer_pos == BUFFER_SIZE) {
                                   fwrite(output_buffer, sizeof(uint8_t), BUFFER_SIZE, output);
                                   in_buffer_pos = 0;
                              }

                              cur_node = root;
                         }

                         if ((1 << in_byte_pos) & input_buffer[i]) {
                              cur_node = cur_node->right_son;
                         }
                         else {
                              cur_node = cur_node->left_son;
                         }
                    }
               }
          }
     }

     fclose(input);
     fclose(output);

     return 0;
}
