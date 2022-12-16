NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC_DIR = src/
SRC = minishell.c
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)
INCLUDE = include \
		-I libft \
		-I ${HOME}/.brew/opt/readline/include
LIBFT = libft/libft.a
READLINE = -lreadline -L ~/.brew/opt/readline/lib

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
endif

all : $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ -I $(INCLUDE) $< $(LDFLAGS) 

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE) -o $(NAME)

$(LIBFT):
	@$(MAKE) -C ./libft all

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
