#include "heap.h"
#include <stdlib.h>

static int node_less(const Node *a, const Node *b)
{
    if (a->weight != b->weight)
        return a->weight < b->weight;

    return a->number < b->number;
}

int heap_init(MinHeap *heap, size_t capacity)
{
    if (heap == NULL)
        return -1;

    heap->items = NULL;
    heap->size = 0;
    heap->capacity = capacity;

    if (capacity == 0)
        return 0;

    heap->items = malloc(capacity * sizeof(*heap->items));
    if (heap->items == NULL)
        return -1;

    return 0;
}

void heap_destroy(MinHeap *heap)
{
    if (heap == NULL)
        return;

    free(heap->items);
    heap->items = NULL;
    heap->size = 0;
    heap->capacity = 0;
}

int heap_push(MinHeap *heap, Node *node)
{
    if (heap == NULL || node == NULL || heap->size >= heap->capacity)
        return -1;

    size_t i = heap->size++;
    heap->items[i] = node;

    while (i > 0)
    {
        size_t parent = (i - 1) / 2;
        if (!node_less(heap->items[i], heap->items[parent]))
            break;

        Node *tmp = heap->items[i];
        heap->items[i] = heap->items[parent];
        heap->items[parent] = tmp;
        i = parent;
    }

    return 0;
}

Node *heap_pop_min(MinHeap *heap)
{
    if (heap == NULL || heap->size == 0)
        return NULL;

    Node *minimum = heap->items[0];
    heap->size--;

    if (heap->size == 0)
        return minimum;

    heap->items[0] = heap->items[heap->size];

    size_t i = 0;
    for (;;)
    {
        size_t left = 2 * i + 1;
        size_t right = left + 1;
        size_t smallest = i;

        if (left < heap->size &&
            node_less(heap->items[left], heap->items[smallest]))
            smallest = left;

        if (right < heap->size &&
            node_less(heap->items[right], heap->items[smallest]))
            smallest = right;

        if (smallest == i)
            break;

        Node *tmp = heap->items[i];
        heap->items[i] = heap->items[smallest];
        heap->items[smallest] = tmp;
        i = smallest;
    }

    return minimum;
}
