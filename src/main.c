/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 16:32:39 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/11 11:56:03 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_signals	g_signals = {0};

int	ft_setup_exec(t_data *data, t_token **token)
{
	data->exec = builder(*token);
	ft_free_token_list(*token);
	*token = NULL;
	if (!data->exec)
		return (1);
	data->exec_count = bd_lstsize(data->exec);
	data->pids = malloc(sizeof(pid_t) * (data->exec_count + 1));
	if (!data->pids)
		return (1);
	data->pid_count = 0;
	return (0);
}

// 파이프라인을 처리하는 함수
int	handle_pipeline(t_data *data, char **line)
{
	data->tklst = tokenize(data, line);
	if (data->tklst == NULL)
		return (1);
	if (ft_handle_heredoc(data->tklst, line) != 0)
	{
		ft_unlink_err(data->tklst);
		ft_free_token_list(data->tklst);
		return (1);
	}
	if (ft_setup_exec(data, &data->tklst) != 0)
		return (1);
	add_history(*line);
	free(*line);
	*line = NULL;
	ex_run_exec(data);
	ms_clear(data, data->tklst);
	return (0);
}

// 입력 루프를 처리하는 함수
int	handle_loop(t_data *data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		ft_init_signal();
		line = readline(PROMPT);
		if (line == NULL)
			break ;
		else if (ms_check_line(line) == 0)
		{
			if (handle_pipeline(data, &line) != 0)
				data->exit_code = 2;
			free(line);
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
