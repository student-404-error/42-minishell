/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:53:28 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/11 15:06:31 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 리디렉션이 나오면 해당 파일명을 t_file에 추가
static int	bd_handle_redirs(t_exec *exec, t_token *token)
{
	t_file	*tmp;

	if (token->next && token->next->value != NULL
		&& (token->type == TOKEN_REDIRECTION_APPEND
			|| token->type == TOKEN_HEREDOC
			|| token->type == TOKEN_REDIRECTION_IN
			|| token->type == TOKEN_REDIRECTION_OUT))
	{
		tmp = file_create(token->next->value, token->type);
		if (!tmp)
			return (-1);
		file_add_back(&(exec->redirs), tmp);
		return (1);
	}
	return (0);
}

// argument 인 경우 t_args에 추가
static int	bd_handle_args(t_exec *exec, t_token *token)
{
	t_args	*new;

	new = NULL;
	if (token->type == TOKEN_STRING)
	{
		new = arg_create(token->value);
		if (!new)
			return (-1);
		arg_add_back(&(exec->args), new);
	}
	return (0);
}

// 실행 구조체를 생성하는 함수
// 입력된 토큰을 분석하여 t_exec 구조체를 생성
// 파이프가 나오면 재귀적으로 다음 명령을 생성
t_exec	*builder(t_token *token)
{
	t_exec	*exec;

	exec = bd_init();
	if (!exec)
		return (NULL);
	while (token != NULL)
	{
		if (token->type == TOKEN_PIPE)
		{
			exec->next = builder(token->next);
			break ;
		}
		else if (token->type == TOKEN_COMMAND)
		{
			exec->cmd = ft_strdup(token->value);
			if (!exec->cmd)
				return (NULL);
		}
		bd_handle_redirs(exec, token);
		bd_handle_args(exec, token);
		token = token->next;
	}
	return (exec);
}
