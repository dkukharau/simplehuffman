#include <stdlib.h>
#include <stdint.h>
#include "tree.h"
#include "heap.h"
#include "params.h"


struct node* construct_huffman_tree(uint32_t char_freq[]) {
     struct heap new_heap;
     heap_init(&new_heap);
     for(size_t i = 0; i < CHARACTERS_NUM; ++i) {
          if(char_freq[i]) {
               struct node* new_node = (struct node*) calloc(1, sizeof(struct node));
               new_node->freq = char_freq[i];
               new_node->value = i;
               heap_push(&new_heap, new_node);
          }
     }

     while(new_heap.count > 1) {
          struct node* min1 = heap_front(&new_heap);
          heap_pop(&new_heap);
          struct node* min2 = heap_front(&new_heap);
          heap_pop(&new_heap);
          struct node* new_node = (struct node*) calloc(1, sizeof(struct node));
          new_node->freq = min1->freq + min2->freq;
          new_node->right_son = min1;
          new_node->left_son = min2;
          heap_push(&new_heap, new_node);
     }

     struct node* root = heap_front(&new_heap);
     heap_term(&new_heap);
     return root;
}

void count_huffman_codes(struct node* root, uint32_t huff_code[], uint8_t huff_code_length[]) {
     count_huffman_codes_helper(root, 0, 0, huff_code, huff_code_length);
}

void count_huffman_codes_helper(struct node* elem, uint8_t level, uint32_t code,
                                uint32_t huff_code[], uint8_t huff_code_length[]) {

     if (elem->left_son == NULL && elem->right_son == NULL) {
          huff_code[elem->value] = code;
          huff_code_length[elem->value] = level;
     }
     else {
          count_huffman_codes_helper(elem->left_son, level + 1, code, huff_code, huff_code_length);
          count_huffman_codes_helper(elem->right_son, level + 1, (1 << level) | code, huff_code, huff_code_length);
     }
}
