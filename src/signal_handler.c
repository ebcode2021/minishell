/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:19 by eunson            #+#    #+#             */
/*   Updated: 2023/01/04 16:40:59 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_prompt(int signo)
{
	if (signo != SIGINT)
		return ;
	rl_on_new_line();
	rl_replace_line("", 1);
	//rl_redisplay();
}

void	set_signal_handler(void)
{
	signal(SIGINT, new_prompt); // ctrl + c (new prompt)
	signal(SIGQUIT, SIG_IGN); // ctrl + \ (do nothing..)
}
