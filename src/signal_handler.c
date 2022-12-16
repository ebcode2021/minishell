/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:19 by eunson            #+#    #+#             */
/*   Updated: 2022/12/16 17:57:42 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_handler(void)
{
	// 지금 진행중인 process kill?? new_life
	// tgoto? nono
}

static void	sigquit_handler(void)
{
	return ;
}

void	set_signal_handler(void)
{
	signal(SIGINT, sigint_handler); // ctrl + c (new prompt)
	signal(SIGQUIT, sigquit_handler); // ctrl + \ (do nothing..)
}