/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:10:05 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/11 14:59:26 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 파이프를 생성하는 함수
// pipe() 시스템 호출을 사용해 fd_pipe 배열에 읽기/쓰기용 파일 디스크립터 저장
void	ex_create_pipe(int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		ex_err_pipe(errno);
}

// 자식 프로세스를 설정하는 함수
// 1. 파이프를 생성하고
// 2. SIGINT 신호 핸들러를 변경한 후
// 3. fork()를 호출하여 자식 프로세스를 생성
// 4. 부모 프로세스는 자식 프로세스의 출력을 표준 입력으로 설정
// 5. 모든 열린 파일 디스크립터를 정리
void	ex_setup_child(t_data *data, t_exec *exec)
{
	int		fd_pipe[2];

	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	ex_create_pipe(fd_pipe);
	signal(SIGINT, sg_exec_handler);
	data->pids[data->pid_count] = fork();
	if (data->pids[data->pid_count] == -1)
		ex_err_fork(errno);
	else if (!data->pids[data->pid_count])
		ex_execute_child(data, exec, fd_pipe);
	else
	{
		if (fd_pipe[0] != -1)
			dup2(fd_pipe[0], STDIN_FILENO);
	}
	ex_close_all_fds(NULL, fd_pipe);
}

// 자식 프로세스에서 실행되는 함수
// 1. SIGQUIT 신호를 기본 동작으로 설정
// 2. 필요한 경우 출력 리디렉션을 설정
// 3. 파일 리디렉션이 실패하면 종료
// 4. 내장 명령어 실행 후 종료
// 5. 외부 명령어 실행 후 종료
void	ex_execute_child(t_data *data, t_exec *exec, int fd_pipe[])
{
	int	exit_code;

	exit_code = 0;
	signal(SIGQUIT, SIG_DFL);
	if (exec->next && exec->fd_out == STDOUT_FILENO && fd_pipe[1] != -1)
		dup2(fd_pipe[1], STDOUT_FILENO);
	if (ex_init_redir(exec))
	{
		ex_close_all_fds(data, fd_pipe);
		ms_free_all(data);
		exit(EXIT_FAILURE);
	}
	ex_close_all_fds(data, fd_pipe);
	if (bi_is_builtin(exec->cmd))
	{
		exit_code = bi_do_builtin(data, exec->cmd, exec->args);
		ms_free_all(data);
		exit(exit_code);
	}
	exit_code = ex_do_exec(data, exec->cmd, exec->args);
	ms_free_all(data);
	if (exit_code == -2)
		exit(IS_A_DIRECTORY);
	exit(COMMAND_NOT_FOUND);
}

// dup2를 실행하고 원본 파일 디스크립터를 닫는 함수
void	ex_dup2_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

// 절대 경로 여부를 확인하는 함수
// 파일 경로에 '/'가 포함되어 있으면 절대 경로로 판단
int	ex_is_abs_path(char *file)
{
	while (*file)
	{
		if (*file++ == '/')
			return (1);
	}
	return (0);
}
