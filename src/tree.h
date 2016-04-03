#ifndef NODE_H
#define NODE_H

#include <stdint.h>


struct node {
     uint8_t value;
     uint32_t freq;
     struct node* left_son;
     struct node* right_son;
};


void count_huffman_codes(struct node* root, uint32_t huff_code[], uint8_t huff_code_length[]);

#endif // NODE_H
