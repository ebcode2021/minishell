/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:51:11 by eunson            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/01/04 16:41:46 by jinholee         ###   ########.fr       */
=======
/*   Updated: 2023/01/04 19:35:50 by jinholee         ###   ########.fr       */
>>>>>>> f59e7c6388d7dc5c80650f7de5d438054b5fe370
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 1. 파이프를 구분자로 split
// 2. 앞뒤로 공백붙은거 제거 - 여기서 빈 문자열 나오면 syntax error
// 3. 각 스트링에 here_doc 있으면 임시파일 생성하고 << 를 < tmp로 치환 - 여기서 redirection뒤에 뭐 없으면 syntax error
// 4. 여기서 생성된 각 스트링마다 fork로 프로세스 생성하고 스트링을 인자로 넘겨줌
// 5. 공백기준(32)로 나눠
// 6. $랑 느낌표 확장.(/는 execve에 고대로 넣으면 ㄴㄴ)
// 7. redirection 기호로 파이프 세팅. ex < tmp가 있으면 dup2(pipe[read] ,tmp_fd);
// 8. -l -e 같은 나머지 옵션들은 char * 배열로 잘 정리
// 9. builtin 명령어인지 아닌지 구분해서 각 함수로 처리하던지 execve로 처리하던지
// 00. signal 처리

//to do list
//1. cmd_not_found 처리. 자식프로세스와 부모 프로세스일때 구분해서 처리할것.
//2. built_in 구현. 역시 에러처리는 1번과 같이
//3. signal 공부해서 어떻게 처리할지

t_system	sys;

void	init_system_info()
{
	sys.env_lst = 0;
	sys.last_exit_status_code = 0;
	sys.last_errno = 0;
	sys.here_doc_names = 0;
	sys.here_doc_index = 0;
	sys.current_fd[READ] = dup2(STD_IN, STDIN_FILENO);
	sys.current_fd[WRITE] = dup2(STD_OUT, STDOUT_FILENO);
}

void	set_tmp_dir(char **envp)
{
	DIR			*dir;
	pid_t		pid;
	char *const rm_args[4] = {"rm", "-rf", sys.tmp_dir, 0};
	char *const mkdir_args[4] = {"mkdir", "-p", sys.tmp_dir, 0};

	dir = opendir(sys.tmp_dir);
	if (dir == 0)
	{
		pid = fork();
		if (pid == 0)
		{
			execve("/bin/rm", rm_args, envp);
			exit(1);
		}
		waitpid(pid, 0, 0);
		pid = fork();
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

void	clean_up(void)
{
	pid_t		pid;
	char		**envp;
	char *const rm_args[4] = {"rm", "-rf", sys.tmp_dir, 0};

	pid = fork();
	if (pid == 0)
	{
		envp = current_env_lst();
		execve("/bin/rm", rm_args, envp);
		exit(1);
	}
	waitpid(pid, 0, 0);
}


void	set_system_info(char *envp[])
{
	t_list	*env;

	getcwd(sys.pwd, BUFFER_SIZE);
	sys.tmp_dir = ft_strjoin(TMP_DIRECTORY, ttyname(STDIN_FILENO));
	set_tmp_dir(envp);
	sys.env_lst = 0;
	while (*envp)
		ft_lstadd_back(&sys.env_lst, ft_lstnew(*envp++));
	sys.home_dir = sys.pwd;
	env = ft_lstfind(sys.env_lst, "HOME");
	if (env)
		sys.home_dir = env->value;
	env = ft_lstfind(sys.env_lst, "OLDPWD");
	free(env->value);
	env->value = 0;
	sys.last_errno = 0;
	sys.last_exit_status_code = 0;
}

int main(int argc, char *argv[], char *envp[])
{
	char			*input;
	t_exec_block	*elem;

	if (!argc && !argv)
		return (0);
	//set_signal_handler();
	set_system_info(envp);
	while (1)
	{
		input = readline("picoshell> ");
		if (input)
			add_history(input);
		if (!input)
			input = ft_strdup("exit");
		if (syntax_check(input))
		{
			elem = exec_block_parser(input);
			execute_handler(elem);
			free_block(elem);
			reset_fd();
		}
		//system("leaks minishell");
		free(input);
	}
	return (0);
}
