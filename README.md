# L2 – Kodowanie Huffmana, część 1: model i koder

## Cel laboratorium
Celem zajęć jest rozpoczęcie realizacji zadania Z2 – stworzenie kompresora Huffmana umożliwiającego kompresję i dekompresję dowolnych plików z zachowaniem identyczności danych bajt po bajcie.

## Zakres L2
- Wyznaczanie liczności 256 możliwych symboli na podstawie pliku wejściowego.
- Implementacja kolejki priorytetowej jako kopca binarnego typu min.
- Budowa drzewa Huffmana.
- Deterministyczne rozstrzyganie remisów w kolejce priorytetowej.
- Generowanie tablicy kodów Huffmana.
- Zapis nagłówka i strumienia zakodowanych danych z wykorzystaniem modułu `BitWriter`.

## Algorytm Huffmana
1. Każdy symbol o niezerowej liczności zostaje liściem drzewa.
2. Liście trafiają do kolejki priorytetowej.
3. Z kolejki pobierane są dwa węzły o najmniejszych wagach.
4. Węzły zostają połączone w nowy węzeł o wadze równej sumie ich wag.
5. Nowy węzeł trafia ponownie do kolejki.
6. Proces powtarza się do uzyskania jednego węzła – korzenia drzewa.
7. Kody symboli wyznaczane są na podstawie ścieżek od korzenia do liści:
   - `0` – lewe dziecko,
   - `1` – prawe dziecko.

## Deterministyczne rozstrzyganie remisów
W przypadku jednakowych wag pierwszeństwo ma węzeł o mniejszym numerze:
- Liście otrzymują numery odpowiadające wartościom symboli (0–255).
- Węzły wewnętrzne otrzymują numery od 256, zgodnie z kolejnością tworzenia.

Zapewnia to identyczne odtworzenie drzewa przez dekoder.

## Format pliku skompresowanego

| Pole | Rozmiar | Opis |
|---|---:|---|
| Sygnatura | 4 B | `HUF1` |
| Rozmiar oryginału | 8 B | `uint64_t`, little endian |
| Liczności | 256 × 4 B | `uint32_t` dla każdego symbolu, little endian |
| Dane | Pozostała część | Strumień kodów, MSB first |

Ostatni bajt strumienia kodów jest dopełniany zerami. Dekoder kończy pracę po odtworzeniu zadeklarowanej liczby symboli.

## Przypadki szczególne
- Pusty plik – brak symboli do zakodowania.
- Plik zawierający tylko jeden rodzaj symbolu – słowo kodowe o długości 1 bitu.

## Punkt kontrolny
Dla pliku `abracadabra.txt` (zawartość `abracadabra`, bez znaku końca linii) należy przygotować:
- Tablicę kodów Huffmana.
- Średnią długość słowa kodowego.
- Porównanie średniej długości kodu z entropią pliku.

## Wykorzystane zagadnienia
- Kodowanie Huffmana.
- Entropia źródła.
- Kod przedrostkowy.
- Kolejka priorytetowa.
- Kopiec binarny typu min.
- Operacje na bitach i bajtach.
- Złożoność obliczeniowa algorytmów.

## Pytania kontrolne
1. Dlaczego kod Huffmana jest kodem przedrostkowym i jakie ma to znaczenie dla dekodowania?
2. Dlaczego dla kodu Huffmana zachodzi nierówność \(H \leq L < H+1\)?
3. Jakie byłyby skutki niedeterministycznego rozstrzygania remisów w kolejce priorytetowej?
4. Jaka jest złożoność obliczeniowa budowy drzewa dla \(k\) różnych symboli przy użyciu kopca?

## Cel końcowy zadania Z2
Program `huff` powinien obsługiwać:

```bash
huff c <wejście> <wyjście>  # kompresja
huff d <wejście> <wyjście>  # dekompresja
```

Po dekompresji plik musi być bajt w bajt identyczny z oryginałem.

**Kontynuacja:** L3 – dekoder, pomiary i rozszerzenie o kanoniczny kod Huffmana.