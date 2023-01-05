int	syntax_error()
{

}

void	skip_blank(char *str, int *idx)
{
	while(str[*idx] == ' ')
		idx++;
}

int syntax_check(char *input)
{
	int	idx;
	const char *trimed = ft_strtrim(input, " ");

	if (*trimed == '|')
		return (syntax_error);
	idx = 0;
	while (trimed[idx])
	{
		if (trimed[idx] == '<' || trimed[idx] == '>')
		{
			if (ft_strncmp(trimed + idx, "<<", 2) == 0 || ft_strncmp(trimed + idx, ">>", 2) == 0)
				idx++;
			else if (ft_strncmp(trimed + idx, "<<<", 3) == 0 || ft_strncmp(trimed + idx, "<<<", 3) == 0)
				return (syntax_error);
			skip_blank(trimed, &idx);
			if (!trimed[idx] || trimed[idx] == '|' || trimed[idx] == '<' || trimed[idx] == '>')
				return (syntax_error); 
		}
		else if (trimed[idx] == '|')
		{
			skip_blank(trimed, &idx);
			if (trimed[idx] == '|')
				return (syntax_error);
		}
		idx++;
	}
	free(trimed);
	return (1);
}

int	syntax_check(char *input)
{
	int			idx;
	const char	*trimed = ft_strtrim(input, " ");
​
	if (*trimed == '|')
		return (syntax_error('|', (char *)trimed));
	idx = -1;
	while (trimed[++idx])
	{
		if (trimed[idx] == '<' || trimed[idx] == '>')
		{
			if (ft_strncmp(trimed + idx, "<<", 2) == 0 \
				|| ft_strncmp(trimed + idx, ">>", 2) == 0)
				idx++;
			else if (ft_strncmp(trimed + idx, "<<<", 3) == 0 \
				|| ft_strncmp(trimed + idx, ">>>", 3) == 0)
				return (syntax_error(trimed[idx], (char *)trimed));
			while (trimed[++idx] == ' ')
				continue ;
			if (!trimed[idx])
				return (syntax_error('\n', (char *)trimed));
			else if (trimed[idx] == '|' || trimed[idx] == '<' || trimed[idx] == '>')
				return (syntax_error(trimed[idx], (char *)trimed));
		}
		else if (trimed[idx] == '|')
		{
			while (trimed[++idx] == ' ')
				continue ;
			if (trimed[idx] == '|')
				return (syntax_error(trimed[idx], (char *)trimed));
		}
	}
	return (is_syntax((char *)trimed));
}
