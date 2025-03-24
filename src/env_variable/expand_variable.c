/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:15:12 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/23 19:49:26 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// " $USER dkfj " 이런 입력에 대해 처리해줘야함.
// 마지막 것만 붙이면 됨.

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
		if(get_next_token_type(token) != TOKEN_STRING)
			return (ft_strdup("$"));
		else
			return (ft_strdup(""));
	else
		ret = get_env_value(data, key);
	free(key);
	return (ret);
}

static char	*expand_env_more_vari(t_data *data, char *token, int start)
{
	int		idx;
	char	*ret;
	char	*key;
	char	*value;

	ret = malloc(sizeof(char) * (count_total_length(data, token) + 1));
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, count_total_length(data, token) + 1);
	idx = -1;
	while (get_dollar_idx(token + start + 1) != -1)
	{
		idx = get_dollar_idx(token + start + 1);
		key = ft_substr(token, start + 1, idx);
		ft_strlcpy(ret + ft_strlen(ret), key, idx + 1);
		free(key);
		key = get_env_key(token + start + idx + 2);
		value = get_env_value(data, key);
		ft_strlcpy(ret + ft_strlen(ret), value, ft_strlen(value) + 1);
		start += idx + ft_strlen(key) + 1;
		free(key);
		free(value);
	}
	ft_strlcpy(ret + ft_strlen(ret), token + start + 1, ft_strlen(token + start + 1) + 1);
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
			inst_lst->value = expand_env_more_vari(data, old_str, -1);
			free(old_str);
		}
		inst_lst = inst_lst->next;
	}
}
