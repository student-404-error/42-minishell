/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:02:54 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/29 17:44:57 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_print_export(t_env *env)
{
	char	**envs;
	char	*tmp;
	char	*tmp_id;
	int		i;

	envs = ex_get_envs(env);
	if (!envs)
		return (1);
	ft_advanced_sort_string_tab(envs, &ft_strcmp);
	i = -1;
	while (envs[++i])
	{
		printf("export ");
		tmp = ft_strchr(envs[i], '=');
		if (!tmp)
			printf("%s\n", envs[i]);
		else
		{
			tmp_id = env_create_id(envs[i]);
			printf("%s=\"%s\"\n", tmp_id, tmp + 1);
			free(tmp_id);
		}
	}
	ft_free_all(envs);
	return (0);
}

static t_env	*bi_new_var(char *arg_id, char *arg_raw)
{
	t_env	*tmp;
	char	*arg_value;

	arg_value = env_create_value(arg_raw);
	tmp = env_create(arg_id, arg_value, arg_raw);
	if (!tmp)
	{
		free(arg_raw);
		if (arg_value)
			free(arg_value);
		free(arg_id);
		return (NULL);
	}
	return (tmp);
}

static void	bi_update_var(t_env *node, char *arg_raw)
{
	char	*arg_value;

	arg_value = env_create_value(arg_raw);
	if (!arg_value)
	{
		free(arg_raw);
		return ;
	}
	if (node->value)
		free(node->value);
	if (node->raw)
		free(node->raw);
	node->value = arg_value;
	node->raw = arg_raw;
}

int	bi_add_var(char *value, t_env **env)
{
	char	*arg_id;
	char	*arg_raw;
	t_env	*tmp;

	arg_id = env_create_id(value);
	if (!arg_id || !bi_check_id(arg_id))
		return (free(arg_id), bi_error_export(value));
	arg_raw = ft_strdup(value);
	if (!arg_raw)
		return (free(arg_id), 1);
	tmp = ms_getenv(arg_id, *env);
	if (!tmp)
	{
		tmp = bi_new_var(arg_id, arg_raw);
		if (!tmp)
			return (1);
		env_add_back(env, tmp);
	}
	else
	{
		free(arg_id);
		bi_update_var(tmp, arg_raw);
	}
	return (0);
}

int	bi_delete_var(char *value, t_env **env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = ms_getenv(value, *env);
	if (!tmp)
		return (0);
	if (*env == tmp)
		*env = tmp->next;
	else
	{
		tmp2 = *env;
		while (tmp2->next != tmp)
			tmp2 = tmp2->next;
		tmp2->next = tmp->next;
	}
	env_del_one(tmp);
	return (0);
}
