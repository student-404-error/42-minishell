/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:07:50 by seong-ki          #+#    #+#             */
/*   Updated: 2025/04/11 12:12:21 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	state_init(t_tokenizer *state)
{
	state->idx = 0;
	state->start = 0;
	state->is_first_token = 1;
	state->after_operator = 0;
	state->tklst = NULL;
}

void	handle_tokens(t_tokenizer *state, char **input)
{
	while ((*input)[state->idx])
	{
		check_state(state);
		if (handle_whitespace(state, *input))
			continue ;
		if (handle_env_variable(state, *input))
			continue ;
		if (handle_quote_token(state, input))
			continue ;
		if (handle_special_operators(state, *input))
			continue ;
		if (handle_single_char_operators(state, *input))
			continue ;
		state->idx++;
	}
}

t_token	*tokenize(t_data *data, char **input)
{
	t_tokenizer	state;

	state_init(&state);
	handle_tokens(&state, input);
	if (state.idx != state.start)
		ft_token_add_back(&state.tklst,
			ft_new_token(ft_substr(*input, state.start,
					state.idx - state.start),
				&state));
	remove_quote(&state.tklst);
	expand_env_vari(data, &state.tklst);
	concat_token(&state.tklst);
	remove_space_token(&state.tklst);
	search_cmd(&state.tklst);
	if (syntax_error(state.tklst) == -1)
		return (ft_free_token_list(state.tklst), NULL);
	return (state.tklst);
}
