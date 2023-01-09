/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:51:11 by eunson            #+#    #+#             */
/*   Updated: 2023/01/09 12:00:58 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_system	g_sys;

int	main(int argc, char *argv[], char *envp[])
{
	char			*input;
	t_exec_block	*execs;

	if (!argc && !argv)
		return (0);
	set_signal_handler();
	init_system_info(envp);
	while (1)
	{
		input = readline("picoshell> ");
		if (input)
			add_history(input);
		else
			pseudo_sigterm();
		if (syntax_check(input))
		{
			execs = exec_block_parser(input);
			execute_handler(execs);
			free_blocks(execs);
			reset_fd();
		}
		free(input);
	}
	return (0);
}
