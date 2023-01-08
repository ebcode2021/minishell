/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:31:58 by eunson            #+#    #+#             */
/*   Updated: 2023/01/08 19:54:41 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_oldpwd(void)
{
	t_list	*oldpwd;
	char	*str_oldpwd;

	oldpwd = ft_lstfind(g_sys.env_lst, "OLDPWD");
	if (!oldpwd)
	{
		str_oldpwd = ft_strjoin("OLDPWD=", g_sys.pwd);
		ft_lstadd_back(&g_sys.env_lst, ft_lstnew(str_oldpwd));
		free(str_oldpwd);
	}
	else
	{
		if (oldpwd->value)
			free(oldpwd->value);
		oldpwd->value = ft_strdup(g_sys.pwd);
	}
}

static int	change_dir(char *dest, t_exec_block *exec)
{
	int	exit_status;

	exit_status = 1;
	if (!dest)
		print_custom_error(exec->command, 0, HOME_NOT_SET);
	else if (chdir(dest) == -1)
		print_error(exec->command, exec->args[1]);
	else
	{
		exit_status = 0;
		update_oldpwd();
		getcwd(g_sys.pwd, BUFFER_SIZE);
	}
	return (exit_status);
}

static int	hypen_handler(t_exec_block *exec)
{
	int		exit_status;
	char	*oldpwd;

	oldpwd = get_env("$OLDPWD", 0);
	exit_status = 0;
	if (oldpwd)
	{
		exit_status = change_dir(oldpwd, exec);
		ft_putendl_fd(g_sys.pwd, STDIN_FILENO);
	}
	else
		print_custom_error(exec->command, 0, OLDPWD_NOT_SET);
	return (exit_status);
}

int	builtin_cd(t_exec_block *exec)
{
	int		exit_status;
	size_t	arg_cnt;

	arg_cnt = 0;
	exit_status = 1;
	while (exec->args[arg_cnt])
		arg_cnt++;
	if (arg_cnt > 2)
		print_custom_error(exec->command, 0, TOO_MANY_ARG);
	else if (arg_cnt == 2)
	{
		if (ft_strncmp(exec->args[1], "-", 2) == 0)
		{
			if (!hypen_handler(exec))
				exit_status = 0;
		}
		else
			exit_status = change_dir(exec->args[1], exec);
	}
	else
		exit_status = change_dir(get_env("$HOME", 0), exec);
	return (exit_status);
}
