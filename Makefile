NAME = minishell
SOURCES = \
	main.c env.c env_utils.c quotes.c piper.c spacer.c expander.c lexer.c \
	checker.c parser.c parser_utils.c str_utils.c execute_binary.c execute.c \
	here_doc.c builtins.c builtins_2.c cd.c exit.c
OBJECTS = $(SOURCES:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include

all: $(NAME)

$(NAME): $(OBJECTS) libft
	$(CC) -o $@ $(OBJECTS) -Llibft -lft -L/opt/homebrew/opt/readline/lib -lreadline

%.o: %.c
	$(CC) -c $(CFLAGS) $?

libft:
	make -C libft bonus

clean:
	$(RM) $(OBJECTS)
	make -C libft clean

fclean: clean
	$(RM) $(NAME) libft/libft.a

re: fclean all

.PHONY: all libft clean fclean re
