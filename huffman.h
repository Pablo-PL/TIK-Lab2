#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap.h"
#include <stdint.h>

#define HUFF_SYMBOLS 256
#define HUFF_MAX_NODES 511
#define HUFF_MAX_CODE_BITS 255

typedef struct {
    uint8_t bits[HUFF_MAX_CODE_BITS];
    uint16_t length;
} HuffCode;

int count_bytes(const char *path, uint32_t counts[HUFF_SYMBOLS],
                uint64_t *file_size);
Node *huffman_build(const uint32_t counts[HUFF_SYMBOLS]);
void huffman_make_codes(const Node *root, HuffCode codes[HUFF_SYMBOLS]);
void huffman_free(Node *root);
double huffman_entropy(const uint32_t counts[HUFF_SYMBOLS], uint64_t total);
int huffman_print_codes(const HuffCode codes[HUFF_SYMBOLS],
                        const uint32_t counts[HUFF_SYMBOLS], uint64_t total);
int huffman_compress(const char *input_path, const char *output_path);

#endif
