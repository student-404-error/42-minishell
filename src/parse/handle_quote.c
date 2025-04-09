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

char *ft_add_new_line(char *str)
{
	char *new_str;

	if (str == NULL)
		return (NULL);
	new_str = ft_strjoin("\n", str);
	free(str);
	return (new_str);
}

static void add_token(t_tokenizer *state, char *input)
{
	t_token *token;

	token = ft_new_token(ft_substr(input, state->start - 1,
								   state->idx - state->start + 2),
						 state);
	ft_token_add_back(&state->tklst, token);
	state->start = ++state->idx;
}

static int handle_unclosed_quote(char **input, t_tokenizer *state, char quote)
{
	char *continue_str;
	char *new_input;
	char *temp;

	continue_str = readline(">");
	while (continue_str)
	{
		temp = continue_str;
		continue_str = ft_add_new_line(continue_str);
		if (!continue_str)
		{
			free(temp);
			return (0);
		}
		new_input = ft_strjoin(*input, continue_str);
		free(*input);
<<<<<<< HEAD
		*input = new_input;
		printf("%ld\n", ft_strlen(*input));
		state->idx = ft_strlen(*input) - ft_strlen(continue_str);
=======
>>>>>>> 958c61ab27b5f314a603a98c488db9ad64041418
		free(continue_str);
		if (!new_input)
			return (0);
		*input = new_input;
		state->idx = ft_strlen(*input) - ft_strlen(temp);
		while ((*input)[state->idx] && (*input)[state->idx] != quote)
			state->idx++;
		if ((*input)[state->idx] == quote)
			return (add_token(state, *input), 1);
		continue_str = readline(">");
	}
	ft_putstr_fd("Error: Unclosed quote\n", 2);
	free(*input);  // 추가: 실패 시 input 해제
	*input = NULL; // 추가: input 포인터를 NULL로 설정
	return (0);
}

int handle_quote_token(t_tokenizer *state, char **input)
{
	char quote;

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
	{
		add_token(state, *input);
		return (1);
	}
	else if (!handle_unclosed_quote(input, state, quote))
		return (0);
	return (1);
}
