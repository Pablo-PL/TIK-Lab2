#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap.h"
#include <stdint.h>

#define HUFF_MAX_CODE_BITS 255

typedef struct {
    uint8_t bits[HUFF_MAX_CODE_BITS];
    uint16_t length;
} HuffCode;

typedef struct {
    HuffNode nodes[HUFF_MAX_NODES];
    size_t used_nodes;
    HuffNode *root;
} HuffTree;

/* Liczenie bajtow: ten sam sposob odczytu strumieniowego co w Z1,
   rozszerzony o liczniki zgodne z formatem HUF1. */
int huffman_count_file(const char *path,
                       uint32_t counts[HUFF_SYMBOLS],
                       uint64_t *file_size);

int huffman_build_tree(const uint32_t counts[HUFF_SYMBOLS], HuffTree *tree);
int huffman_make_codes(const HuffTree *tree,
                       HuffCode codes[HUFF_SYMBOLS]);
int huffman_print_codes(const HuffCode codes[HUFF_SYMBOLS],
                        const uint32_t counts[HUFF_SYMBOLS],
                        uint64_t total);
int huffman_compress(const char *input_path, const char *output_path);

double huffman_entropy(const uint32_t counts[HUFF_SYMBOLS], uint64_t total);

#endif
