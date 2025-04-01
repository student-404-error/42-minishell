/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:15:12 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/29 17:40:24 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_next_token_type(t_token *token)
{
	if (token->next == NULL)
		return (-1);
	return (token->next->type);
}

char	*expand_env_one_vari(t_data *data, t_token *token)
{
	char	*ret;
	char	*key;

	key = get_env_key(token->value + 1);
	if (ft_strcmp(key, "") == 0)
		if (get_next_token_type(token) != TOKEN_STRING)
			return (free(key), ft_strdup("$"));
		else
			return (free(key), ft_strdup(""));
	else
		ret = get_env_value(data, key);
	return (free(key), ret);
}

static char	*expand_env_more_vari(t_data *data, char *token, int start, int idx)
{
	int		total_length;
	char	*ret;
	char	*key;
	char	*value;

	total_length = count_total_length(data, token);
//	if (total_length == 0)
//		return (ft_strdup(""));
	ret = malloc(sizeof(char) * (total_length + 1));
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, total_length + 1);
	while (get_dollar_idx(token + start + 1) != -1)
	{
		idx = get_dollar_idx(token + start + 1);
		ft_strlcpy(ret + ft_strlen(ret), token + start + 1, idx + 1);
		key = get_env_key(token + start + idx + 2);
		value = get_env_value(data, key);
		ft_strlcpy(ret + ft_strlen(ret), value, ft_strlen(value) + 1);
		start += idx + ft_strlen(key) + 1;
		free(key);
		free(value);
	}
	ft_strlcpy(ret + ft_strlen(ret), token + start + 1,
		ft_strlen(token + start + 1) + 1);
	return (ret);
}

void	expand_env_vari(t_data *data, t_token **tklst)
{
	t_token	*inst_lst;
	char	*old_str;

	inst_lst = *tklst;
	while (inst_lst)
	{
		if (inst_lst->type == TOKEN_ENV_VARI)
		{
			old_str = inst_lst->value;
			inst_lst->value = expand_env_one_vari(data, inst_lst);
			free(old_str);
		}
		else if (inst_lst->type == TOKEN_STRING)
		{
			old_str = inst_lst->value;
			inst_lst->value = expand_env_more_vari(data, old_str, -1, -1);
			free(old_str);
		}
		inst_lst = inst_lst->next;
	}
}
