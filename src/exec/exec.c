/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:09:53 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/24 16:08:36 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
실행할 명령이 없으면 그냥 종료
fdio을 백업하고 명령 실행 후 복원
ex_run_pipeline에서 파이프 생성
*/
int	ex_run_exec(t_data *data)
{
	if (data->exec_count == 0)
		return (0);
	ex_backup_restore_fds(data, 0);
	ex_run_pipeline(data);
	ex_backup_restore_fds(data, 1);
	return (0);
}

// 단일 빌트인 exec(cd, export)이면 fork 없이 실행
// 그 외의 명령어는 자식 프로세스로 실행.
// 모든 프로세스를 실행한 후  종료 대기
int	ex_run_pipeline(t_data *data)
{
	t_exec	*tmp;
	int		builtin_type;

	tmp = data->exec;
	builtin_type = bi_is_builtin(tmp->cmd);
	if (tmp->next == NULL && builtin_type)
	{
		if (ex_init_redir(tmp))
			return (data->exit_code = 1, 1);
		printf("test 1 ok\n");
		if (builtin_type == 2)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		ex_unlink_heredoc(data);
		data->exit_code = bi_do_builtin(data, tmp->cmd, tmp->args);
		return (0);
	}
	while (tmp)
	{
		ex_setup_child(data, tmp);
		data->pid_count++;
		tmp = tmp->next;
	}
	ex_wait_child(data);
	return (0);
}

// fdio를 백업하거나 복원
// 리디렉션이 있는 경우 원래 입출력 상태로 되돌리는 데 필요
void	ex_backup_restore_fds(t_data *data, int mode)
{
	if (!mode)
	{
		data->def_in = dup(STDIN_FILENO);
		data->def_out = dup(STDOUT_FILENO);
	}
	else
	{
		ex_dup2_close(data->def_in, STDIN_FILENO);
		ex_dup2_close(data->def_out, STDOUT_FILENO);
	}
}

// def_in, def_out을 닫아서 inout을 안전하게 관리
// 파이프의 읽기/쓰기도 닫음
void	ex_close_all_fds(t_data *data, int pipe[])
{
	if (data)
	{
		ex_close(&(data->def_in));
		ex_close(&(data->def_out));
	}
	if (pipe)
	{
		ex_close(&(pipe[0]));
		ex_close(&(pipe[1]));
	}
}

// waitpid를 사용하여 모든 자식 프로세스가 종료될 때까지 기다림
// 정상 종료된 경우(WIFEXITED(status)), exit_code를 업데이트
// 시그널로 종료된 경우(WIFSIGNALED(status)), g_signals.signal_code 업데이트
// 마지막에 heredoc 삭제
void	ex_wait_child(t_data *data)
{
	int		status;
	int		i;

	i = 0;
	while (i < data->pid_count)
	{
		if (waitpid(data->pids[i], &(status), 0))
		{
			if (WIFEXITED(status))
			{
				g_signals.signal_code = 0;
				data->exit_code = WEXITSTATUS(status);
			}
			else if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == SIGQUIT)
					ex_err_coredump(data->pids[i]);
				g_signals.signal_code = SIGNAL_OFFSET + WTERMSIG(status);
			}
		}
		i++;
	}
	ex_unlink_heredoc(data);
}
