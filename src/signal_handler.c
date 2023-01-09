/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:19 by eunson            #+#    #+#             */
/*   Updated: 2023/01/09 21:49:02 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	pseudo_sigterm(void)
{
	clean_up();
	ft_putstr_fd("\033[1A", STDOUT_FILENO);
	ft_putstr_fd("\033[11C", STDOUT_FILENO);
	ft_putendl_fd("exit", STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}

void	signal_interrupt(int signo)
{
	if (signo != SIGINT)
		return ;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 1);
	exit(EXIT_INTERRUPT);
}

void	signal_quit(int signo)
{
	if (signo != SIGQUIT)
		return ;
	ft_putstr_fd("Quit: ", STDOUT_FILENO);
	ft_putnbr_fd(signo, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	exit(EXIT_QUIT);
}

void	set_signal_handler(void)
{
	extern int	rl_catch_signals;

	rl_catch_signals = 0;
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}
