#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "tree.h"
#include "heap.h"
#include "params.h"
#include "huff.h"

#define MIN(x, y) (((x) < (y)) ? (x) : (y))


void compress_file(FILE* input, FILE* output) {

     uint8_t input_buffer[BUFFER_SIZE] = {};
     uint8_t output_buffer[BUFFER_SIZE] = {};
     uint32_t char_freq[CHARACTERS_NUM] = {};

     uint32_t huff_code[CHARACTERS_NUM] = {};
     uint32_t huff_code_length[CHARACTERS_NUM] = {};
     uint32_t file_size = 0;

     while(!feof(input)) {

          size_t bytes_num = fread(input_buffer, sizeof(uint8_t), BUFFER_SIZE, input);
          if (ferror(input)) {
               perror("");
               exit(1);
          }

          file_size += bytes_num;
          for(size_t i = 0; i < bytes_num; ++i) {
               ++char_freq[input_buffer[i]];
          }
     }

     struct tree_node* root = construct_huffman_tree(char_freq);
     count_huffman_codes(root, huff_code, huff_code_length);

     if (fseek(input, 0, SEEK_SET)) {
          perror("");
          exit(1);
     }


     size_t in_buffer_pos = 0;
     uint8_t in_byte_pos = 0;

     fwrite(&file_size, sizeof(file_size), 1, output);
     if (ferror(output)) {
          perror("");
          exit(1);
     }

     fwrite(char_freq, sizeof(uint32_t), sizeof(char_freq) / sizeof(uint32_t), output);
     if (ferror(output)) {
          perror("");
          exit(1);
     }

     while(!feof(input)) {

          size_t bytes_num = fread(input_buffer, sizeof(uint8_t), BUFFER_SIZE, input);
          if (ferror(input)) {
               perror("");
               exit(1);
          }

          for(size_t i = 0; i < bytes_num; ++i) {
               uint32_t cur_code_length = huff_code_length[input_buffer[i]];
               uint32_t cur_code = huff_code[input_buffer[i]];
               while (cur_code_length > 0) {
                    uint32_t trailing_bits_num = 8 - in_byte_pos;
                    output_buffer[in_buffer_pos] |= ((~(0xFFFF << trailing_bits_num)) & cur_code) << in_byte_pos;
                    uint32_t written_bits_num = MIN(cur_code_length, trailing_bits_num);
                    cur_code_length -= written_bits_num;
                    in_byte_pos += written_bits_num;
                    cur_code >>= written_bits_num;
                    if (in_byte_pos == 8) {
                         if (++in_buffer_pos == BUFFER_SIZE - 1) {
                              fwrite(output_buffer, sizeof(uint8_t), BUFFER_SIZE - 1, output);
                              memset(output_buffer, 0, BUFFER_SIZE);
                              in_buffer_pos = 0;
                         }
                         in_byte_pos = 0;
                    }
               }
          }
     }

     fwrite(output_buffer, sizeof(uint8_t), in_byte_pos ? in_buffer_pos + 1 : in_buffer_pos, output);
     if (ferror(output)) {
          perror("");
          exit(1);
     }

     release_huffman_tree(root);
}


void decompress_file(FILE* input, FILE* output) {

     uint8_t input_buffer[BUFFER_SIZE] = {};
     uint8_t output_buffer[BUFFER_SIZE] = {};
     uint32_t char_freq[CHARACTERS_NUM] = {};

     uint32_t former_file_size;
     uint32_t cur_file_size = 0;

     fread(&former_file_size, sizeof(former_file_size), 1, input);
     if (ferror(input)) {
          perror("");
          exit(1);
     }

     fread(char_freq, sizeof(uint32_t), sizeof(char_freq) / sizeof(uint32_t), input);
     if (ferror(input)) {
          perror("");
          exit(1);
     }


     struct tree_node* root = construct_huffman_tree(char_freq);
     struct tree_node* cur_node = root;

     size_t in_buffer_pos = 0;

     while(!feof(input)) {

          size_t bytes_num = fread(input_buffer, sizeof(uint8_t), BUFFER_SIZE, input);
          if (ferror(input)) {
               perror("");
               exit(1);
          }

          for(size_t i = 0; i < bytes_num; ++i) {
               for(uint8_t in_byte_pos = 0; in_byte_pos <= 7; ++in_byte_pos) {
                    if (!(cur_node->left_son)) {
                         output_buffer[in_buffer_pos] = cur_node->value;

                         if (++cur_file_size == former_file_size) {

                              fwrite(output_buffer, sizeof(uint8_t), in_buffer_pos + 1, output);
                              if (ferror(output)) {
                                   perror("");
                                   exit(1);
                              }
                              break;
                         }
                         if (++in_buffer_pos == BUFFER_SIZE) {

                              fwrite(output_buffer, sizeof(uint8_t), BUFFER_SIZE, output);
                              if (ferror(output)) {
                                   perror("");
                                   exit(1);
                              }

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
     release_huffman_tree(root);
}
