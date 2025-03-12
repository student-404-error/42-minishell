/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:29:25 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 15:16:24 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdlib.h>

size_t	key_length(char *key_value)
{
	size_t	len;

	len = 0;
	while (key_value[len] != '\0' && key_value[len] != '=')
		len++;
	return (len);
}

int	is_valid_env_key(char *key)
{
	while (*key)
	{
		if (*key == '=')
			return (1);
		key++;
	}
	return (0);
}

int	builtin_unset(t_data *data, char *target)
{
	t_env	*env_list;
	t_env	*tmp;

	if (!ft_strcmp(target, "_")) // _는 삭제되면 안됨.
		return (SUCCESS);
	if (is_valid_env_key(target))
	{
		// unset할 때 무조건 env_name만 arg로 받아야함. 아니면 에러.
		printf("minishell: unset: `%s': not a valid identifier\n", target);
		return (ERROR);
	}
	env_list = data->envp;
	tmp = NULL;
	if (ft_strcmp(env_list->key, target) == 0)
		data->envp = env_list->next;
	else
	{
		while (env_list->next->next && ft_strcmp(env_list->next->key, target) != 0)
			env_list = env_list->next;
		tmp = env_list->next;
		env_list->next = tmp->next;
	}
	return (free(tmp->key), free(tmp->value), free(tmp), SUCCESS);
}

// 자 지금 구현해야하는게
// 생성, 변경 두개야.
// 근데 여기서 세부적으로 나눠보자면
// export!!
// 1. 생성
//    1. 새로운 env 생성
//    2. 기존 env_list에 추가.
// 2. 변경
//	  1. 검색
//	  2. 수정
// unset!!
// 1. 삭제
// 
// 총 필요한 거는
// 삽입, 삭제, 수정, 검색
//
// 최종 알고리즘은
// export니까
// 1. 검색
// if. 이미 존재하는가?
//		yes: 수정
//		no : 삽입 -> 정렬
// 
//

t_env	*ft_new_env(char *str)
{
	t_env	*new_env;
	size_t	len;

	new_env = malloc(sizeof(t_env));
	len = key_length(str);
	new_env->key = ft_substr(str, 0, len);
	new_env->value = ft_substr(str, len + 1, ft_strlen(str));
	new_env->len = ft_strlen(new_env->value);
	new_env->next = NULL;
	return (new_env);
}

t_env	*ft_last_env(t_env *env_list)
{
	t_env	*env_ptr;

	if (env_list == NULL)
		return (NULL);
	env_ptr = env_list;
	while (env_ptr->next)
		env_ptr = env_ptr->next;
	return (env_ptr);
}

void	ft_env_add_back(t_env **env_list, t_env *new_env)
{
	t_env	*last_env;

	last_env = ft_last_env(*env_list);
	if (!new_env)
		return ;
	if (last_env)
		last_env->next = new_env;
	else
		*env_list = new_env;
}

void	init_env(t_data *data, char **env_list)
{
	size_t	i;
	t_env	*new_env;

	i = 0;
	data->envp = NULL;
	while (env_list[i])
	{
		new_env = ft_new_env(env_list[i]);
		ft_env_add_back(&data->envp, new_env);
		i++;
	}
}

int	builtin_env(t_data data)
{
	t_env	*env_list;

	env_list = data.envp;
	if (!env_list)
		return (1);
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
	return (0);
}
