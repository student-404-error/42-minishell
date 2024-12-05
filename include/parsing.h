/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:33:08 by seong-ki          #+#    #+#             */
/*   Updated: 2024/10/24 15:39:13 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "builtin.h"

typedef enum {
	TOKEN_STRING,
	TOKEN_OPTION,
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
	struct s_token	*prev;
}	t_token;


t_token	*ft_new_token(char *value);
t_token	*ft_tklast(t_token *tklst);
void	ft_token_add_back(t_token **tklst, t_token *new);
void	change_env_vari(t_data *data, t_token **tklst);
int		count_special_character(t_data *data, char *input);

#endif // !PARSING.15:33:20
