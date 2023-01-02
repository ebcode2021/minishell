/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:31:58 by eunson            #+#    #+#             */
/*   Updated: 2023/01/02 12:11:51 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(char *diretory)
{
	const char	*pwd[2] = {"PWD", 0};
	const char	*new_pwd[2] = {diretory, 0};

	builtin_unset(pwd);
	builtin_export(new_pwd);
}

void	assert_cd(char *directory)
{
	DIR		*dir;

	dir = opendir(directory);
	if (!dir)
		error_handler();
	//closedir()
}

void	builtin_cd(char **directories)
{
	char	*pwd;
	size_t	idx;

	pwd = directories[0];
	assert_cd(pwd);
	update_pwd(pwd)
}
