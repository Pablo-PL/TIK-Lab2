#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>
#include <stdint.h>

typedef struct Node {
    uint64_t weight;
    uint16_t number;
    int symbol; /* 0..255 dla liscia, -1 dla wezla wewnetrznego */
    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node **items;
    size_t size;
    size_t capacity;
} MinHeap;

int heap_init(MinHeap *heap, size_t capacity);
void heap_destroy(MinHeap *heap);
int heap_push(MinHeap *heap, Node *node);
Node *heap_pop_min(MinHeap *heap);

#endif
