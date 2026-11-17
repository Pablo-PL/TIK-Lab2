#include "huffman.h"

#include <stdio.h>
#include <string.h>

static void print_usage(const char *program)
{
    fprintf(stderr,
            "Uzycie:\n"
            "  %s c <wejscie> <wyjscie>  - kompresja Huffmana\n"
            "  %s t <plik>               - tabela kodow i statystyki (L2)\n",
            program, program);
}

static int print_table(const char *path)
{
    uint32_t counts[HUFF_SYMBOLS];
    uint64_t file_size;
    HuffTree tree;
    HuffCode codes[HUFF_SYMBOLS];

    if (huffman_count_file(path, counts, &file_size) != 0)
        return -1;

    if (huffman_build_tree(counts, &tree) != 0 ||
        huffman_make_codes(&tree, codes) != 0) {
        fprintf(stderr, "Blad budowania drzewa lub tablicy kodow.\n");
        return -1;
    }

    printf("Rozmiar pliku: %llu bajtow\n",
           (unsigned long long)file_size);

    return huffman_print_codes(codes, counts, file_size);
}

int main(int argc, char *argv[])
{
    if (argc == 4 && strcmp(argv[1], "c") == 0) {
        if (huffman_compress(argv[2], argv[3]) != 0) {
            fprintf(stderr, "Kompresja nie powiodla sie.\n");
            return 1;
        }

        printf("Kompresja zakonczona: %s -> %s\n", argv[2], argv[3]);
        return 0;
    }

    if (argc == 3 && strcmp(argv[1], "t") == 0) {
        if (print_table(argv[2]) != 0)
            return 1;
        return 0;
    }

    print_usage(argv[0]);
    return 1;
}
