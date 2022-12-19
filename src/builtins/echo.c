/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:32:00 by eunson            #+#    #+#             */
/*   Updated: 2022/12/19 16:15:09 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char *str, int n_option)
{
	if (n_option)
		ft_putstr_fd(str, STDIN_FILENO);
	else
		ft_putendl_fd(str, STDIN_FILENO);
}
