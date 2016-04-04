#include "tree.h"

typedef struct node* type;

#define CMP(a, b) ((a->freq) <= (b->freq))
#define BASE_SIZE CHARACTERS_NUM


struct heap
{
        uint32_t size;
        uint32_t count;
        type *data;
};

void heap_init(struct heap *restrict h);
void heap_push(struct heap *restrict h, type value);
void heap_pop(struct heap *restrict h);


#define heap_front(h) (*(h)->data)

#define heap_term(h) (free((h)->data))
