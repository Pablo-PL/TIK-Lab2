CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
LDLIBS = -lm

TARGET = huff
SOURCE = main.c huffman.c heap.c bitio.c

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDLIBS)

clean:
	rm -f $(TARGET) $(TARGET).exe

.PHONY: all clean
