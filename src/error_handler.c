/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:56:42 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/02 21:51:04 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// builtin + redirection-> picoshell : cmd : arg : err-msg (env 조심)
// program -> cmd : arg : 
// redirection -> 
// $? <- sys.last_exit_status_code

void	builtin_error()
{
	
}

void	redirection_error()
{
	
}

void	error_handler(int category, char *cmd, char *argv)
{
	ft_putstr_fd("picoshell: ", STDERR_FILENO);
	if (category == BUILT_IN)
		builtin_error(cmd, argv);
	else
		redirection_error(cmd, argv);
	
		ft_putstr_fd("picoshell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	
	perror(argv);
	
	//command_na,e	
	//fprintf(stderr,"여기서 에러 처리를 어떻게 하는게 좋을까여");
}
