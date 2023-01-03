/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:56:42 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/03 14:52:36 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// builtin + redirection-> picoshell : cmd : arg : err-msg (env 조심)
// program -> cmd : arg : 
// redirection -> 
// $? <- sys.last_exit_status_code

// env is hashed (/usr/bin/env)이여서 내장으로 보기도 하지만
// builtin으로 하라 그랬으니까, 기본적인 built_in error 처리대로 해도되지/

// env는 첫번째 argv[1]에서만 오류 출력
// exit는 일단 exit 메세지는 보여주고. 에러 첫번째만 출력하고.
// cd는 첫번째 arg만
// export, unset은 각각의 argv들을 일일이 다 에러처리. 에러로 인식하는 형식이 있음.
// ex) unset 1=a 2=b
// is_alpha , under_bar만 허용 << 첫 글자 규칙 
// is_alnum
// asdfadsf   = 1

void	command_not_found(char *command)
{
	ft_putstr_fd("picoshell: ", STDERR_FILENO);
	ft_putstr_fd(command, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

void	print_error_msg(char *location, char *argument)
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
		print_error_msg(AMBIGUOUS, 0);
	else
	{
		print_error_msg(file_name, 0);
		free(file_name);
	}
	if (child)
	{
		sys.last_exit_status_code = 1;
		//builtin_exit(exec);
	}
}

// void	builtin_error(t_exec_block *exec, int idx, int child)
// {
	

// }




// void	all_arg_error_check(t_exec_block *exec)
// {
// 	size_t	idx;

// 	idx = 1;
// 	while (exec->args[idx]) 
// 	//무조건 에러처리하면 안되고. 조건따져야지. 실행? 아. 이건 내부에서. 여기서 처리할게 아니라.
// 		print_error_msg(exec->command, exec->args[idx++]);
// }

// void	builtin_error(t_exec_block *exec)
// {
// 	// export, unset은 while문 타야됨.
// 	if (!ft_strncmp("unset", exec->command, 6) || !ft_strncmp("export", exec->command, 7))
// 		all_arg_error_check(exec);
// 	else
// 		print_error_msg(exec->command, exec->args[1]);
// }

// exec -> cmd, argv 판단
// category -> built_in, redirection check
// parents, child -> 즉시 exit or 시켜야할지 판단.

// void	error_handler(t_exec_block *exec, int category, int child)
// {
// 	if (category == BUILT_IN)
// 		builtin_error(exec);
// 	else
// 		redirection_error(exec);
// 	if (child)
// 	{
// 		sys.last_exit_status_code = 1;
// 		//builtin_exit(exec);
// 	}
// }