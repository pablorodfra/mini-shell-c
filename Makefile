#Indica que compilador
CC = gcc

#Son opciones del compilador:

#-Wall → activa advertencias comunes.
#-Wextra → activa advertencias adicionales.
#-Werror → convierte las advertencias en errores.
#-Iinclude → busca los .h dentro de include/.

CFLAGS = -Wall -Wextra -Werror -Iinclude

NAME = mini_shell.out

# Enumerar todos los archivos fuente
SRC = src/main.c \
	  src/parsing.c

all: $(NAME)

# Convierte por ejemplo src/main.c --> src/main.o
OBJ = $(SRC:.c=.o)

# Para que make recompile lo necesario cuando cambie un .h
$(OBJ): include/parsing.h

# Compila el programa
$(NAME): $(OBJ)
		$(CC) $(OBJ) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@
	
clean:
		rm -f $(OBJ)
	
fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clena fclean re