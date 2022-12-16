/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:47:39 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/12 14:56:57 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_error_msg(const char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	exit(1);
}

void	*ft_malloc(size_t size)
{
	void	*mem;

	mem = ft_calloc(1, size);
	if (!mem)
		exit_with_error_msg("malloc failure");
	return (mem);
}
