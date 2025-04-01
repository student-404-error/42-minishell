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

int	print_syntax_error(char *token)
{
	printf("charles mishell: syntax error near unexpected token `%s'", token);
	return (1);
}
/*
int	check_heredoc_syntax()
{
	if (first_token->type = TOKEN_PIPE)
		return (print_syntax_error("<<"));
	if (last_token->type = TOKEN_PIPE)
		return (print_syntax_error("<<"));
	if (pipe_token->next->type = TOKEN_PIPE)
		return (print_syntax_error("<<"));
	if (redir_token->type = TOKEN_PIPE)
		return (print_syntax_error("<<"));
}

int	check_redir_syntax()
{
	if (first_token->type = TOKEN_PIPE)
		return (print_syntax_error("|"));
	if (last_token->type = TOKEN_PIPE)
		return (print_syntax_error("|"));
	if (pipe_token->next->type = TOKEN_PIPE)
		return (print_syntax_error("|"));
	if (redir_token->type = TOKEN_PIPE)
		return (print_syntax_error("|"));
}
*/
int	check_pipe_syntax(t_token *tklst)
{
	if (tklst->prev == NULL)
		return (print_syntax_error("|"));
	if (tklst->next == NULL)
		return (print_syntax_error("|"));
	if (tklst->next->type == TOKEN_PIPE)
		return (print_syntax_error("|"));
	if (tklst->prev->type >= 6 && tklst->prev->type <= 9)
		return (print_syntax_error("|"));
	return (0);
}

void	syntax_error(t_token *tklst)
{
	while (tklst)
	{
		if (tklst->type == TOKEN_PIPE)
			if (check_pipe_syntax(tklst))
				return /* free tklst or return err*/ ;
//		if (tklst->type == TOKEN_HEREDOC)
//			if (check_redir_syntax(tklst))
//				return (err);
//		if (tklst->type == TOKEN_REDIRECTION_IN)
//			if (check_heredoc_syntax(tklst))
//				return (err);
		tklst = tklst->next;
	}
}
