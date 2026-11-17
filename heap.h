#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdint.h>

#define HUFF_SYMBOLS 256
#define HUFF_MAX_NODES (2 * HUFF_SYMBOLS - 1)

typedef struct HuffNode {
    uint64_t weight;
    uint16_t number;
    int symbol; /* 0..255 dla liscia, -1 dla wezla wewnetrznego */
    struct HuffNode *left;
    struct HuffNode *right;
} HuffNode;

typedef struct {
    HuffNode *items[HUFF_MAX_NODES];
    size_t size;
} MinHeap;

void heap_init(MinHeap *heap);
int heap_push(MinHeap *heap, HuffNode *node);
HuffNode *heap_pop_min(MinHeap *heap);

#endif
