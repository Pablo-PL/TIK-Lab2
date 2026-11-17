# TIiK – L2: Kodowanie Huffmana (model i koder)

Projekt realizuje zakres L2 z instrukcji laboratoryjnej. Zawiera model zrodlowy, kopiec binarny typu min, deterministyczne budowanie drzewa Huffmana, tablice kodow oraz zapis pliku w formacie HUF1.

**To jest wersja L2 – nie zawiera dekodera.** Program nie obsluguje polecenia `huff d`; dekoder jest zakresem kolejnych zajec L3.

## Zawartosc

- `main.c` – obsluga polecen `c` (kompresja) i `t` (tabela kontrolna L2).
- `huffman.c`, `huffman.h` – liczenie symboli, budowa drzewa, tablica kodow, statystyki i kompresja.
- `heap.c`, `heap.h` – kolejka priorytetowa oparta na kopcu binarnym typu min.
- `bitio.c`, `bitio.h` – modul BitWriter, zapis MSB first i dopelnianie ostatniego bajtu zerami.
- `abracadabra.txt` – plik kontrolny zawierajacy dokladnie `abracadabra`, bez znaku konca linii.

## Kompilacja

GCC / MinGW-w64:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 main.c huffman.c heap.c bitio.c -o huff -lm
```

Windows:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 main.c huffman.c heap.c bitio.c -o huff.exe -lm
```

Mozna tez uzyc:

```bash
make
```

## Uruchamianie

Kompresja:

```bash
./huff c wejscie.bin wyjscie.huf
```

Tabela kodow i statystyki – punkt kontrolny L2:

```bash
./huff t abracadabra.txt
```

Na Windows mozna wpisac `./huff.exe` albo `huff.exe`.

## Format HUF1

Naglowek i dane sa zapisywane dokladnie w kolejnosci:

1. 4 bajty: ASCII `HUF1`.
2. 8 bajtow: rozmiar oryginalu `n` jako `uint64_t`, little endian.
3. 256 licznikow: kazdy jako `uint32_t`, little endian (lacznie 1024 bajty).
4. Strumien bitow kodow Huffmana, MSB first. Ostatni niepelny bajt jest dopelniany zerami po prawej stronie.

Dekoder ma zakonczyc odczyt po odtworzeniu `n` symboli; nie nalezy interpretowac bitow dopelnienia. Dekodera w tym projekcie L2 celowo nie ma.

## Deterministyczne drzewo

Kopiec porownuje wezly najpierw wedlug rosnacej wagi, a przy remisie wedlug rosnacego numeru wezla. Liscie maja numery rowne wartosci bajtu (0–255). Wezly wewnetrzne otrzymuja numery 256, 257, ... w kolejnosci tworzenia. Pierwszy zdjety wezel staje sie lewym dzieckiem (bit 0), drugi – prawym (bit 1).

## Przypadki szczegolne

- Pusty plik: zapisuje sie naglowek z `n = 0` i 256 zerowymi licznikami; czesc danych jest pusta.
- Jeden rodzaj bajtu: symbol otrzymuje kod `0` o dlugosci 1 bitu, zgodnie z instrukcja.
- Liczniki symboli maja format `uint32_t`; jesli liczba wystapien ktoregos symbolu przekroczy ten zakres, kompresja zostaje przerwana.
- Pliki sa otwierane binarnie. Bledy odczytu, zapisu i zamykania plikow sa sygnalizowane kodem wyjscia roznym od zera.

## Punkt kontrolny: abracadabra

Plik testowy nie zawiera znaku nowej linii. Oczekiwane kody wynikajace z regul rozstrzygania remisow:

| Symbol | Licznosc | Kod | Dlugosc |
|---|---:|---|---:|
| a | 5 | `0` | 1 |
| b | 2 | `110` | 3 |
| c | 1 | `100` | 3 |
| d | 1 | `101` | 3 |
| r | 2 | `111` | 3 |

Srednia dlugosc: `2.090909` bitow/symbol. Entropia: okolo `2.040373` bitow/symbol.
