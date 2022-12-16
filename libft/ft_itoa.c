/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:47:18 by jinholee          #+#    #+#             */
/*   Updated: 2022/07/06 16:45:12 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_nbrlen(long long nbr)
{
	int	i;

	i = 0;
	if (nbr <= 0)
		i++;
	while (nbr)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	const int	n_len = get_nbrlen(n);
	char		*res;
	int			i;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	res = malloc(sizeof(char) * (n_len + 1));
	if (!res)
		return (res);
	if (n < 0)
	{
		n *= -1;
		res[0] = '-';
	}
	if (n == 0)
		res[0] = '0';
	i = n_len;
	while (n)
	{
		res[--i] = n % 10 + '0';
		n /= 10;
	}
	res[n_len] = '\0';
	return (res);
}
