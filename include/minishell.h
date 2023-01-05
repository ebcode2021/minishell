/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:42:34 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 20:56:26 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "const.h"
# include "error.h"
# include "struct.h"
# include "libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <term.h>
# include <readline/history.h>
# include <readline/readline.h>

extern t_system	g_sys;

/* builtins */
void			builtin_cd(t_exec_block *block);
void			builtin_echo(t_exec_block *exec);
void			builtin_env(void);
void			builtin_exit(t_exec_block *exec);
void			builtin_export(t_exec_block *exec);
void			builtin_pwd(void);
void			builtin_unset(t_exec_block *exec);

/*block_utils.c*/
void			add_block(t_exec_block	**head, t_exec_block *new);
void			free_blocks(t_exec_block *blocks);
void			print_block(t_exec_block *block);
t_exec_block	*new_block(void);

/*builtin_handler.c*/
int				check_export_unset_argv(char *arguments, int unset);
int				is_builtin(char *command);
void			builtin_handler(t_exec_block *exec);

/*command_handler.c*/
char			**current_env_lst(void);
void			command_handler(t_exec_block *exec);

/*here_doc.c*/
char			*get_tmp_filename(int number);
void			here_doc(char *eof, char *tmp_filename);
void			here_doc_handler(t_redirecion *redirection);

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
int				is_quoted(char *str);

/*replace_utils.c*/
char			*str_replace(char *str, char *to_find, char *to_replace);
char			*tilde_replace(char *str);

/*exec_block_parser.c*/
t_exec_block	*str_to_block(char *str);
t_exec_block	*exec_block_parser(char *raw_input);

/*execute_handler.c*/
void			execute_handler(t_exec_block *execs);

/*execute_utils.c*/
pid_t			pipe_n_fork(t_pipe *new_pipe);
void			set_current_cmd(t_exec_block *execs);

/*error_handler.c*/
void			child_error_handler(int signo);
void			print_custom_error(char *location, char *argument, char *msg);
void			print_error(char *location, char *argument);
void			redirection_error(char *file_name, int child);
int				syntax_error(char c, char *trimed);

/*fd_handler.c*/
int				get_redirection_fd(t_exec_block *exec, char *file_name);
void			set_redirection_fd(t_exec_block *exec, int child);
void			change_pipe_fd(t_exec_block *exec, t_pipe *iter_pipe);
void			reset_fd(void);

/*signal_handler*/
void			new_prompt(int signo);
void			set_signal_handler(void);
void			pseudo_sigterm(void);
void			signal_interrupt(int signo);
void			signal_quit(int signo);

/*string_utils.c*/
int				is_blank(char *str);
void			convert_back(char **split, char c);
char			**split_with_char(char *raw_input, char c);
void			free_split(char **splitted);
void			*ft_malloc(size_t size);

/*syntax.c*/
int				syntax_check(char *input);

#endif
