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
	mem_utils.c \
	quote_handler.c \
	redirection_utils.c \
	replace_utils.c \
	signal_handler.c \
	sort_utils.c \
	string_utils.c \
	syntax.c \
	system_utils.c
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

.PHONY: all clean fclean re libft
