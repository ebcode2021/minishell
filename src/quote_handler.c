/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/30 21:34:57 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/30 21:35:26 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*double_quote_handler(char *str)
{
	char	*replaced;

	replaced = str_replace(str, "\"", "");
	return (replaced);
}

char	*single_quote_handler(char *str)
{
	return (str_replace(str, "\'", ""));
}

char	*quote_handler(char *str)
{
	char	*result;

	if (*str == '\"')
		result = double_quote_handler(str);
	else if (*str == '\'')
		result = single_quote_handler(str);
	else
		result = str;
	return (result);
}