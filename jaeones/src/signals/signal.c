/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 16:11:30 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/10 17:24:27 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Readline 이벤트 훅에서 호출되는 간단한 함수 (현재는 EXIT_SUCCESS만 반환)
이벤트 루프가 돌면서 시그널을 감지함
*/
int sg_readline_event(void)
{
    return (EXIT_SUCCESS);
}

/*
시그널 핸들러를 설정하는 함수
SIGINT (Ctrl+C) -> sg_input_handler 실행
SIGQUIT (Ctrl+\) 및 SIGTSTP (Ctrl+Z) -> 무시
*/
void ft_init_signal(void)
{
    rl_event_hook = sg_readline_event; // Readline 이벤트 훅 설정
    signal(SIGINT, sg_input_handler);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
}

// Ctrl+C(SIGINT)를 입력했을 때 호출되는 핸들러
void sg_input_handler(int status)
{
    (void)status;
    if (g_signals.signal_code != 1) // 현재 SIGINT가 이미 처리되지 않았는지 확인
    {
        g_signals.signal_code = SIGNAL_OFFSET + SIGINT; // SIGINT 이벤트 발생 기록
        write(STDIN_FILENO, "\n", 1); // 새 줄 출력
        rl_replace_line("", 0); // 현재 입력된 줄 삭제
        rl_on_new_line(); // 새로운 입력 줄 준비
        rl_redisplay(); // Readline을 다시 출력
    }
}

// 실행 중인 명령어가 있을 때 Ctrl+C를 입력하면 실행되는 핸들러
void sg_exec_handler(int status)
{
    (void)status;
    g_signals.signal_code = SIGNAL_OFFSET + SIGINT; // SIGINT 이벤트 발생 기록
    write(STDERR_FILENO, "\n", 1); // 에러 출력 스트림에 새 줄 추가 (현재 실행 중인 명령 종료)
}

// Heredoc 입력 도중 Ctrl+C를 입력하면 실행되는 핸들러
void sg_heredoc_handler(int status)
{
    (void)status;
    rl_replace_line("", 0); // 현재 입력 줄 삭제
    rl_redisplay(); // Readline을 다시 출력
    rl_done = 1; // Readline 종료 플래그 설정
    g_signals.eof = 1; // Heredoc 종료 상태로 변경
    g_signals.signal_code = SIGNAL_OFFSET + SIGINT; // SIGINT 이벤트 발생 기록
}