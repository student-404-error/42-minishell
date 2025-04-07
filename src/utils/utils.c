/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 12:39:30 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/07 16:32:01 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 미니쉘을 실행할 때 필요한 t_data를 초기화하는 함수
// envp를 복사하고, 파일 디스크립터를 설정함
t_data	*ms_init_data(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->envp = ms_env_dup(envp);
	if (!data->envp)
	{
		free(data);
		return (NULL);
	}
	data->def_in = STDIN_FILENO;
	data->def_out = STDOUT_FILENO;
	data->exec = NULL;
	data->pids = NULL;
	data->exec_count = 0;
	data->pid_count = 0;
	data->exit_code = 0;
	return (data);
}

// 미니쉘 실행 중에 할당된 메모리를 해제하는 함수.
void	ms_clear(t_data *data, t_token *token)
{
	if (token)
		ft_free_token_list(token);
	if (data)
	{
		if (data->exec)
		{
			bd_free(data->exec);
			data->exec = NULL;
		}
		if (data->pids)
		{
			free(data->pids);
			data->pids = NULL;
		}
	}
}

// 미니쉘이 종료될 때 실행되어 모든 할당된 메모리를 해제
// 환경 변수, 실행 정보, 프로세스 리스트 등 전체를 정리
void	ms_free_all(t_data *data)
{
	if (data)
	{
		if (data->exec)
			bd_free(data->exec);
		if (data->envp)
			env_free(data->envp);
		if (data->pids)
			free(data->pids);
		free(data);
	}
	rl_clear_history();
}

int	ms_check_line(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}

char	*ft_gen_random_name(char *str)
{
	unsigned long	rand;
	int				i;
	char			*new;

	if (!str)
		return (NULL);
	new = ft_calloc(sizeof(char), 17);
	if (!new)
		return (NULL);
	rand = (unsigned long)str;
	ft_strlcpy(new, "/tmp/hd_", 9);
	i = 8;
	while (i < 16)
	{
		rand *= RND_OFFSET + RND_PRIME;
		new[i] = 'a' + (rand % 26);
		i++;
	}
	new[i] = '\0';
	return (new);
}
