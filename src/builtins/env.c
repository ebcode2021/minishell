/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:02 by eunson            #+#    #+#             */
/*   Updated: 2023/01/01 21:41:41 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char *arg)
{
	size_t	i;

	//split var_name and value. 
	//and the value should be handled with quote_handler.
}

void	*builtin_env(t_exec_block block)
{
	t_list	*elem;
	size_t	i;
	int		fd;

	//set redirections.
	//need to parse args whether they are in 'var_name=value' form.
	//if not, args are treated as files or directories.
	//whether is the file or directory exists or not it always
	//returns an error "No such file or directory"
	//if any errors occur, env does nothing.
	i = 0;
	while (block->args[i])
		add_env(block->args[i++]);
	elem = sys.env_lst;
	while (elem)
	{
		ft_putstr_fd(elem->variable_name, fd);
		ft_putstr_fd("=", fd);
		ft_putendl_fd(elem->value, fd);
		elem = elem->next;
	}
}