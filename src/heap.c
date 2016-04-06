/**
 *  @file heap.c
 *  @brief This file contains all function definitions
 *         needed to work with heap data structure
 *  @author Daniel Kukharau
 */
#include <stdlib.h>
#include <stdio.h>

#include "heap.h"
#include "params.h"


void heap_init(struct heap* h) {
     *h = (struct heap) {
          .size = HEAP_BASE_SIZE,
          .count = 0,
          .data = malloc(sizeof(type) * HEAP_BASE_SIZE)
     };
     if (!h->data) {
          perror("");
          exit(1);
     }
}


void heap_push(struct heap* h, type value) {
     uint32_t index, parent;

     if (h->count == h->size) {
          h->size <<= 1;
          h->data = realloc(h->data, sizeof(type) * h->size);
          if (!h->data) {
               perror("");
               exit(1);
          }
     }

     for(index = h->count++; index; index = parent) {
          parent = (index - 1) >> 1;
          if HEAP_CMP(h->data[parent], value) break;
          h->data[index] = h->data[parent];
     }
     h->data[index] = value;
}


void heap_pop(struct heap* h) {
     uint32_t index, swap, other;

     type temp = h->data[--h->count];

     for(index = 0; 1; index = swap) {
          swap = (index << 1) + 1;
          if (swap >= h->count) break;
          other = swap + 1;
          if ((other < h->count) && HEAP_CMP(h->data[other], h->data[swap])) swap = other;
          if HEAP_CMP(temp, h->data[swap]) break;

          h->data[index] = h->data[swap];
     }
     h->data[index] = temp;
}
