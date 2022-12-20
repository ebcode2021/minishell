/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:57:26 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/20 20:03:43 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "libft.h"
# include "const.h"

typedef struct s_token
{
	int		type;
	char	*str;
}				t_token;

typedef struct s_system
{
	t_list	*env_lst;
	char	pwd[BUFFER_SIZE];
	int		last_exit_status_code;
	int		last_errno;
}				t_system;

#endif
