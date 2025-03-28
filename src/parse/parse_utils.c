/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:13:22 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/29 17:34:47 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_token(t_token **tklst)
{
	t_token	*now_token;
	t_token	*prev_token;
	char	*new_str;

	now_token = (*tklst)->next;
	if (now_token != NULL)
		prev_token = now_token->prev;
	else
		prev_token = NULL;
	while (now_token)
	{
		if (prev_token && prev_token->type < 4 && now_token->type < 4)
		{
			new_str = ft_strjoin(prev_token->value, now_token->value);
			if (prev_token->prev == NULL)
			{
				*tklst = now_token;
				now_token->prev = NULL;
			}
			else
			{
				prev_token->prev->next = now_token;
				now_token->prev = prev_token->prev;
			}
			free(prev_token->value);
			now_token->type = prev_token->type;
			free(prev_token);
			free(now_token->value);
			now_token->value = new_str;
		}
		prev_token = now_token;
		now_token = now_token->next;
	}
}

void	remove_quote(t_token **tklst)
{
	t_token	*inst_lst;
	char	*new_value;

	inst_lst = *tklst;
	while (inst_lst)
	{
		if (inst_lst->type < 4)
		{
			if (inst_lst->value[0] == '\'' || inst_lst->value[0] == '\"')
			{
				new_value = ft_substr(inst_lst->value, 1,
						ft_strlen(inst_lst->value) - 2);
				free(inst_lst->value);
				inst_lst->value = new_value;
				inst_lst->type = TOKEN_STRING;
			}
		}
		inst_lst = inst_lst->next;
	}
}

void	remove_space_token(t_token **tklst)
{
	t_token	*inst_lst;
	t_token	*free_lst;

	free_lst = *tklst;
	while (free_lst)
	{
		inst_lst = free_lst->next;
		if (free_lst->type == TOKEN_SPACE)
		{
			if (free_lst->prev == NULL)
			{
				*tklst = free_lst->next;
				(*tklst)->prev = NULL;
			}
			else if (free_lst->next == NULL)
				free_lst->prev->next = NULL;
			else
			{
				free_lst->prev->next = free_lst->next;
				free_lst->next->prev = free_lst->prev;
			}
			ft_free_token(free_lst);
		}
		free_lst = inst_lst;
	}
}

void	change_env_to_cmd(t_token **tklst)
{
	t_token	*inst_lst;
	int		after_operator;

	inst_lst = *tklst;
	after_operator = 1;
	while (inst_lst)
	{
		if (after_operator && (inst_lst->type == TOKEN_ENV_VARI
				|| inst_lst->type == TOKEN_STRING))
			inst_lst->type = TOKEN_COMMAND;
		after_operator = 0;
		if (inst_lst->type == TOKEN_PIPE)
			after_operator = 1;
		inst_lst = inst_lst->next;
	}
}
