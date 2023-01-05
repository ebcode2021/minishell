/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:47:39 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 10:58:44 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **splitted)
{
	size_t	idx;

	idx = 0;
	while (splitted[idx])
		free(splitted[idx++]);
	free(splitted);
}

void	*ft_malloc(size_t size)
{
	void	*mem;

	mem = ft_calloc(1, size);
	if (!mem)
	{
		print_custom_error(0, 0, MALLOC_FAIL);
		exit(EXIT_FAILURE);
	}
	return (mem);
}
