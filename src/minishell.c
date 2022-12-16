/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:51:11 by eunson            #+#    #+#             */
/*   Updated: 2022/12/16 21:47:29 by eunson           ###   ########.fr       */
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

void	syntax_check(char *input)
{
	// | 이후에 공백만 들어온경우
	// redirection이 잘못된 경우
}

void	event_handler(char **commands)
{
	here_doc_handler(commands);
	reserved_word_handler(commands); /// $ ! ~
	// 1. here_doc

	
}

char	**command_parser(char *input)
{
	char	**pipe_split;

	// 1) | 가 이상하지 않은지
	// 2) redirection이 이상하지 않은지.
	syntax_check(input);
	pipe_split = ft_split(input, '|');
	event_handler(pipe_split);
	return (pipe_split);
}

void	execute(char **commands)
{
	// commands = "ls -al", "pwd", "hostname"
	while (*commands) 
	//pipe_n_fork
	//자식(child)
	//command_str 을 공백으로 split
	//? 나 ! 확장
	if(is_builtin(split_commands[0]))
		builtin_handler();
	else
	{
		//find_path
		//execve() 여기서 바로 실행
	}
}

int main(void)
{
	char	*input;
	char	**commands;

	set_signal_handler();
	while (1)
	{
		input = readline("picoshell> ");
		exit_check(input); 
		add_history(input);
		commands = command_parser(input);
		execute(commands);
		printf("아무래도..input : %s\n",input);
		free(input);
	}
	return (0);
}
