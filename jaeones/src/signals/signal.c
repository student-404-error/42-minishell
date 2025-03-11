/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:11:30 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/11 15:17:28 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Readline 이벤트 훅에서 호출되는 간단한 함수 (현재는 EXIT_SUCCESS만 반환)
// 이벤트 루프가 돌면서 시그널을 감지함
int	sg_readline_event(void)
{
	return (EXIT_SUCCESS);
}

// 시그널 핸들러를 설정하는 함수
// SIGINT (Ctrl+C) -> sg_input_handler 실행
// SIGQUIT (Ctrl+\) 및 SIGTSTP (Ctrl+Z) -> 무시
void	ft_init_signal(void)
{
	rl_event_hook = sg_readline_event;
	signal(SIGINT, sg_input_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}

// Ctrl+C(SIGINT)를 입력했을 때 호출되는 핸들러
void	sg_input_handler(int status)
{
	(void)status;
	if (g_signals.signal_code != 1)
	{
		g_signals.signal_code = SIGNAL_OFFSET + SIGINT;
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

// 실행 중인 명령어가 있을 때 Ctrl+C를 입력하면 실행되는 핸들러
void	sg_exec_handler(int status)
{
	(void)status;
	g_signals.signal_code = SIGNAL_OFFSET + SIGINT;
	write(STDERR_FILENO, "\n", 1);
}

// Heredoc 입력 도중 Ctrl+C를 입력하면 실행되는 핸들러
void	sg_heredoc_handler(int status)
{
	(void)status;
	rl_replace_line("", 0);
	rl_redisplay();
	rl_done = 1;
	g_signals.eof = 1;
	g_signals.signal_code = SIGNAL_OFFSET + SIGINT;
}
