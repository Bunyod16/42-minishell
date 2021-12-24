NAME = minishell
SOURCES = main.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -D READLINE_LIBRARY=1

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $@ $^ -Llibreadline -lreadline

%.o: %.c
	$(CC) -c $(CFLAGS) $?

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re