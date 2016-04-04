#include <stdlib.h>

#include "heap.h"
#include "params.h"


void heap_init(struct heap *restrict h)
{
     *h = (struct heap){
          .size = BASE_SIZE,
          .count = 0,
          .data = malloc(sizeof(type) * BASE_SIZE)
     };
     if (!h->data) exit(1);
}


void heap_push(struct heap *restrict h, type value)
{
     uint32_t index, parent;

     if (h->count == h->size)
     {
          h->size <<= 1;
          h->data = realloc(h->data, sizeof(type) * h->size);
          if (!h->data) exit(1);
     }

     for(index = h->count++; index; index = parent)
     {
          parent = (index - 1) >> 1;
          if CMP(h->data[parent], value) break;
          h->data[index] = h->data[parent];
     }
     h->data[index] = value;
}


void heap_pop(struct heap *restrict h)
{
     uint32_t index, swap, other;

     type temp = h->data[--h->count];

     for(index = 0; 1; index = swap)
     {
          swap = (index << 1) + 1;
          if (swap >= h->count) break;
          other = swap + 1;
          if ((other < h->count) && CMP(h->data[other], h->data[swap])) swap = other;
          if CMP(temp, h->data[swap]) break;

          h->data[index] = h->data[swap];
     }
     h->data[index] = temp;
}
