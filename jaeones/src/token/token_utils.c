/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:11:18 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/20 15:50:41 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 개별 토큰을 메모리에서 해제하는 함수
void	tok_free(t_token *token)
{
	if (token->value)
		free(token->value);
	free(token);
}

// 토큰 리스트 전체를 메모리에서 해제하는 함수
void	tok_free_list(t_token *token)
{
	t_token	*tmp;

	while (token != NULL)
	{
		tmp = token;
		token = token->next;
		tok_free(tmp);
	}
}

// 새로운 토큰을 생성하는 함수
// 문자열 value의 앞 n글자를 복사하여 토큰을 만듦
t_token	*tok_create(char *value, int n, t_tok_type type, t_data *data)
{
	t_token	*token;
	char	*new;

	token = malloc(sizeof(t_token));
	if (token == NULL)
		return (NULL);
	new = ft_strndup(value, n);
	if (!new)
	{
		free(token);
		return (NULL);
	}
	token->value = new;
	token->type = type;
	token->data = data;
	token->next = NULL;
	return (token);
}

/*
토큰 리스트에서 마지막 토큰을 찾는 함수
*/
t_token	*tok_get_last(t_token *token)
{
	while (token->next != NULL)
		token = token->next;
	return (token);
}

/*
새로운 토큰을 리스트 끝에 추가하는 함수
*/
int	tok_append(t_token **head, t_token *new)
{
	if (new == NULL)
		return (1);
	if (*head == NULL)
		*head = new;
	else
		tok_get_last(*head)->next = new;
	return (0);
}
