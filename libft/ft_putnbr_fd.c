/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:48:20 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/05 12:21:55 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	temp[10];
	int		i;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	i = 0;
	while (1)
	{
		temp[i++] = n % 10 + '0';
		n /= 10;
		if (n == 0)
			break ;
	}
	while (i > 0)
	{
		write(fd, &temp[--i], 1);
	}
}
