/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:57:26 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/27 16:52:25 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"
# include "const.h"

typedef struct s_system
{
	t_list	*env_lst;
	t_list	*here_doc_names;
	char	pwd[BUFFER_SIZE];
	int		last_exit_status_code;
	int		last_errno;
	int		here_doc_index;
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
	struct s_exec_block *next;
}				t_exec_block;

#endif
