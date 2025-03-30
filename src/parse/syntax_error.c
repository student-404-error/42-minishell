/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:19:23 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/30 17:28:32 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_syntax_error(char *token)
{
	printf("charles mishell: syntax error \
			near unexpected token \`%s\'", token);
}

int	check_heredoc_syntax();
int	check_redir_syntax();
int	check_pipe_syntax()
{
	// 파이프를 기준으로 cmd가 양쪽에 있어야하는거잖아.
	// 예를 들어
	// | echo 3 -> syntax_error
	// echo 3 | -> syntax_error
	// | -> syntax_error
	// < |
	// | |
	return (1);
}
void	syntax_error(t_token *tklst)
{
	if (check_pipe_syntax(tklst))
		return (err);
	if (check_redir_syntax(tklst))
		return (err);
	if (check_heredoc_syntax(tklst))
		return (err);
}
