/**
 *  @file tree.h
 *  @brief This header file contains Huffman tree node data structure definition
 *         as well as all function declarations needed to work with one
 *  @author Daniel Kukharau
 */
#ifndef TREE_NODE_H
#define TREE_NODE_H


#include <stdint.h>

/**
 *  @brief Huffman tree node data structure definition
 */
struct tree_node {
     struct tree_node* left_son; /**< Pointer to the left son of the node */
     struct tree_node* right_son; /**< Pointer to the right son of the node */
     uint32_t freq; /**< Frequency of the symbol represented by the node(only for leaf nodes) */
     uint8_t value; /**< Symbol represented by node(only for leaf nodes) */
};

/**
 *  @brief Construct a Huffman tree
 *  @param char_freq Array of the symbol frequencies of the data to be compressed
 *  @return Pointer to the root node of the Huffman tree
 */
struct tree_node* construct_huffman_tree(uint32_t char_freq[]);

/**
 *  @brief Compute Huffman codes used to compress data
 *  @param root Pointer to the root node of the Huffman tree
 *  @param huff_code  Array to write Huffman codes to
 *  @param huff_length  Array to write Huffman code length to
 */
void count_huffman_codes(struct tree_node* root, uint32_t huff_code[], uint32_t huff_code_length[]);

/**
 *  @brief Helper function used to compute Huffman codes
 *  @param elem Pointer to the curent node
 *  @param level Current tree level
 *  @param code Current Huffman code
 *  @param huff_code  Array to write Huffman codes to
 *  @param huff_length  Array to write Huffman code length to
 */
void _count_huffman_codes_helper(struct tree_node* elem, uint32_t level, uint32_t code,
                                 uint32_t huff_code[], uint32_t huff_code_length[]);

/**
 *  @brief Release resources used by a Huffman tree
 *  @param root Pointer to the root node of the Huffman tree
 */
void release_huffman_tree(struct tree_node* root);


#endif // TREE_NODE_H
