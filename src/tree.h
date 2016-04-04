#ifndef NODE_H
#define NODE_H

#include <stdint.h>


struct node {
     struct node* left_son;
     struct node* right_son;
     uint32_t freq;
     uint8_t value;
};


void count_huffman_codes(struct node* root, uint32_t huff_code[], uint8_t huff_code_length[]);

struct node* construct_huffman_tree(uint32_t char_freq[]);

#endif // NODE_H
