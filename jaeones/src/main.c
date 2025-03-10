/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:32:39 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/10 14:14:26 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signals	g_signals = {0};

int	ms_setup_exec(t_data *data, t_token **token)
{
	// 토큰을 기반으로 실행 리스트를 생성
	data->exec = builder(*token);
	tok_free_list(*token);
	*token = NULL;
	if (!data->exec)
		return (1);

	// 실행할 명령어 개수를 저장
	data->exec_count = bd_lstsize(data->exec);

	// 프로세스 ID를 저장할 메모리 할당
	data->pids = malloc(sizeof(pid_t) * (data->exec_count + 1));
	if (!data->pids)
		return (1);
	data->pid_count = 0;
	return (0);
}

// 파이프라인을 처리하는 함수
int	handle_pipeline(t_data *data, char *line)
{
	t_token	*token;
	
	data->tklst = tokenize(data, line);
	free(line);
	if (data->tklst == NULL)
		return (0);
	if (ft_strncmp(line, "env", 3) == 0)
		builtin_env(data);
	else if (ft_strncmp(line, "unset", 5) == 0)
	{
		builtin_unset(data, line + 6);
	}
	free(line);
	if (ms_setup_exec(data, &token) != 0)
		return (1);
	ex_run_exec(data); // 실행부부 함수 호출
	ms_clear(data, token); // 실행 후 데이터 정리
	return (0);
}

// 입력 루프를 처리하는 함수
int	handle_loop(t_data *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		sg_init_signal();
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		else if (ms_check_line(line) == 0) // 빈 입력이 아닐 경우 처리
		{
			add_history(line);
			if (handle_pipeline(data, line) != 0)
			{
				ft_putstr_fd("Parsing error!\n", 2);
				data->exit_code = 2;
			}
			line = NULL;
		}
		if (line)
			free(line);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = ms_init_data(envp);
	if (!data)
		return (EXIT_FAILURE);
	handle_loop(data);
	ms_free_all(data);
	ft_putstr_fd("exit\n", 2);
	return (EXIT_SUCCESS);
}
