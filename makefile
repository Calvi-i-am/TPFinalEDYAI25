CC = gcc
CFLAGS = -Wall -Werror -std=c99 -g
TARGET = programa
SRCS = main.c \
       Funciones/Funciones.c \
       Tablas/Tablas.c \
       Sentencias/Sentencias.c \
       Parser/Parser.c \
       Listas/Listas.c
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean run

run: $(TARGET)
	.
