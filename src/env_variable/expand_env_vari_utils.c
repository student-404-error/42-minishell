/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_vari_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:51:41 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 18:53:06 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_dollar_idx(char *s)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_key(char *str)
{
	int		len;
	char	*key;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	key = malloc(sizeof(char) * len + 1);
	if (key == NULL)
		return (NULL);
	ft_strlcpy(key, str, len + 1);
	return (key);
}

char	*get_env_value(t_data *data, char *key)
{
	t_env	*env;

	if (ft_strcmp(key, "") == 0)
		return (ft_strdup("$"));
	env = data->env;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

int	get_env_value_len(t_data *data, char *key)
{
	t_env	*env;

	if (ft_strcmp(key, "") == 0)
		return (0);
	env = data->env;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->len);
		env = env->next;
	}
	return (-1);
}

int	count_total_length(t_data *data, char *token)
{
	int		length;
	int		idx;
	char	*key;

	idx = -1;
	length = 0;
	while (get_dollar_idx(token + idx + 1) != -1)
	{
		length += get_dollar_idx(token + idx + 1);
		idx += get_dollar_idx(token + idx + 1) + 1;
		key = get_env_key(token + idx + 1);
		length += get_env_value_len(data, key);
		idx += ft_strlen(key);
		free(key);
	}
	return (length);
}
