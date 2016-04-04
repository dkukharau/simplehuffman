#ifndef HEAP_H
#define HEAP_H


#include "tree.h"

typedef struct tree_node* type;

#define HEAP_CMP(a, b) ((a->freq) <= (b->freq))
#define HEAP_BASE_SIZE CHARACTERS_NUM


struct heap {
        type *data;
        uint32_t size;
        uint32_t count;
};

void heap_init(struct heap* h);
void heap_push(struct heap* h, type value);
void heap_pop(struct heap* h);


#define heap_front(h) (*(h)->data)

#define heap_term(h) (free((h)->data))


#endif // HEAP_H
