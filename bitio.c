#include "bitio.h"

void bw_init(BitWriter *w, FILE *f)
{
    w->f = f;
    w->buf = 0;
    w->nbits = 0;
    w->error = 0;
}

int bw_write_bit(BitWriter *w, int bit)
{
    if (w == NULL || w->f == NULL || w->error)
        return -1;

    w->buf = (uint8_t)((w->buf << 1) | (bit & 1));
    w->nbits++;

    if (w->nbits == 8)
    {
        if (fputc(w->buf, w->f) == EOF)
        {
            w->error = 1;
            return -1;
        }
        w->buf = 0;
        w->nbits = 0;
    }
    return 0;
}

int bw_write_bits(BitWriter *w, uint32_t value, int n)
{
    if (w == NULL || n < 0 || n > 32)
        return -1;

    for (int i = n - 1; i >= 0; i--)
        if (bw_write_bit(w, (int)((value >> i) & 1U)) != 0)
            return -1;

    return 0;
}

int bw_flush(BitWriter *w)
{
    if (w == NULL || w->f == NULL || w->error)
        return -1;

    if (w->nbits > 0)
    {
        w->buf = (uint8_t)(w->buf << (8 - w->nbits));
        if (fputc(w->buf, w->f) == EOF)
        {
            w->error = 1;
            return -1;
        }
        w->buf = 0;
        w->nbits = 0;
    }
    return 0;
}

void br_init(BitReader *r, FILE *f)
{
    r->f = f;
    r->buf = 0;
    r->nbits = 0;
}

int br_read_bit(BitReader *r)
{
    if (r == NULL || r->f == NULL)
        return -1;

    if (r->nbits == 0)
    {
        int byte = fgetc(r->f);
        if (byte == EOF)
            return -1;
        r->buf = (uint8_t)byte;
        r->nbits = 8;
    }

    int bit = (r->buf >> 7) & 1;
    r->buf <<= 1;
    r->nbits--;
    return bit;
}

int br_read_bits(BitReader *r, int n, uint32_t *out)
{
    if (r == NULL || out == NULL || n < 0 || n > 32)
        return -1;

    *out = 0;
    for (int i = 0; i < n; i++)
    {
        int bit = br_read_bit(r);
        if (bit < 0)
            return -1;
        *out = (*out << 1) | (uint32_t)bit;
    }
    return 0;
}
