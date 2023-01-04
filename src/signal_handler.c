/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:19 by eunson            #+#    #+#             */
/*   Updated: 2023/01/04 22:16:03 by jinholee         ###   ########.fr       */
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
	ft_putstr_fd("\033[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[11C", STDOUT_FILENO);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(0);
}

void	set_signal_handler(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
	signal(SIGINT, new_prompt); // ctrl + c (new prompt)
	signal(SIGQUIT, SIG_IGN); // ctrl + \ (do nothing..)
}
