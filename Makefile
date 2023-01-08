NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC_DIR = src/
SRC = minishell.c \
	block_utils.c \
	builtin_handler.c \
	command_handler.c \
	error_handler.c \
	exec_block_parser.c \
	execute_handler.c \
	execute_utils.c \
	fd_handler.c \
	here_doc.c \
	quote_handler.c \
	redirection_utils.c \
	replace_utils.c \
	syntax.c \
	signal_handler.c \
	string_utils.c \
	init.c \
	sort_utils.c
BUILT_IN = builtins/cd.c builtins/pwd.c builtins/echo.c builtins/env.c builtins/export.c builtins/unset.c builtins/exit.c
SRCS = $(addprefix $(SRC_DIR), $(SRC)) $(addprefix $(SRC_DIR), $(BUILT_IN))
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
INCLUDE = include \
		-I libft \
		-I ${HOME}/.brew/opt/readline/include
LIBFT = libft/libft.a
READLINE = -lreadline -L ~/.brew/opt/readline/lib
#READLINE = -lreadline -L /usr/local/Cellar/readline/8.2.1/lib

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ -I $(INCLUDE) $< $(LDFLAGS) 

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft bonus

clean : 
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all

sanitize :
	make SANITIZE=1 re

.PHONY: all clean fclean re libft bonus sanitize
