/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:56:42 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 10:59:10 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_custom_error(char *location, char *argument, char *message)
{
	ft_putstr_fd("picoshell: ", STDERR_FILENO);
	if (location)
		ft_putstr_fd(location, STDERR_FILENO);
	if (argument)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(argument, STDERR_FILENO);
	}
	ft_putendl_fd(message, STDERR_FILENO);
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
		sys.last_exit_status_code = 1;
		//builtin_exit(exec);
	}
}
