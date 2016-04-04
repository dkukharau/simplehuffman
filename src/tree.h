#ifndef TREE_NODE_H
#define TREE_NODE_H


#include <stdint.h>


struct tree_node {
     struct tree_node* left_son;
     struct tree_node* right_son;
     uint32_t freq;
     uint8_t value;
};

void count_huffman_codes(struct tree_node* root, uint32_t huff_code[], uint32_t huff_code_length[]);

void _count_huffman_codes_helper(struct tree_node* elem, uint32_t level, uint32_t code,
                                 uint32_t huff_code[], uint32_t huff_code_length[]);

struct tree_node* construct_huffman_tree(uint32_t char_freq[]);
void release_huffman_tree(struct tree_node* root);


#endif // TREE_NODE_H
