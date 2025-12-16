CC=gcc
CFLAGS=-Wall -Wextra -O2 -std=c11
TARGET=main

.PHONY: all run clean

all: run

$(TARGET): main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
