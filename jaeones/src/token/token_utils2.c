/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:11:04 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/20 15:54:23 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 따옴표 내부 문자열의 길이를 계산하는 함수
int	tok_quote_len(char *str, char quote)
{
	int	i;

	i = 1; // 따옴표 이후부터 탐색
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

// 일반 문자열의 길이를 계산하는 함수
// 연산자나 공백을 만나면 종료
int	tok_strlen(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(str);
	while (i < len)
	{
		if (str[i] == '\'')
			i += tok_quote_len(&(str[i]), '\'');
		else if (str[i] == '\"')
			i += tok_quote_len(&(str[i]), '\"');
		else if (tok_is_operator(str[i]) || (str[i] == ' ' || str[i] == '\t'))
			break ;
		i++;
	}
	return (i);
}

// 주어진 문자열이 차지하는 토큰 길이를 계산하는 함수
int	tok_get_len(char *str, t_tok_type type)
{
	if (type == HEREDOC || type == APPEND)
		return (2); // `<<`, `>>`는 두 글자
	else if (type == INFILE || type == OUTFILE || type == PIPE)
		return (1); // `<`, `>`, `|`는 한 글자
	else if (type == STRING)
		return (tok_strlen(str));
	return (0);
}

// 주어진 문자열의 토큰 타입을 결정하는 함수
t_tok_type	tok_get_type(char *str)
{
	if (str[0] == '<')
		return (str[1] == '<' ? HEREDOC : INFILE);  // `<<` 또는 `<`
	else if (str[0] == '>')
		return (str[1] == '>' ? APPEND : OUTFILE);  // `>>` 또는 `>`
	else if (str[0] == '|')
		return (PIPE);
	return (STRING);
}

// 해당 문자가 연산자인지 확인하는 함수
int	tok_is_operator(char c)
{
	int	found;

	found = 0;
	if (c == '|')
		found = 1;
	else if (c == '<')
		found = 2;
	else if (c == '>')
		found = 3;
	else if (c == '\"')
		found = 4;
	else if (c == '\'')
		found = 5;
	return (found);
}
