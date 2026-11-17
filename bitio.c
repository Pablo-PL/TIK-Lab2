#include "bitio.h"

void bw_init(BitWriter *writer, FILE *file)
{
    if (writer == NULL)
        return;

    writer->file = file;
    writer->buffer = 0;
    writer->bits_in_buffer = 0;
    writer->error = 0;
}

int bw_write_bit(BitWriter *writer, unsigned bit)
{
    if (writer == NULL || writer->file == NULL || writer->error)
        return -1;

    writer->buffer = (uint8_t)(((unsigned)writer->buffer << 1) | (bit & 1U));
    writer->bits_in_buffer++;

    if (writer->bits_in_buffer == 8U) {
        if (fputc((int)writer->buffer, writer->file) == EOF) {
            writer->error = 1;
            return -1;
        }
        writer->buffer = 0;
        writer->bits_in_buffer = 0;
    }

    return 0;
}

int bw_write_bits(BitWriter *writer, uint32_t value, unsigned bit_count)
{
    unsigned i;

    if (writer == NULL || bit_count > 32U)
        return -1;

    for (i = bit_count; i > 0U; i--) {
        if (bw_write_bit(writer, (value >> (i - 1U)) & 1U) != 0)
            return -1;
    }

    return 0;
}

int bw_flush(BitWriter *writer)
{
    if (writer == NULL || writer->file == NULL || writer->error)
        return -1;

    if (writer->bits_in_buffer > 0U) {
        writer->buffer = (uint8_t)(writer->buffer <<
                                   (8U - writer->bits_in_buffer));
        if (fputc((int)writer->buffer, writer->file) == EOF) {
            writer->error = 1;
            return -1;
        }
        writer->buffer = 0;
        writer->bits_in_buffer = 0;
    }

    return 0;
}
