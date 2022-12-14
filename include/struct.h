/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:57:26 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/10 15:46:05 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"
# include "const.h"

typedef struct s_system
{
	t_list	*env_lst;
	char	*tmp_dir;
	char	pwd[BUFFER_SIZE];
	char	*home_dir;
	int		last_exit_status_code;
	int		here_doc_index;
	int		signal;
}				t_system;

typedef struct s_redirection
{
	char					*file_name;
	int						type;
	struct s_redirection	*next;
}				t_redirecion;

typedef struct s_exec_block
{
	char				*command;
	char				**args;
	t_redirecion		*redirection;
	size_t				idx;
	struct s_exec_block	*next;
}				t_exec_block;

typedef struct s_pipe
{
	int	prev_fd;
	int	fd[2];
}				t_pipe;

#endif
