/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 10:51:11 by eunson            #+#    #+#             */
/*   Updated: 2023/01/10 11:58:10 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_system	g_sys;

static void	print_main(void)
{
	printf("%s", "\033[36m");
	printf(" ____  __  ___  __   ____  _  _  ____  __    __   \n");
	printf("(  _ \\(  )/ __)/  \\ / ___)/ )( \\(  __)(  )  (  )  \n");
	printf(" ) __/ )(( (__(  O )\\___ \\) __ ( ) _) / (_/\\/ (_/\\ \n");
	printf("(__)  (__)\\___)\\__/ (____/\\_)(_/(____)\\____/\\____/\n\n");
	printf("		      %sㄴr의 작고,,소듕한,,picoshell,,☆\n", "\033[36m");
	printf("\
		\
		%sby %seunson %sand %sjinholee\n",
		"\033[36m", "\033[33m", "\033[036m", "\033[33m");
	printf("\n\n%s", "\033[0m");
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*input;
	t_exec_block	*execs;

	if (!argc && !argv)
		return (0);
	init_system_info(envp);
	print_main();
	while (1)
	{
		input = readline("picoshell> ");
		if (input)
			add_history(input);
		else
			pseudo_sigterm();
		if (syntax_check(input))
		{
			execs = exec_block_parser(input);
			execute_handler(execs);
			free_blocks(execs);
			reset_params();
		}
		free(input);
	}
	return (0);
}
