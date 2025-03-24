/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:07:50 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/24 14:55:02 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens(t_token *tklst)
{
	t_token	*list_ptr;

	if (!tklst)
		return ;
	list_ptr = tklst;
	printf("\n\n===========RESULT===========\n");
	while (list_ptr)
	{
		printf("lexing: token: %s | type: %d\n", list_ptr->value, list_ptr->type);
		list_ptr = list_ptr->next;
	}
	printf("\n\n");
	return ;
}

void	state_init(t_tokenizer *state)
{
	state->idx = 0;
	state->start = 0;
	state->is_first_token = 1;
	state->after_operator = 0;
	state->tklst = NULL;
}

t_token	*tokenize(t_data *data, char *input)
{
	t_tokenizer	state;

	state_init(&state);
	while (input[state.idx])
	{
		check_state(&state);
		if (handle_whitespace(&state, input))
			continue ;
		if (handle_env_variable(&state, input))
			continue ;
		if (handle_quote_token(&state, input))
			continue ;
		if (handle_special_operators(&state, input))
			continue ;
		if (handle_single_char_operators(&state, input))
			continue ;
		state.idx++;
	}
	if (state.idx != state.start)
		ft_token_add_back(&state.tklst,
			ft_new_token(ft_substr(input, state.start,
					state.idx - state.start), &state));
	remove_quote(&state.tklst);
	expand_env_vari(data, &state.tklst);
	concat_token(&state.tklst);
	remove_space_token(&state.tklst);
	change_env_to_cmd(&state.tklst);
	return (state.tklst);
}
