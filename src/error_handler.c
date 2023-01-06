/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:56:42 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/06 19:17:55 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_exit_handler(int exit_code)
{
	exit_code %= 256;
	if (exit_code == SIGQUIT)
	{
		ft_putstr_fd("Quit ", STDERR_FILENO);
		ft_putnbr_fd(exit_code, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (exit_code != 0)
		ft_putchar_fd('\n', STDERR_FILENO);
	if (exit_code)
		exit_code += 128;
	g_sys.last_exit_status_code = exit_code;
	signal(SIGINT, new_prompt);
}

void	print_custom_error(char *location, char *argument, char *msg)
{
	ft_putstr_fd("picoshell: ", STDERR_FILENO);
	if (location)
	{
		ft_putstr_fd(location, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (argument)
	{
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

void	redirection_error(char *file_name, char *location, int child)
{
	if (!file_name)
		print_custom_error(location, 0, AMBIGUOUS);
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
