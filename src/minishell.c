/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:51:11 by eunson            #+#    #+#             */
/*   Updated: 2022/12/21 18:55:29 by eunson           ###   ########.fr       */
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

//test log

t_system	sys;

void	exit_check(char *input)
{
	char	*trimed;

	if (!input)
		builtin_exit();
	trimed = ft_strtrim(input, " "); 
	if (ft_strncmp("exit", trimed, 5) == 0)
	{
		free(trimed);
		builtin_exit();
	}

	//kill all process;
	// exit_code 직접 세팅..?
	//set_exit_code()
	//exit(exit code?)
}

int	is_redirection(char **input)
{
	char	c;

	if (**input == '<' || **input == '>')
	{
		c == **input;
		*input++;
		if (c == '<' && **input == '<')
			return (IN_REDIECTION);
		else if (c == '>' && **input == '>')
			return (OUT_APPEND);
		else if (c == '<')
			return (1);
		else if (c == '>')
			return (3);
	}
	return (0);
}

void	syntax_check(char *input)
{
	size_t	idx;
	char	*trimed;

	idx = 0;
	trimed = ft_strtrim(input, " ");
	if (input[idx++] == '|')
		error_handler();
	while (input[idx])
	{
		while (input[idx] == ' ')
			input++;
		if (is_redirection(&input))
		{
			if (*input == '|' || *input == '\n')
				printf("syntax error near unexpected token \`%c\'", *input);
		}
		else if (is_pipe(&input))
		{
			
		}
		input++;
	}
	// | 로 바로 시작되는 경우
	// | | 사이에 공백만 들어온경우
	// redirection 기호 이후에 아무인자가 없는 경우.
}

char	**command_parser(char *input) 
{
	size_t	idx;
	char	**pipe_split;

	idx = 0;
	syntax_check(input);
	quote_interpreter(input);
	pipe_split = ft_split(input, '|');
	while (pipe_split[idx])
		event_handler(pipe_split[idx++]);
	return (pipe_split);
}

void	execute(char **commands)
{
	size_t	idx;

	idx = 0;
	// asdf=1
	// command가 맞나? 아님 builtin인가? . export
	// commands = "ls -al", "pwd", "hostname"
	while (commands[idx]) 
	//pipe_n_fork
	//자식(child)
	//command_str 을 공백으로 split
	//? 나 ! 확장
	if (is_command(commands[idx]))
		command_handler(commands[idx]);
	else if(is_builtin(commands[idx]))
		builtin_handler(commands[idx]);
	else 
		error_handler();
}

void	set_system_info(char *envp[])
{
	char	**splitted;

	sys.env_lst = 0;
	while (*envp)
	{
		splitted = ft_split(*envp++, '=');
		ft_lstadd_back(&sys.env_lst, ft_lstnew(splitted[0], splitted[1]));
		free_split(splitted);
	}
	getcwd(sys.pwd, BUFFER_SIZE);
	sys.last_errno = 0;
	sys.last_exit_status_code = 0;
}

int main(int argc, char *argv[], char *envp[])
{
	// char		*input;
	// char		**commands;

	//set_signal_handler();
	argc = 0;
	argv = 0;
	set_system_info(envp);
	return (0);
	// while (1)
	// {
	// 	input = readline("picoshell> ");
	// 	exit_check(input); 
	// 	add_history(input);
	// 	commands = command_parser(input);
	// 	execute(commands);
	// 	printf("아무래도..input : %s\n",input);
	// 	free(input);
	// }
	//return (0);
}
