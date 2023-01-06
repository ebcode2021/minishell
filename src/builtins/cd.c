/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:31:58 by eunson            #+#    #+#             */
/*   Updated: 2023/01/06 15:41:32 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(void)
{
	t_list	*oldpwd;

	oldpwd = ft_lstfind(g_sys.env_lst, "OLDPWD");
	if (!oldpwd)
		ft_lstadd_back(&g_sys.env_lst, ft_lstnew(g_sys.pwd));
	else
	{
		if (oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = ft_strdup(g_sys.pwd);
	}
}

static int	change_dir(char *dest, t_exec_block *exec)
{
	int	success;

	success = 0;
	if (!dest)
		print_custom_error(exec->command, 0, HOME_NOT_SET);
	else if (chdir(dest) == -1)
		print_error(exec->command, exec->args[1]);
	else
	{
		success = 1;
		update_oldpwd();
		getcwd(g_sys.pwd, BUFFER_SIZE);
	}
	return (success);
}

static int	is_oldpwd(t_exec_block *exec)
{
	char	*oldpwd;
	int		oldpwd_cnt;

	oldpwd = get_env("$OLDPWD", 0);
	oldpwd_cnt = 0;
	if (oldpwd)
	{
		oldpwd_cnt = change_dir(oldpwd, exec);
		ft_putendl_fd(g_sys.pwd, STDIN_FILENO);
	}
	else
		print_custom_error(exec->command, 0, OLDPWD_NOT_SET);
	return (oldpwd_cnt);
}

int	builtin_cd(t_exec_block *exec)
{
	int		exit_status;
	size_t	arg_cnt;

	arg_cnt = 0;
	exit_status = 0;
	while (exec->args[arg_cnt])
		arg_cnt++;
	if (arg_cnt > 2)
	{
		exit_status = 1;
		print_custom_error(exec->command, 0, TOO_MANY_ARG);
	}
	else if (arg_cnt == 2)
	{
		if (ft_strncmp(exec->args[1], "-", 2) == 0 && !is_oldpwd(exec))
			exit_status = 1;
		else
			exit_status = change_dir(exec->args[1], exec);
	}
	else
		exit_status = change_dir(get_env("$HOME", 0), exec);
	return (exit_status);
}
