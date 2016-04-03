#include <stdlib.h>
#include <stdint.h>
#include "tree.h"


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
