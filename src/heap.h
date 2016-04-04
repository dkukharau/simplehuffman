/**
 *   @file heap.h
 *   @brief This header file contains heap struct definition as well
 *          as all functions declarations needed to work with heap
 *   @author Daniel Kukharau
 */

#ifndef HEAP_H
#define HEAP_H


#include "tree.h"

/**
 *  @brief Defines data type used by heap
 */
typedef struct tree_node* type;

/**
 *  @brief Defines comparison logic used by heap
 */
#define HEAP_CMP(a, b) ((a->freq) <= (b->freq))

/**
 *  @brief Defines heap initial size
 */
#define HEAP_BASE_SIZE CHARACTERS_NUM

/**
 *  @brief Heap struct definition
 */
struct heap {
        type *data; /**< Pointer to the top of the heap */
        uint32_t size; /**< Number of elements reserved by heap */
        uint32_t count; /**< Number of actual elements in heap */
};

/**
 *  @brief Initialize a heap
 *  @param h Pointer to the heap to be initialized
 *  @note You must call this method before performing any operations on a heap
 */
void heap_init(struct heap* h);

/**
 *  @brief Add element to a heap
 *  @param h Pointer to the heap to push to
 *  @param value Element to add to the heap
 */
void heap_push(struct heap* h, type value);

/**
 *  @brief Remove element from top of a heap
 *  @param h Pointer to the heap to pop
 *  @note Heap must not be empty when you call this method
 */
void heap_pop(struct heap* h);

/**
 *  @brief Remove element from top of a heap
 *  @param h Pointer to the heap to remove from
 *  @note Heap must not be empty when you call this macro
 */
#define heap_front(h) (*(h)->data)

/**
 *  @brief Release resources used by a heap
 *  @param h Pointer to the heap to release
 *  @note Heap must not be empty when you call this macro
 */
#define heap_term(h) (free((h)->data))


#endif // HEAP_H
