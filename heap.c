#include "heap.h"

static int node_less(const HuffNode *a, const HuffNode *b)
{
    if (a->weight != b->weight)
        return a->weight < b->weight;

    return a->number < b->number;
}

void heap_init(MinHeap *heap)
{
    if (heap != NULL)
        heap->size = 0;
}

int heap_push(MinHeap *heap, HuffNode *node)
{
    size_t i;

    if (heap == NULL || node == NULL || heap->size >= HUFF_MAX_NODES)
        return -1;

    i = heap->size++;
    heap->items[i] = node;

    while (i > 0) {
        size_t parent = (i - 1U) / 2U;
        HuffNode *tmp;

        if (!node_less(heap->items[i], heap->items[parent]))
            break;

        tmp = heap->items[i];
        heap->items[i] = heap->items[parent];
        heap->items[parent] = tmp;
        i = parent;
    }

    return 0;
}

HuffNode *heap_pop_min(MinHeap *heap)
{
    HuffNode *minimum;
    size_t i;

    if (heap == NULL || heap->size == 0)
        return NULL;

    minimum = heap->items[0];
    heap->size--;

    if (heap->size == 0)
        return minimum;

    heap->items[0] = heap->items[heap->size];
    i = 0;

    for (;;) {
        size_t left = 2U * i + 1U;
        size_t right = left + 1U;
        size_t smallest = i;
        HuffNode *tmp;

        if (left < heap->size &&
            node_less(heap->items[left], heap->items[smallest]))
            smallest = left;

        if (right < heap->size &&
            node_less(heap->items[right], heap->items[smallest]))
            smallest = right;

        if (smallest == i)
            break;

        tmp = heap->items[i];
        heap->items[i] = heap->items[smallest];
        heap->items[smallest] = tmp;
        i = smallest;
    }

    return minimum;
}
