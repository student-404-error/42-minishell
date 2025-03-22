/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:13:22 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 20:25:21 by seong-ki         ###   ########.fr       */
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
			}
		}
		inst_lst = inst_lst->next;
	}
}

void	remove_space_token(t_token **tklst)
{
	t_token	*inst_lst;

	inst_lst = tklst;
	while (inst_lst)
	{
		if (inst_lst->type == TOKEN_SPACE)
		{
			if (inst_lst->prev == NULL)
			{
				*tklst = inst_lst->next;
				*tklst->prev = NULL;
			}
			else if (inst_lst->next == NULL)
				inst_lst->prev->next = NULL;
			else
			{
				inst_lst->prev->next = inst_lst->next;
				inst_lst->next->prev = inst_lst->prev;
			}
			ft_free_token(inst_lst);
		}
	}
}


