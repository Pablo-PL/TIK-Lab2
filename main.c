#include "huffman.h"
#include <stdio.h>
#include <string.h>

static void usage(const char *program)
{
    fprintf(stderr,
            "Uzycie:\n"
            "  %s c <wejscie> <wyjscie>  - kompresja\n"
            "  %s t <plik>               - tabela kodow i statystyki\n",
            program, program);
}

int main(int argc, char *argv[])
{
    if (argc == 3 && strcmp(argv[1], "t") == 0)
    {
        uint32_t counts[HUFF_SYMBOLS];
        uint64_t file_size;
        Node *root;
        HuffCode codes[HUFF_SYMBOLS];

        if (count_bytes(argv[2], counts, &file_size) != 0)
            return 1;

        root = huffman_build(counts);
        if (file_size > 0 && root == NULL)
        {
            fprintf(stderr, "Blad budowania drzewa Huffmana.\n");
            return 1;
        }

        huffman_make_codes(root, codes);
        printf("Rozmiar pliku: %llu bajtow\n",
               (unsigned long long)file_size);
        huffman_print_codes(codes, counts, file_size);
        huffman_free(root);
        return 0;
    }

    if (argc == 4 && strcmp(argv[1], "c") == 0)
    {
        if (huffman_compress(argv[2], argv[3]) != 0)
        {
            fprintf(stderr, "Kompresja nie powiodla sie.\n");
            return 1;
        }

        printf("Kompresja zakonczona: %s -> %s\n", argv[2], argv[3]);
        return 0;
    }

    usage(argv[0]);
    return 1;
}
