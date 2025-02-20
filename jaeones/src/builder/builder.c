/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:53:28 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/19 17:41:54 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 리디렉션이 나오면 해당 파일명을 t_file에 추가
static int	bd_handle_redirs(t_exec *exec, t_token *token)
{
	t_file	*tmp;

	// 리디렉션 토큰이면서 다음 토큰에 파일명이 존재하는 경우
	if (token->next && token->next->value != NULL
		&& (token->type == APPEND || token->type == N_HEREDOC
			|| token->type == INFILE || token->type == OUTFILE))
	{
		tmp = file_create(token->next->value, token->type);
		if (!tmp)
			return (-1);
		file_add_back(&(exec->redirs), tmp); // 리스트에 추가
		return (1);
	}
	return (0);
}

// argument 인 경우 t_args에 추가
static int	bd_handle_args(t_exec *exec, t_token *token)
{
	t_args	*new;

	new = NULL;
	if (token->type == ARGUMENT)
	{
		new = arg_create(token->value);
		if (!new)
			return (-1);
		arg_add_back(&(exec->args), new); // 리스트에 추가
	}
	return (0);
}

t_exec	*builder(t_token *token)
{
	t_exec	*exec;

	exec = bd_init();
	if (!exec)
		return (NULL);
	while (token != NULL)
	{
		if (token->type == PIPE) //if 파이프가 다음 명령을 재귀로 생성
		{
			exec->next = builder(token->next);
			break ;
		}
		else if (token->type == COMMAND) //if 명령어, 저장
		{
			exec->cmd = ft_strdup(token->value);
			if (!exec->cmd)
				return (NULL);
		}
		// 리디렉션 및 인자 처리
		bd_handle_redirs(exec, token);
		bd_handle_args(exec, token);
		token = token->next; 
	}
	return (exec);
}
