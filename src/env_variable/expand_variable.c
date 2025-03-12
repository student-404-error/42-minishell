/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:15:12 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 21:23:53 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_env_vari2(t_data *data, char *token, int start)
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
	return (ret);
}

void	expand_env_vari(t_data *data, t_token **tklst)
{
	t_token	*inst_lst;
	char	*old_str;

	inst_lst = *tklst;
	while (inst_lst)
	{
		if (inst_lst->type == 3)
		{
			old_str = inst_lst->value;
			inst_lst->value = expand_env_vari2(data, old_str, -1);
			free(old_str);
		}
		inst_lst = inst_lst->next;
	}
}
