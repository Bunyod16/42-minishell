NAME = minishell
SOURCES = \
	main.c env.c env_utils.c quotes.c spacer.c lexer.c checker.c parser.c \
	str_utils.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS) libft
	$(CC) -o $@ $(OBJECTS) -Llibft -lft -Llibreadline -lreadline

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft bonus

clean:
	rm -f $(OBJECTS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all

.PHONY: all libft clean fclean re