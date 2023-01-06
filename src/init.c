/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 14:44:39 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/06 15:11:18 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_env_lst(char **envp)
{
	t_list	*env;
	size_t	i;

	i = 0;
	g_sys.env_lst = 0;
	while (envp[i])
		ft_lstadd_back(&g_sys.env_lst, ft_lstnew(envp[i++]));
	g_sys.home_dir = g_sys.pwd;
	env = ft_lstfind(g_sys.env_lst, "HOME");
	if (env)
		g_sys.home_dir = ft_strdup(env->value);
	ft_lst_remove_if(&g_sys.env_lst, "OLDPWD");
}

static void	create_tmp_dir(char **envp)
{
	DIR			*dir;
	pid_t		pid;
	char *const	rm_args[4] = {"rm", "-rf", g_sys.tmp_dir, 0};
	char *const	mkdir_args[4] = {"mkdir", "-p", g_sys.tmp_dir, 0};

	dir = opendir(g_sys.tmp_dir);
	if (dir == 0)
	{
		pid = pipe_n_fork(0);
		if (pid == 0)
		{
			execve("/bin/rm", rm_args, envp);
			exit(1);
		}
		waitpid(pid, 0, 0);
		pid = pipe_n_fork(0);
		if (pid == 0)
		{
			execve("/bin/mkdir", mkdir_args, envp);
			exit(1);
		}
		return ;
		waitpid(pid, 0, 0);
	}
	closedir(dir);
}

void	init_system_info(char **envp)
{
	getcwd(g_sys.pwd, BUFFER_SIZE);
	g_sys.tmp_dir = ft_strjoin(TMP_DIRECTORY, ttyname(STDIN_FILENO));
	create_tmp_dir(envp);
	create_env_lst(envp);
	g_sys.last_errno = 0;
	g_sys.last_exit_status_code = 0;
}