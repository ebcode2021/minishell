/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:02 by eunson            #+#    #+#             */
/*   Updated: 2023/01/04 12:05:27 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char *arg)
{
	size_t	i;

	//split var_name and value. 
	//and the value should be handled with quote_handler.
}

void	*builtin_env(t_exec_block exec)
{
	size_t	idx;
	t_list	*head;

	idx = 1;
	while (exec->args[idx])
		add_env(block->args[idx++]);
	head = sys.env_lst;
	while (head)
	{
		ft_putendl_fd(head->copy, );
		ft_putstr_fd(elem->variable_name, fd);
		ft_putstr_fd("=", fd);
	å	ft_putendl_fd(elem->value, fd);
		head = head->next;
	}
}
	//need to parse args whether they are in 'var_name=value' form.
	//if not, args are treated as files or directories.
	//whether is the file or directory exists or not it always
	//returns an error "No such file or directory"
	//if any errors occur, env does nothing.