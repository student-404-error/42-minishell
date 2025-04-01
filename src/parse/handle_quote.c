#include "minishell.h"

static int	handle_unclosed_quote(char **input, t_tokenizer *state, char quote)
{
	char	*continue_str;
	char	*new_input;

	continue_str = readline(">");
	while (continue_str)
	{
		new_input = ft_strjoin(*input, continue_str);
		free(*input);
		*input = new_input;
		state->idx = ft_strlen(*input) - ft_strlen(continue_str);
		free(continue_str);
		while ((*input)[state->idx] && (*input)[state->idx] != quote)
			state->idx++;
		if ((*input)[state->idx] == quote)
			return (1);
		continue_str = readline(">");
	}
	ft_putstr_fd("Error: Unclosed quote\n", 2);
	return (0);
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
