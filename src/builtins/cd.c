/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:31:58 by eunson            #+#    #+#             */
/*   Updated: 2023/01/05 13:14:00 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(void)
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

void	change_dir(char *dest, t_exec_block *exec)
{
	if (!dest)
		print_custom_error(exec->command, 0, HOME_NOT_SET);
	else if (chdir(dest) == -1)
		print_error(exec->command, exec->args[1]);
	else
	{
		update_oldpwd();
		getcwd(g_sys.pwd, BUFFER_SIZE);
	}
}

void	hyphen_handler(t_exec_block *exec)
{
	char	*oldpwd;

	oldpwd = get_env("$OLDPWD", 0);
	if (oldpwd)
	{
		change_dir(oldpwd, exec);
		ft_putendl_fd(g_sys.pwd, STDIN_FILENO);
	}
	else
		print_custom_error(exec->command, 0, OLDPWD_NOT_SET);
}

void	builtin_cd(t_exec_block *exec)
{
	size_t	arg_cnt;

	arg_cnt = 0;
	while (exec->args[arg_cnt])
		arg_cnt++;
	if (arg_cnt > 2)
		print_custom_error(exec->command, 0, TOO_MANY_ARG);
	else if (arg_cnt == 2)
	{
		if (ft_strncmp(exec->args[1], "-", 2) == 0)
			hyphen_handler(exec);
		else
			change_dir(exec->args[1], exec);
	}
	else
		change_dir(get_env("$HOME", 0), exec);
}
