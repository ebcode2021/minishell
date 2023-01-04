/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:19 by eunson            #+#    #+#             */
/*   Updated: 2023/01/04 21:26:34 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_prompt(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	pseudo_SIGTERM(void)
{
	ft_putstr_fd("exit", STDIN_FILENO);
	//ft_putendl_fd("exit", STDOUT_FILENO);
	//rl_redisplay();
	//rl_replace_line("exit\n", STDOUT_FILENO);
	exit(0);
}

void	set_signal_handler(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
	signal(SIGINT, new_prompt); // ctrl + c (new prompt)
	signal(SIGQUIT, SIG_IGN); // ctrl + \ (do nothing..)
}
