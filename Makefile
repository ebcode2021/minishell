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
	init.c \
	quote_handler.c \
	redirection_utils.c \
	replace_utils.c \
	sort_utils.c \
	syntax.c \
	string_utils.c \
	signal_handler.c \
	mem_utils.c
BUILT_IN_DIR = src/builtins/
BUILT_IN = cd.c \
		pwd.c \
		echo.c \
		env.c \
		export.c \
		unset.c \
		exit.c
SRCS = $(addprefix $(SRC_DIR), $(SRC)) $(addprefix $(BUILT_IN_DIR), $(BUILT_IN))
OBJS = $(SRCS:.c=.o)

INCLUDE = include \
		-I libft \
		-I ${HOME}/.brew/opt/readline/include
LIBFT = libft/libft.a
READLINE = -lreadline -L ~/.brew/opt/readline/lib
#READLINE = -lreadline -L /usr/local/Cellar/readline/8.2.1/lib
LIBFT_RULE = @$(MAKE) -C ./libft bonus

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
	LIBFT_RULE = @$(MAKE) -C ./libft bonus sanitize
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ -I $(INCLUDE) $< $(LDFLAGS) 

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT):
	$(LIBFT_RULE)

clean : 
	@$(MAKE) -C ./libft clean
	rm -rf $(OBJS) $(OBJS_BONUS)

fclean : clean
	@$(MAKE) -C ./libft fclean
	rm -rf $(NAME) $(NAME_BONUS)

re : fclean all

sanitize :
	make SANITIZE=1 re

.PHONY: all clean fclean re libft sanitize
