/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:33:08 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 21:23:49 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

typedef struct	s_tokenizer {
	int	idx;
	int	start;
	int	is_first_token;
	int	after_operator;
	t_token	*tklst;
} t_tokenizer;

void	ft_print_tokens(t_token *tklst);
t_token	*ft_new_token(char *value, t_tokenizer *state);
t_token	*ft_tklast(t_token *tklst);
void	ft_token_add_back(t_token **tklst, t_token *new);
void	expand_env_vari(t_data *data, t_token **tklst);
t_token	*tokenize(t_data *data, char *input);

#endif // !PARSING.15:33:20
