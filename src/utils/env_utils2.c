/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:42:57 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/20 16:02:41 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_default_env(void)
{
	char	*id;
	char	*value;
	t_env	*def;

	id = env_get_id(DEF_ENV);
	value = env_get_value(DEF_ENV);
	def = env_create(id, value, ft_strdup(DEF_ENV));
	return (def);
}

/*
환경 변수 이름(PATH)을 입력 전달.
이를 통해 $PATH 또는 $HOME과 같은 환경 변수의 값을 가져옴.
반환 값은 메모리 해제가 필요 없는 char*.
'path'가 $?와 같은지 확인하는 조건문 추가 가능.
$?일 경우, 마지막 명령의 종료 코드를 반환 가능.
printf "$?\n"이랑 비슷한 방식.
*/

t_env	*ms_getenv(char *path, t_env *envp)
{
	if (envp == NULL || path == NULL)
		return (NULL);
	while (envp != NULL)
	{
		if (ft_strcmp(path, envp->id) == 0)
			return (envp);
		envp = envp->next;
	}
	return (NULL);
}

char	*env_get_id(char *raw)
{
	char	*eq;

	if (!raw)
		return (NULL);
	eq = ft_strchr(raw, '=');
	if (!eq)
		return (ft_strdup(raw));
	else if (eq - raw == 0)
		return (NULL);
	return (ft_strndup(raw, eq - raw));
}

char	*env_get_value(char *raw)
{
	char	*eq;

	if (!raw)
		return (NULL);
	eq = ft_strchr(raw, '=');
	if (!eq)
		return (NULL);
	else if (eq - raw == 0)
		return (NULL);
	return (ft_strdup(raw + (eq - raw + 1)));
}

int	env_lstsize(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
