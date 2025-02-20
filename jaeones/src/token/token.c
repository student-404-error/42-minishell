/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:11:13 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/20 15:54:37 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
주어진 문자열에서 토큰을 추출하는 함수
토큰의 길이와 타입을 결정하고 새로운 토큰을 생성함
*/
t_token	*tok_get_token(char *str, t_data *data)
{
	t_token			*new;
	t_tok_type	type;
	int				len;

	new = NULL;
	type = tok_get_type(str); // 현재 문자열에서 토큰 타입 판별
	len = tok_get_len(str, type); // 해당 토큰의 길이 계산
	new = tok_create(str, len, type, data); // 토큰 생성
	return (new);
}

//토큰 메인 함수
t_token	*tokenize(t_data *data, char *line)
{
	t_token	*token_list;
	t_token	*new_token;
	int		i;

	i = 0;
	token_list = NULL;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t') // 공백이 아닌 경우에만 처리
		{
			new_token = tok_get_token(&(line[i]), data); // 현재 위치에서 토큰 생성
			if (new_token == NULL) // 메모리 할당 실패 시 기존 토큰 해제 후 NULL 반환
			{
				tok_free_list(token_list);
				return (NULL);
			}
			tok_append(&(token_list), new_token); // 생성된 토큰을 리스트에 추가
			i += ft_strlen(new_token->value); // 토큰의 길이만큼 인덱스 증가
		}
		else
			i++; // 공백이면 다음 문자로 이동
	}
	return (token_list); // 생성된 토큰 리스트 반환
}
