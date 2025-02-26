/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:10:05 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/17 16:47:34 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 파이프를 생성하는 함수
// pipe() 시스템 호출을 사용해 fd_pipe 배열에 읽기/쓰기용 파일 디스크립터 저장
void	ex_create_pipe(int fd_pipe[2])
{
	if (pipe(fd_pipe) == -1)
		ex_err_pipe(errno); // 파이프 생성 실패 시 오류 처리
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
	ex_create_pipe(fd_pipe); // 파이프 생성
	signal(SIGINT, sg_exec_handler); // SIGINT 핸들러 설정
	data->pids[data->pid_count] = fork(); // 자식 프로세스 생성
	if (data->pids[data->pid_count] == -1)
		ex_err_fork(errno); // fork() 실패 시 오류 처리
	else if (!data->pids[data->pid_count])
		ex_execute_child(data, exec, fd_pipe); // 자식 프로세스 실행
	else
	{
		if (fd_pipe[0] != -1)
			dup2(fd_pipe[0], STDIN_FILENO); // 부모 프로세스의 입력을 자식 프로세스의 출력으로 설정
	}
	ex_close_all_fds(NULL, fd_pipe); // 불필요한 파일 디스크립터 닫기
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
	signal(SIGQUIT, SIG_DFL); // SIGQUIT 기본 동작 설정
	if (exec->next && exec->fd_out == STDOUT_FILENO && fd_pipe[1] != -1)
		dup2(fd_pipe[1], STDOUT_FILENO); // 출력을 파이프의 쓰기 끝으로 변경
	if (ex_init_redir(exec))
	{
		ex_close_all_fds(data, fd_pipe);
		ms_free_all(data);
		exit(EXIT_FAILURE); // 리디렉션 실패 시 종료
	}
	ex_close_all_fds(data, fd_pipe);
	if (bi_is_builtin(exec->cmd))
	{
		exit_code = bi_do_builtin(data, exec->cmd, exec->args);
		ms_free_all(data);
		exit(exit_code); // 내장 명령어 실행 후 종료
	}
	exit_code = ex_do_exec(data, exec->cmd, exec->args); // 외부 명령어 실행
	ms_free_all(data);
	if (exit_code == -2)
		exit(IS_A_DIRECTORY); // 실행 대상이 디렉토리일 경우 종료
	exit(COMMAND_NOT_FOUND); // 명령어를 찾을 수 없는 경우 종료
}

// dup2를 실행하고 원본 파일 디스크립터를 닫는 함수
void	ex_dup2_close(int fd1, int fd2)
{
	dup2(fd1, fd2); // fd1을 fd2로 복사
	close(fd1); // 원본 파일 디스크립터 닫기
}

// 절대 경로 여부를 확인하는 함수
// 파일 경로에 '/'가 포함되어 있으면 절대 경로로 판단
int	ex_is_abs_path(char *file)
{
	while (*file)
	{
		if (*file++ == '/')
			return (1); // 절대 경로일 경우 1 반환
	}
	return (0); // 상대 경로일 경우 0 반환
}