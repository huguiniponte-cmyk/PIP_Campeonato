# Makefile para Gestão de Campeonatos
TARGET = lega
CC = gcc
CFLAGS = -Wall -Wextra -std=c99

# Diretórios
SRC_DIR = src
INCLUDE_DIR = include

# Ficheiros fonte
SRC = $(SRC_DIR)/lega.c \
      $(SRC_DIR)/equipas.c \
      $(SRC_DIR)/jogos.c \
      $(SRC_DIR)/estatisticas.c \
      $(SRC_DIR)/classificacao.c  \

# Ficheiros objeto
OBJ = $(SRC:.c=.o)

# Regra principal
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Regra para compilar cada ficheiro .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Limpar ficheiros compilados
clean:
	rm -f $(OBJ) $(TARGET)

# Executar o programa
run: $(TARGET)
	./$(TARGET)

.PHONY: clean run
