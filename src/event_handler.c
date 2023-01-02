/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 21:12:43 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/02 11:59:01 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	event_handler(char **commands)
{
	//const char	*reserved_word[3] = {'$', '!', '~'}
	//$?
	here_doc_handler(commands);
	reserved_word_handler(commands); /// $ ! ~
	// 1. here_doc
 
	
}