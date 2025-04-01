/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:18:28 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/29 17:49:45 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env_variable(char *value)
{
	if (*value == '\'')
		return (0);
	if (ft_strchr(value, '$') != NULL)
		return (1);
	return (0);
}

void	check_state_after_space(t_tokenizer *state, t_token *last_token)
{
	if (last_token->prev == NULL || (last_token->prev->type == TOKEN_PIPE))
		state->after_operator = 1;
	else if (last_token->prev->type >= TOKEN_REDIRECTION_IN
		&& last_token->prev->type <= TOKEN_REDIRECTION_APPEND)
		state->after_operator = 2;
	else if (last_token->prev->type == TOKEN_HEREDOC)
		state->after_operator = 3;
	else
		state->after_operator = 0;
}

void	check_state(t_tokenizer *state)
{
	t_token	*last_token;

	if (state->tklst == NULL)
		return ;
	last_token = ft_tklast(state->tklst);
	if (last_token->type == TOKEN_SPACE && state->is_first_token == 0)
		check_state_after_space(state, last_token);
	else if (last_token->type == TOKEN_PIPE)
		state->after_operator = 1;
	else if (last_token->type == TOKEN_REDIRECTION_IN
		|| last_token->type == TOKEN_REDIRECTION_OUT
		|| last_token->type == TOKEN_REDIRECTION_APPEND
		|| last_token->type == TOKEN_HEREDOC)
		state->after_operator = 2;
	else
		state->after_operator = 0;
}

t_token_type	check_token_type(char *value, t_tokenizer *state)
{
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strcmp(value, "<") == 0)
		return (TOKEN_REDIRECTION_IN);
	else if (ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIRECTION_OUT);
	else if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIRECTION_APPEND);
	else if (value[0] == '\"')
		return (TOKEN_DOUBLE_Q);
	else if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(value, " ") == 0)
		return (TOKEN_SPACE);
	else if (is_env_variable(value))
		return (TOKEN_ENV_VARI);
	else if (state->is_first_token || state->after_operator == 1)
		return (TOKEN_COMMAND);
	else if (state->after_operator == 2)
		return (TOKEN_FILENAME);
	else
		return (TOKEN_STRING);
}
