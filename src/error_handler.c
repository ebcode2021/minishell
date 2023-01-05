/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:56:42 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 20:47:02 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_error_handler(int signo)
{
	if (signo == 131)
	{
		ft_putstr_fd("Quit", STDERR_FILENO);
		ft_putnbr_fd(signo - 128, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	print_custom_error(char *location, char *argument, char *msg)
{
	ft_putstr_fd("picoshell: ", STDERR_FILENO);
	if (location)
		ft_putstr_fd(location, STDERR_FILENO);
	if (argument)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(argument, STDERR_FILENO);
	}
	ft_putendl_fd(msg, STDERR_FILENO);
}

void	print_error(char *location, char *argument)
{
	ft_putstr_fd("picoshell: ", STDERR_FILENO);
	if (!argument)
		perror(location);
	else
	{
		ft_putstr_fd(location, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		perror(argument);
	}
}

void	redirection_error(char *file_name, int child)
{
	if (!file_name)
		print_error(AMBIGUOUS, 0);
	else
	{
		print_error(file_name, 0);
		free(file_name);
	}
	if (child)
	{
		g_sys.last_exit_status_code = 1;
		exit(1);
	}
}

int	syntax_error(char c, char *trimed)
{
	char	str[2];

	if (!c)
		print_custom_error(0, 0, SYNTAX_NEW_LINE);
	else
	{
		str[0] = c;
		str[1] = 0;
		ft_putstr_fd("picoshell: ", STDERR_FILENO);
		ft_putstr_fd(SYNTAX_TOKEN, STDERR_FILENO);
		ft_putstr_fd(str, STDERR_FILENO);
		ft_putendl_fd("\'", STDERR_FILENO);
	}
	free(trimed);
	return (0);
}
