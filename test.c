#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>

void	syntax_check(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] == ' ')
		i++;
	if (input[i] == '|')
		printf("bash: syntax error near unexpected token `|\'\n");
	while (input[i])
	{	
		if (input[i] == '<' || input[i] == '>')
		{
			i++;
			if (input[i-1] == '<' && input[i] == '<')
				printf("do some here_doc\n");
			if (input[i] == '<' || input[i] == '>')
				i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|')
			{
				printf("bash: syntax error near unexpected token `|\'\n");
				break ;
			}
			else if (input[i] == 0)
			{
				printf("bash: syntax error near unexpected token `newline\'\n");
				break ;
			}
			else if (input[i] == '<' || input[i] == '>')
			{
				printf("bash: syntax error near unexpected token `%c'\n", input[i]);
				break ;
			}
		}
		if (input[i] == '|')
		{
			i++;
			while (input[i] == ' ')
				i++;
			if (input[i] == '|')
			{
				printf("bash: syntax error near unexpected token `|\'\n");
				break ;
			}
		}
		i++;
	}
}

void	parse_input(char *input)
{
	syntax_check(input);
}

int	main(int argc, char **argv)
{
	char *input;

	while (1)
	{
		input = readline("picoshell> ");
		add_history(input);
		printf("input : %s\n",input);
		parse_input(input);
		free(input);
	}
	return (0);
}

/* [ list1, list2 list3]
list1 -> cat -> "'" -> $abc -> "'"
lsit2 -> cat -> "$abc"
list3 -> < -> tmp_file_name
list4 -> export -> a=b */

/* int	is_redirection(char *input, size_t *i)
{
	if (input[*i] == '<')
	{
		*i += 1;
		if (input[*i] == '<')
		{
			*i += 1;
			return (2);
		}
		return (1);
	}
	else if (input[*i] == '>')
	{
		*i += 1;
		if (input[*i] == '>')
		{
			*i += 1;
			return (4);
		}
		return (3);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	size_t	i;
	char	*input = ft_strtrim(argv[1], " ");

	i = 0;
	printf("trimed = \"%s\"\n", input);
	input = ft_strjoin(ft_strtrim(argv[1], " "), "\n");
	while (input[i])
	{
		printf("%zu\n", i);
		if (is_redirection(input, &i))
		{
			printf("%zu\n", i);
			while (input[i] == ' ')
				i++;
			if (input[i] == '|')
			{
				printf("syntax error unexpected token near `|\'\n");
				exit(1);
			}
			else if (input[i] == '\n')
			{
				printf("syntax error unexpected token near \'newline\'\n");
				exit(1);
			}
		}
		i++;
	}
	printf("input = \"%s\"\n", input);
	return (0)
}
 */