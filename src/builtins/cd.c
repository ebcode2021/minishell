/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:31:58 by eunson            #+#    #+#             */
/*   Updated: 2023/01/03 16:20:13 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_dir(char *dest)
{
	if (!dest)
	{
		fprintf(stderr, "picoshell: cd: HOME not set\n");
		return (-1);
	}
	else if (chdir(dest) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		perror(dest);
		return (-1);
	}
	getcwd(sys.pwd, BUFFER_SIZE);
	return (0);
}

int	hyphen_handler()
{
	char	*OLDPWD;

	OLDPWD = get_env("$OLDPWD", 0);
	if (!OLDPWD)
	{
		fprintf(stderr, "picoshell: cd: OLDPWD not set\n");
		return (-1);
	}
	change_dir(OLDPWD);
	printf("%s\n", sys.pwd);
	return (0);
}

void	builtin_cd(t_exec_block *block)
{
	size_t	number_of_args;

	//set redirections
	number_of_args = 0;
	while (block->args[number_of_args])
		number_of_args++;
	if (number_of_args > 2)
		fprintf(stderr, "picoshell: cd: too many argument\n");
	else if (number_of_args == 1)
		change_dir(get_env("$HOME", 0));
	else if (number_of_args == 2)
	{
		if (ft_strncmp(block->args[1], "-", 2) == 0)
			hyphen_handler();
		else
			change_dir(block->args[1]);
	}
}
