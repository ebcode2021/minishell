/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:29:12 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/06 17:21:15 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	free_all(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

static size_t	count_words(char *str, char c)
{
	int	count;
	int	after_sep;

	count = 0;
	after_sep = 1;
	while (*str)
	{
		if (*str == c)
			after_sep = 1;
		else if (after_sep)
		{
			count++;
			after_sep = 0;
		}
		str++;
	}
	return (count);
}

static char	*return_word(char *word, char *str, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (str[i] == c)
		i++;
	while (str[i + len] && str[i + len] != c)
		len++;
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		return (0);
	len = 0;
	while (str[i + len] && str[i + len] != c)
	{
		word[len] = str[i + len];
		len++;
	}
	word[i + len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	const size_t	word_count = count_words((char *)s, c);
	size_t			i;
	char			**words;

	words = malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (words);
	i = 0;
	while (i < word_count)
	{
		if (*s == c)
			s++;
		else
		{
			words[i] = return_word(words[i], (char *)s, c);
			if (!words[i])
			{
				free_all(words);
				return (0);
			}
			s += ft_strlen(words[i++]);
		}
	}
	words[word_count] = 0;
	return (words);
}
