#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "tree.h"
#include "heap.h"

#define BUFFER_SIZE 1024
#define CHARACTERS_NUM 256


int main(int argc, char *argv[]) {
     if (argc != 4 || !(strcmp(argv[2], "-c") == 0 || strcmp(argv[2], "-x") == 0)) {
          fprintf(stderr, "%s\n\n%s\n%s\n", "Incorrect Usage", "Usage:",
                  "huff input [ -c|-x ] output");
          exit(1);
     }

     uint8_t buffer[BUFFER_SIZE] = {};
     uint8_t output_buffer[BUFFER_SIZE] = {};
     uint32_t char_freq[CHARACTERS_NUM] = {};
     uint32_t huff_code[CHARACTERS_NUM] = {};
     uint8_t huff_code_length[CHARACTERS_NUM] = {};

     FILE* input = fopen(argv[1], "rb");
     FILE* output = fopen(argv[3], "wb");

     while(!feof(input)) {
          size_t bytes_num = fread(buffer, sizeof(uint8_t), BUFFER_SIZE, input);
          for(size_t i = 0; i < bytes_num; ++i) {
               ++char_freq[buffer[i]];
          }
     }

     struct heap new_heap;
     heap_init(&new_heap);
     for(size_t i = 0; i < CHARACTERS_NUM; ++i) {
          struct node* new_node = (struct node*) calloc(1, sizeof(struct node));
          new_node->value = i;
          new_node->freq = char_freq[i];
          heap_push(&new_heap, new_node);
     }

     while(new_heap.count > 1) {
          struct node* min1 = heap_front(&new_heap);
          heap_pop(&new_heap);
          struct node* min2 = heap_front(&new_heap);
          heap_pop(&new_heap);
          struct node* new_node = (struct node*) calloc(1, sizeof(struct node));
          new_node->freq = min1->freq + min2->freq;
          new_node->left_son = min1;
          new_node->right_son = min2;
          heap_push(&new_heap, new_node);
     }

     struct node* root = heap_front(&new_heap);

     count_huffman_codes(root, huff_code, huff_code_length);

     fseek(input, 0, SEEK_SET);

     size_t in_buffer_pos = 0;
     uint8_t in_byte_pos = 0;
     while(!feof(input)) {
          size_t bytes_num = fread(buffer, sizeof(uint8_t), BUFFER_SIZE, input);
          for(size_t i = 0; i < bytes_num; ++i) {
               output_buffer[in_buffer_pos] |= ((~(~0 << (8 - in_byte_pos)) & huff_code[buffer[i]]) << in_byte_pos);

               if(huff_code_length[buffer[i]] >= 8 - in_byte_pos) {
                    ++in_buffer_pos;
                    if (in_buffer_pos == BUFFER_SIZE - 1) {
                         fwrite(output_buffer, sizeof(uint8_t), BUFFER_SIZE - 1, output);
                         in_buffer_pos = 0;
                    }
                    output_buffer[in_buffer_pos] |= huff_code[buffer[i]] >> (8 - in_byte_pos);
                    in_byte_pos = huff_code_length[buffer[i]] - (8 - in_byte_pos);
               }
               else {
                    in_byte_pos += huff_code_length[buffer[i]];
               }
          }
     }

     fwrite(output_buffer, sizeof(uint8_t), in_buffer_pos + 1, output);

     fclose(input);
     fclose(output);

     return 0;
}
