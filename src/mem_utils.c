/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 11:57:05 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/09 11:57:28 by jinholee         ###   ########.fr       */
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
