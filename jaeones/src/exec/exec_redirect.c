/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:10:16 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/10 16:45:13 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_init_redir(t_exec *exec)
{
	if (ex_handle_redir(exec))
		return (1);
	return (0);
}
/*
exec->redirs는 명령과 함께 설정된 리디렉션 정보를 담고 있음
모든 리디렉션을 하나씩 처리(ex_redirection)
파일 디스크립터(fd_in 또는 fd_out)가 -1이면 오류 발생
*/
int	ex_handle_redir(t_exec *exec)
{
	t_file	*tmp;

	tmp = exec->redirs;
	while (tmp) // 연결된 모든 리디렉션 처리
	{
		ex_redirection(exec, tmp); // 개별 리디렉션 설정
		if (exec->fd_in == -1 || exec-> fd_out == -1) // 파일 열기 실패 체크
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
/*
*** input redirect (<, <<)
fd_in을 닫고, 새 파일을 O_RDONLY로로 오픈
ex_dup2_close(exec->fd_in, STDIN_FILENO)를 사용하여 STDIN_FILENO을 새 파일로 변경
*** output redirect (>, >>)
기존 표준 출력(fd_out)을 닫고, 새 파일을 O_WRONLY로 오픈
>: 덮어쓰기(O_TRUNC)
>>: 추가 모드(O_APPEND)
ex_dup2_close(exec->fd_out, STDOUT_FILENO)를 사용하여 STDOUT_FILENO을 새 파일로 변경
*/
void	ex_redirection(t_exec *exec, t_file *file)
{
	if (file->type == TOKEN_REDIRECTION_IN || file->type == TOKEN_FILENAME) // 입력 리디렉션 처리
	{
		if (exec->fd_in != STDIN_FILENO)
			close (exec->fd_in);
		exec->fd_in = open(file->path, O_RDONLY);
		if (exec->fd_in == -1)
			ex_err_open(errno, file->path);
		ex_dup2_close(exec->fd_in, STDIN_FILENO); // 표준 입력으로 설정
	}
	else // 출력 리디렉션 처리
	{
		if (exec->fd_out != STDOUT_FILENO)
			close(exec->fd_out);
		if (file->type == TOKEN_REDIRECTION_OUT) // > : 덮어쓰기 모드
			exec->fd_out = open(file->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (file->type == TOKEN_REDIRECTION_APPEND) // >> : 추가 모드
			exec->fd_out
				= open(file->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (exec->fd_out == -1)
			ex_err_open(errno, file->path);
		ex_dup2_close(exec->fd_out, STDOUT_FILENO); // 표준 출력으로 설정
	}
}
