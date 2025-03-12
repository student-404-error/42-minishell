/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:52:16 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 20:12:11 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quote_token(t_tokenizer *state, char *input)
{
	char	quote;
	t_token	*token;

	if (input[state->idx] == '\'' || input[state->idx] == '"')
	{
		quote = input[state->idx];
		if (state->idx != state->start)
		{
			token = ft_new_token(ft_substr(input, state->start, state->idx - state->start), state);
			ft_token_add_back(&state->tklst, token);
		}
		state->start = ++state->idx;
		while (input[state->idx] && input[state->idx] != quote)
			state->idx++;
		if (input[state->idx] == quote)
		{
			token = ft_new_token(ft_substr(input, state->start - 1, state->idx - state->start + 2), state);
			ft_token_add_back(&state->tklst, token);
			state->start = ++state->idx;
		}
		else
			exit(1); // 잘 안닫혀있음. 에러 메모리 해제.
		return (1);
	}
	return (0);
}

int	handle_whitespace(t_tokenizer *state, char *input)
{
	if ((input[state->idx] >= 9 && input[state->idx] <= 13)
		|| input[state->idx] == ' ')
	{
		if (state->idx != state->start)
			ft_token_add_back(&state->tklst,
				ft_new_token(ft_substr(input, state->start,
						state->idx - state->start), state));
		while ((input[state->idx] >= 9 && input[state->idx] <= 13)
			|| input[state->idx] == ' ')
			state->idx++;
		ft_token_add_back(&state->tklst, ft_new_token(ft_strdup(" "), state));
		state->start = state->idx;
		return (1);
	}
	return (0);
}

int	handle_env_variable(t_tokenizer *state, char *input)
{
	if (input[state->idx] == '$')
	{
		if (state->idx != state->start)
			ft_token_add_back(&state->tklst,
				ft_new_token(ft_substr(input, state->start,
						state->idx - state->start), state));
		state->start = state->idx;
		state->idx++;
		while (input[state->idx] && !(input[state->idx] == ' '
				|| input[state->idx] == '$' || input[state->idx] == '\''
				|| input[state->idx] == '"' || input[state->idx] == '<'
				|| input[state->idx] == '>' || input[state->idx] == '|'))
			state->idx++;
		ft_token_add_back(&state->tklst,
			ft_new_token(ft_substr(input, state->start,
					state->idx - state->start), state));
		state->start = state->idx;
		return (1);
	}
	return (0);
}

int	handle_special_operators(t_tokenizer *state, char *input)
{
	if (!ft_strncmp(input + state->idx, "<<", 2)
		|| !ft_strncmp(input + state->idx, ">>", 2))
	{
		if (state->idx != state->start)
			ft_token_add_back(&state->tklst,
				ft_new_token(ft_substr(input, state->start,
						state->idx - state->start), state));
		ft_token_add_back(&state->tklst,
			ft_new_token(ft_substr(input, state->idx, 2), state));
		state->idx += 2;
		state->start = state->idx;
		return (1);
	}
	return (0);
}

int	handle_single_char_operators(t_tokenizer *state, char *input)
{
	if (input[state->idx] == '<'
		|| input[state->idx] == '>'
		|| input[state->idx] == '|')
	{
		if (state->idx != state->start)
			ft_token_add_back(&state->tklst,
				ft_new_token(ft_substr(input, state->start,
						state->idx - state->start), state));
		ft_token_add_back(&state->tklst,
			ft_new_token(ft_substr(input, state->idx, 1), state));
		state->idx++;
		state->start = state->idx;
		return (1);
	}
	return (0);
}
