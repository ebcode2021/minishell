/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:42:34 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/26 15:34:07 by jinholee         ###   ########.fr       */
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

void	free_split(char **splitted);
void	exit_with_error_msg(const char *msg);
void	*ft_malloc(size_t size);
int		syntax_check(char *input);
void	here_doc(char *eof, char *tmp_filename);
void	here_doc_handler(char *raw_input, char *tmp_filename);
int		here_doc_fork(char *raw_input);
char	*expand_quotes(char *input);

#endif
