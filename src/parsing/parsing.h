/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:51:12 by seong-ki          #+#    #+#             */
/*   Updated: 2024/09/17 16:52:42 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdlib.h>

typedef enum {
	TOKEN_COMMAND,
	TOKEN_OPTION,
	TOKEN_ARGUMENT,
	TOKEN_VARIABLE,
	TOKEN_OPERATOR,
	TOKEN_REDIRECTION,
	TOKEN_PIPE,
	TOKEN_HEREDOC,
}	e_token_type;

typedef struct s_token {
	e_token_type	type;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_tokenlist
{
	t_token	*tokens;
	size_t	size;
} t_tokenlist;

#endif // !PARSING_H
