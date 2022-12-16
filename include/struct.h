/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:57:26 by jinholee          #+#    #+#             */
/*   Updated: 2022/12/13 19:17:47 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_token
{
	int		type;
	char	*str;                                                  
}				t_token;

//enum insert
enum e_type
{
	// cmd
	// redirection
	// argument
	// quote
	// pipe
}	t_type;

enum e_redirection
{
	here_doc
		
};

typedef struct s_node
{
	t_token			*token;
	struct s_node	*parent;
	struct s_node	*l_child;
	struct s_node	*r_child;
}				t_node;

#endif
