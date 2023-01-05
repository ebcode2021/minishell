/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:42:34 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 10:38:22 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "const.h"
# include "error.h"
# include "struct.h"
# include "libft.h"
# include <fcntl.h>
# include <dirent.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <curses.h>
# include <term.h>

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
char			*double_quote_handler(char *str);
char			*get_env(char *str, size_t *index);
char			*expand_env(char *str);
char			*expanded_join(char **split);

/*redirection_utils.c*/
void			add_redirection(t_redirecion **head, \
								char **split, size_t *index);
char			**set_redirections(t_exec_block *block, char **split);
char			**set_arguments(char **split);

/*string_utils.c*/
int				is_blank(char *str);
char			*str_replace(char *str, char *to_find, char *to_replace);
void			convert_back(char **split, char c);
char			**split_with_char(char *raw_input, char c);
char			*tilde_replace(char *str);

/*block_utils.c*/
t_exec_block	*block_new(void);
void			block_add(t_exec_block	**head, t_exec_block *new);
void			free_block(t_exec_block *blocks);
void			print_block(t_exec_block *block);

/*exec_block_parser.c*/
t_exec_block	*str_to_block(char *str);
t_exec_block 	*exec_block_parser(char *raw_input);

/*execute.c*/
void			execute_handler(t_exec_block *execs);

/*error_handler.c*/
void			print_custom_error_msg(char *location, char *argument, char *message);
void			print_error_msg(char *location, char *argument);
void			redirection_error(char *file_name, int child);

/*builtin_handler.c*/
int				is_builtin(char *command);
void			builtin_handler(t_exec_block *exec);
int				check_export_unset_argv(char *arguments, int unset);

/*command_handler.c*/
void			command_handler(t_exec_block *exec);
void			redirection_error(char *file_name, int child);
char			**current_env_lst();

/*fd_handler.c*/
int				get_redirection_fd(t_exec_block *exec, char *file_name);
void			set_redirection_fd(t_exec_block *exec, int child);
void			change_pipe_fd(t_exec_block *exec, t_pipe *iter_pipe);
void			reset_fd(void);

/*builtins*/
void			builtin_cd(t_exec_block *block);
void			builtin_pwd(void);
void			builtin_env(void);
void			builtin_echo(t_exec_block *execs);
void			builtin_unset(t_exec_block *exec);
void			builtin_export(t_exec_block *exec);
void			builtin_exit(t_exec_block *execs);

/*signals*/
void			set_signal_handler(void);
void			pseudo_sigterm(void);

#endif
