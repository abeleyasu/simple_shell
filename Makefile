CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic
SRC = main.c shell.c builtin.c
OBJ = $(SRC:.c=.o)
NAME = hsh
all: $(NAME)
$(NAME): $(OBJ)
$(CC) $(CFLAGS) -o $(NAME) $(OBJ)
%.o: %.c
$(CC) $(CFLAGS) -c $< -o $@
clean:
rm -f $(OBJ)
fclean: clean
rm -f $(NAME)
re: fclean all
