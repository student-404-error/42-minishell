/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:43:07 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/17 15:42:59 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ms_env_dup(char **envp)
{
	int		i;
	char	*key;
	char	*value;
	t_env	*new_env;
	t_env	*tmp;

	i = 0;
	new_env = NULL;
	if (!envp || (envp && *envp == NULL))
		return (env_default_env());
	while (envp[i])
	{
		key = env_create_id(envp[i]);
		value = env_create_value(envp[i]);
		tmp = env_create(key, value, ft_strdup(envp[i]));
		if (!tmp)
			return (NULL);
		env_add_back(&new_env, tmp);
		i++;
	}
	return (new_env);
}

t_env	*env_create(char *key, char *value, char *raw)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
	{
		free(key);
		free(value);
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->raw = raw;
	new->len = ft_strlen(value);
	new->next = NULL;
	return (new);
}

int	env_add_back(t_env **head, t_env *new)
{
	t_env	*tmp;

	if (*head == NULL)
		*head = new;
	else
	{
		tmp = (*head);
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (0);
}

void	env_del_one(t_env *env)
{
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	if (env->raw)
		free(env->raw);
	free(env);
}

void	env_free(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		env_del_one(tmp);
	}
}
