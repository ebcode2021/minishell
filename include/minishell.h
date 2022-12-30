/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:42:34 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/31 00:41:09 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "struct.h"
# include "error.h"
# include "const.h"

extern t_system	sys;

void			free_split(char **splitted);
void			exit_with_error_msg(const char *msg);
void			*ft_malloc(size_t size);
int				syntax_check(char *input);

/*here_doc.c*/
char			*get_tmp_filename(int number);
void			here_doc(char *eof, char *tmp_filename);
int				here_doc_handler(t_redirecion *redirection);

/*quote_handler.c*/
char			*quote_handler(char *str);
char			*single_quote_handler(char *str);
char			*double_quote_handler(char *str);
char			*get_env(char *str, size_t *index);
char			*expand_env(char *str);

/*redirection_utils.c*/
void			add_redirection(t_redirecion **head, \
								char **split, size_t *index);
char			**set_redirections(t_exec_block *block, char **split);
char			**set_arguments(char **split);

/*string_utils.c*/
char			*str_replace(char *str, char *to_find, char *to_replace);
void			convert_back(char **split, char c);
char			**split_with_char(char *raw_input, char c);

/*block_utils.c*/
t_exec_block	*block_new(void);
void			block_add(t_exec_block	**head, t_exec_block *new);
void			free_block(t_exec_block *blocks);
void			print_block(t_exec_block *block);

/*exec_block_parser.c*/
t_exec_block	*str_to_block(char *str);
t_exec_block 	*exec_block_parser(char *raw_input);

#endif
