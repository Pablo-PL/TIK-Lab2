# TIK-Lab2 – Kodowanie Huffmana

Projekt realizowany w ramach laboratorium Teorii Informacji i Kodowania (L2).

## Opis projektu

Program w języku C implementujący kompresję danych z wykorzystaniem algorytmu Huffmana.

Aktualna wersja umożliwia zliczanie symboli, budowanie drzewa Huffmana, generowanie tablicy kodów oraz zapis skompresowanych danych w formacie binarnym HUF1.

## Struktura projektu

| Plik | Opis |
|---|---|
| `main.c` | Główna funkcja programu i obsługa argumentów |
| `huffman.c/.h` | Algorytm Huffmana, zliczanie symboli, drzewo i kody |
| `heap.c/.h` | Kolejka priorytetowa oparta na kopcu binarnym typu min |
| `bitio.c/.h` | Odczyt i zapis danych bit po bicie |
| `Makefile` | Automatyzacja kompilacji |
| `abracadabra.txt` | Plik testowy |
| `huff.exe` | Skompilowany program dla Windows |

## Funkcjonalności

- Zliczanie wystąpień 256 możliwych symboli.
- Budowanie deterministycznego drzewa Huffmana.
- Obsługa kolejki priorytetowej z wykorzystaniem kopca binarnego.
- Generowanie tablicy kodów Huffmana.
- Obliczanie entropii i średniej długości kodu.
- Kompresja plików do formatu HUF1.
- Obsługa pustych plików i plików zawierających jeden rodzaj symbolu.

## Kompilacja

Wymagany kompilator GCC oraz Make.

```bash
make
```

Usuwanie plików kompilacji:

```bash
make clean
```

## Uruchamianie

Wyświetlenie tabeli kodów i statystyk:

```bash
./huff t abracadabra.txt
```

Kompresja pliku:

```bash
./huff c wejscie.txt wyjscie.huf
```

## Przykład działania

Dla pliku `abracadabra.txt` zawierającego tekst:

```text
abracadabra
```

Program generuje następujące kody:

| Symbol | Liczność | Kod | Długość |
|---|---:|---|---:|
| a | 5 | 0 | 1 |
| b | 2 | 110 | 3 |
| c | 1 | 100 | 3 |
| d | 1 | 101 | 3 |
| r | 2 | 111 | 3 |

Przykładowe statystyki:

```text
Rozmiar pliku: 11 bajtow

Srednia dlugosc kodu L: 2.636364 bitow/symbol
Entropia H:              2.040373 bitow/symbol
```

## Format HUF1

Nagłówek pliku skompresowanego zawiera:
- Sygnaturę `HUF1` (4 bajty).
- Rozmiar oryginalnego pliku (8 bajtów, little endian).
- Liczności 256 symboli (256 × 4 bajty, little endian).

Pozostałą część stanowi strumień kodów Huffmana zapisany bitowo w kolejności MSB first.

## Status projektu

**L2 – Koder:** zaimplementowany.

**L3 – Dekoder i rozszerzenia:** do realizacji.