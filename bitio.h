#ifndef BITIO_H
#define BITIO_H

#include <stdint.h>
#include <stdio.h>

typedef struct {
    FILE *file;
    uint8_t buffer;
    unsigned bits_in_buffer;
    int error;
} BitWriter;

void bw_init(BitWriter *writer, FILE *file);
int bw_write_bit(BitWriter *writer, unsigned bit);
int bw_write_bits(BitWriter *writer, uint32_t value, unsigned bit_count);
int bw_flush(BitWriter *writer);

#endif
