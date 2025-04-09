/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:11:40 by seong-ki          #+#    #+#             */
/*   Updated: 2025/04/01 18:11:41 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_new_line(char *str)
{
	char	*new_str;

	if (str == NULL)
		return (NULL);
	new_str = ft_strjoin("\n", str);
	free(str);
	return (new_str);
}

static void	add_token(t_tokenizer *state, char *input)
{
	t_token	*token;

	token = ft_new_token(ft_substr(input, state->start - 1,
				state->idx - state->start + 2),
			state);
	ft_token_add_back(&state->tklst, token);
	state->start = ++state->idx;
}

static int	handle_unclosed_quote(char **input, t_tokenizer *state, char quote)
{
	char	*continue_str;
	char	*new_input;

	continue_str = readline(">");
	while (continue_str)
	{
		continue_str = ft_add_new_line(continue_str);
		new_input = ft_strjoin(*input, continue_str);
		free(*input);
		*input = new_input;
		printf("%ld\n", ft_strlen(*input));
		state->idx = ft_strlen(*input) - ft_strlen(continue_str);
		free(continue_str);
		while ((*input)[state->idx] && (*input)[state->idx] != quote)
			state->idx++;
		if ((*input)[state->idx] == quote)
			return (add_token(state, *input), 1);
		continue_str = readline(">");
	}
	ft_putstr_fd("Error: Unclosed quote\n", 2);
	return (0);
}

int	handle_quote_token(t_tokenizer *state, char **input)
{
	char	quote;

	if ((*input)[state->idx] != '\'' && (*input)[state->idx] != '"')
		return (0);
	quote = (*input)[state->idx];
	if (state->idx != state->start)
		ft_token_add_back(&state->tklst,
			ft_new_token(ft_substr(*input, state->start,
					state->idx - state->start),
				state));
	state->start = ++state->idx;
	while ((*input)[state->idx] && (*input)[state->idx] != quote)
		state->idx++;
	if ((*input)[state->idx] == quote)
		add_token(state, *input);
	else if (!handle_unclosed_quote(input, state, quote))
		return (0);
	return (1);
}
