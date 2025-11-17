# Makefile para Gestão de Campeonatos
TARGET = campeonato
CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRC = Copia.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
