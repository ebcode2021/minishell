/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 17:19:10 by eunson            #+#    #+#             */
/*   Updated: 2023/01/10 12:14:21 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define AMBIGUOUS ": ambiguous redirect"
# define COMMAND_NOT_FOUND ": command not found"
# define FORK_ERR ": fork error"
# define HOME_NOT_SET ": HOME not set"
# define IS_DIR ": is a directory"
# define MALLOC_FAIL ": malloc failure"
# define NO_SUCH_FILE_DIR ": No such file or directory"
# define NOT_A_VALID ": not a valid identifier"
# define NOT_A_DIR ": not a directory"
# define NUMERIC_ARG ": numeric argument required"
# define OLDPWD_NOT_SET ": OLDPWD not set"
# define QUOTE_MATCH ": unclosed quotes"
# define SYNTAX_NEW_LINE ": syntax error near unexpected token `newline\'"
# define SYNTAX_TOKEN  ": syntax error near unexpected token `"
# define TOO_MANY_ARG ": too many arguments"
# define TOO_MANY_PIPE ": picoshell only support less than 100 pipes"

#endif