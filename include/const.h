/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eunson <eunson@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 19:01:59 by jinholee          #+#    #+#             */
/*   Updated: 2023/01/05 13:56:15 by eunson           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONST_H
# define CONST_H

# define BUFFER_SIZE 1024
# define TMP_DIRECTORY "/tmp/picoshell/"

# define INFILE 60
# define OUTFILE 62
# define HERE_DOC 120
# define OUTFILE_A 124

# define READ 0
# define WRITE 1

# define REDIRECTION 0
# define BUILT_IN 1

# define STD_IN 1000
# define STD_OUT 1001

# define PARENTS 0
# define CHILD 1

# define EXPORT 0
# define UNSET 1
# define LONG_MAX 9223372036854775807UL

#endif