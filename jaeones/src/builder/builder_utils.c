/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:03:44 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/19 17:43:25 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_exec를 초기화하는 함수
t_exec	*bd_init(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	new->args = NULL;
	new->cmd = NULL;
	new->fd_in = STDIN_FILENO;
	new->fd_out = STDOUT_FILENO;
	new->redirs = NULL;
	new->next = NULL;
	return (new);
}

// t_exec의 메모리를 해제하는 함수
void	bd_free(t_exec *exec)
{
	t_exec	*tmp;

	while (exec != NULL)
	{
		tmp = exec;
		if (exec->cmd)
			free(exec->cmd);
		if (exec->args)
			arg_free(exec->args);
		if (exec->redirs)
			file_free(exec->redirs);
		exec = exec->next;
		free(tmp);
	}
}

// 실행 리스트의 크기를 반환하는 함수
int	bd_lstsize(t_exec *exec)
{
	int	i;

	i = 0;
	while (exec)
	{
		i++;
		exec = exec->next;
	}
	return (i);
}
