/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:07:50 by seong-ki          #+#    #+#             */
/*   Updated: 2024/10/24 15:39:23 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_token	*ft_new_token(char *value)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);		// malloc 할당 에러
	token->type = TOKEN_STRING;// enum으로 잘 적용. 아마 if else?
	// check_token_type(token, value);
	token->value = ft_strdup(value);//ft_strdup(str);
	free(value);
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*ft_tklast(t_token *tklst)
{
	t_token	*list_ptr;

	if (!tklst)
		return (NULL);
	list_ptr = tklst;
	while (list_ptr->next)
		list_ptr = list_ptr->next;
	return (list_ptr);
}

void	ft_token_add_back(t_token **tklst, t_token *new)
{
	t_token	*last_token;

	last_token = ft_tklast(*tklst);
	if (!new)
		return ;
	if (last_token)
	{
		new->prev = last_token;
		last_token->next = new;
	}
	else
	{
		new->prev = NULL;
		*tklst = new;
	}
	new->next = NULL;
	printf("token: -%s-\n", new->value);
}

int	ft_dollor_idx(char *s)
{
	int	i;
	int	single_flag;

	if (s == NULL)
		return (-1);
	single_flag = -1;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			single_flag *= -1;
		else if (single_flag != 1 && s[i] == '$')
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*fine_env_key(char *str)
{
	int		len;
	char	*env_name;

	len = 0;
	while (str[len] != '\0' && str[len] != ' ' && str[len] != '$' && str[len] != '\"' /* whitespace */)
		len++;
	env_name = malloc(sizeof(char) * len + 1);
	if (env_name == NULL)
		return (NULL);
	ft_strlcpy(env_name, str, len + 1);
	return (env_name);
}

char	*get_env_value(t_data *data, char *key)
{
	t_env	*env;

	env = data->env;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
			// return (env->key + (ft_strlen(key) + 1)); //이렇게 되면 반환값이 메모리가 어떻게 되는건지 모르겠음.
		// 이게 malloc이 되어있는건지 아니면 어떻게 메모리 릭이 안나는건지 너무 애매함.
		// 메모리 릭 안나면 너무 사기같은데 ...
		env = env->next;
	}
	return (ft_strdup(""));
}

void	change_env_vari(t_data *data, t_token **tklst)
{
	int		dollor_idx;
	char	*str;
	char	*ret;
	t_token	*inst_lst;

	inst_lst = *tklst;
	while (inst_lst)
	{
		dollor_idx = ft_dollor_idx(inst_lst->value);
		if (dollor_idx >= 0)
		{
			ret = ft_substr(inst_lst->value, 0, dollor_idx - 1); // ret malloc됨.
			// 1. 첫번째 dollor 전까지 str에 복사.
			// printf("value: %s\n", get_env_key(inst_lst->value + dollor_idx));
			// 2. dollor 환경변수 값 조회 후 join.
			str = ret;
			ret = ft_strjoin(ret, get_env_value(data, fine_env_key(inst_lst->value + dollor_idx)));
			free(str);
			// 3. 남은 dollor 확인하러 아래의 while문 입장.
			while (1)
			{
				// 5. dollor가 더 이상 없으면 break;
				if (ft_dollor_idx(inst_lst->value + dollor_idx) == -1)
					break;
				else {
					dollor_idx += ft_dollor_idx(inst_lst->value + dollor_idx);
					str = ret;
					ret = ft_strjoin(ret, get_env_value(data, fine_env_key(inst_lst->value + dollor_idx)));
					free(str);
					// 4. dollor 환경변수 값 조회 후 str에 join.
					// printf("value: %s\n", get_env_key(inst_lst->value + dollor_idx));
				}
			}
			printf("return: -%s-\n", ret);
			free(ret);
		}
		inst_lst = inst_lst->next;
	}
	// 6. break 후 inst_lst->value를 str로 update;
	// return (ret);
}


// to-do
// 1. 양 끝에 있는 쿼트 제거 함수 구현
// 2. enum TOKEN 정해주는 함수 구현
// 3. 재귀 하향 파싱 구현
// 4. AST 구현
// 파싱 끝~
// test 생성
void	remove_quote(t_token **tklst)
{
	t_token	*inst_lst;

	inst_lst = *tklst;
	while (inst_lst)
	{
		if (inst_lst->token == TOKEN_STRING)
		{
			// new token->value(str) malloc -> ft_strtrim
			// current token->value(str) free -> free()
			// token change
		}
		inst_lst = inst_lst->next;
	}
}

void	handle_quote_token(char *input, int *idx, int *start, t_token **tklst, char quote)
{
	t_token	*token;

	// 앞 문자열을 토큰화
	if (*idx != *start)
	{
		token = ft_new_token(ft_substr(input, *start, *idx - *start));
		ft_token_add_back(tklst, token);
	}
	// 따옴표로 묶인 문자열을 처리
	*start = (*idx)++;
	while (input[*idx] && input[*idx] != quote)
		(*idx)++;
	if (input[*idx] == quote)
	{
		token = ft_new_token(ft_substr(input, *start, *idx - *start + 1));
		ft_token_add_back(tklst, token);
		*start = (*idx) + 1;
		(*idx)++;
	}
	else
	{
		printf("Error: Unclosed quote detected.\n");
		// 에러 처리
	}
}

t_token*	tokenize(t_data *data, char *input)
{
	int	idx;
	int	start;
	t_token	*tklst;

	tklst = NULL;
	idx = 0;
	start = 0;

	while (input[idx])
	{
		// 공백 처리
		if (input[idx] == ' '/* && start != 0 && input[idx + 1] != '\0'*/)
		{
			if (idx != start)
				ft_token_add_back(&tklst, ft_new_token(ft_substr(input, start, idx - start)));
			while (input[idx] == ' ') idx++;
			ft_token_add_back(&tklst, ft_new_token(ft_strdup(" ")));
			start = idx;
		}
		// 따옴표 처리
		else if (input[idx] == '\'' || input[idx] == '\"')
			handle_quote_token(input, &idx, &start, &tklst, input[idx]);
		// 연속된 특수 문자 처리 (<<, >>)
		else if (!ft_strncmp(input + idx, "<<", 2) || !ft_strncmp(input + idx, ">>", 2))
		{
			if (idx != start)
				ft_token_add_back(&tklst, ft_new_token(ft_substr(input, start, idx - start)));
			ft_token_add_back(&tklst, ft_new_token(ft_substr(input, idx, 2)));
			start = (idx += 2);
		}
		// 단일 특수 문자 처리 (<, >, |)
		else if (input[idx] == '<' || input[idx] == '>' || input[idx] == '|')
		{
			if (idx != start)
				ft_token_add_back(&tklst, ft_new_token(ft_substr(input, start, idx - start)));
			ft_token_add_back(&tklst, ft_new_token(ft_substr(input, idx, 1)));
			start = ++idx;
		}
		// 일반 문자열
		else
			idx++;
	}
	// 마지막 남은 문자열 처리
	if (idx != start)
		ft_token_add_back(&tklst, ft_new_token(ft_substr(input, start, idx - start)));

	change_env_vari(data, &tklst);
	return (tklst);
}
//
// int	count_special_character(t_data *data, char *input)
// {
// 	int	idx;
// 	int	start;
// 	int len;
// 	t_token	*token;
// 	t_token	*tklst;
//
// 	tklst = NULL;
// 	idx = 0;
// 	start = 0;
// 	len = (int)ft_strlen(input);
// 	while (input[idx])
// 	{
// 		printf("len-idx-start: %zu-%d-%d\n", ft_strlen(input), idx, start);
// 		printf("condition: %d\n", input[idx] == '\"' && (idx != 0 && start < len));
// 		if (input[idx] == ' ' && (idx != 0 && idx != len))
// 		{
// 			token = ft_new_token(ft_substr(input, start, idx - start));
// 			ft_token_add_back(&tklst, token);
// 			start = idx;
// 			while (input[idx] == ' ')
// 				idx++;
// 			token = ft_new_token(ft_strdup(" "));
// 			ft_token_add_back(&tklst, token);
// 			start = idx;
// 		}
// 		else if (input[idx] == '\'' && (idx != 0 && start < len))
// 		{
// 			token = ft_new_token(ft_substr(input, start, idx - start));
// 			ft_token_add_back(&tklst, token);
// 			start = idx;
// 			while (input[++idx] != '\'')
// 				continue ;
// 			token = ft_new_token(ft_substr(input, start, idx - start + 1));
// 			ft_token_add_back(&tklst, token);
// 			start = idx + 1;
// 		}
// 		else if (input[idx] == '\"' && (idx != 0 && start < len))
// 		{
// 			token = ft_new_token(ft_substr(input, start, idx - start));
// 			ft_token_add_back(&tklst, token);
// 			start = idx;
// 			while (input[++idx] != '\"')
// 				continue ;
// 			token = ft_new_token(ft_substr(input, start, idx - start + 1));
// 			ft_token_add_back(&tklst, token);
// 			start = idx + 1;
// 		}
// 		if ((!ft_strncmp(input + idx, "<<", 2) || !ft_strncmp(input + idx, ">>", 2)))
// 		{
// 			if (idx != start)
// 			{
// 				token = ft_new_token(ft_substr(input, start, idx - start));
// 				ft_token_add_back(&tklst, token);
// 			}
// 			token = ft_new_token(ft_substr(input, idx, 2));
// 			ft_token_add_back(&tklst, token);
// 			start = idx + 2;
// 			idx = idx + 2;
// 		}
// 		else if ((!ft_strncmp(input + idx, "<", 1) || !ft_strncmp(input + idx, ">", 1) || !ft_strncmp(input + idx, "|", 1)))
// 		{
// 			if (idx != start)
// 			{
// 				token = ft_new_token(ft_substr(input, start, idx - start));
// 				ft_token_add_back(&tklst, token);
// 			}
// 			token = ft_new_token(ft_substr(input, idx, 1));
// 			ft_token_add_back(&tklst, token);
// 			start = idx + 1;
// 			idx = idx + 1;
// 		}
// 		// else if ((input[idx] == ' ')/*나중에 화이트 스페이스로 변경.*/)
// 		// {
// 		// 	if (idx != start)
// 		// 	{
// 		// 		token = ft_new_token(ft_substr(input, start, idx - start));
// 		// 		ft_token_add_back(&tklst, token);
// 		// 	}
// 		// 	start = idx + 1;
// 		// 	idx = idx + 1;
// 		// }
// 		else
// 			idx = idx + 1;
// 	}
// 	token = ft_new_token(ft_substr(input, start, idx - start));
// 	ft_token_add_back(&tklst, token);
//
// 	// if (single_flag == 1 || double_flag == 1)
// 	// 	return (-1);
//
// 	change_env_vari(data, &tklst);
// 	return (1);
// }


//
// void	read_input(char *input)
// {
// 	int	i;
//
// 	i = 0;
// 	while (input[i])
// 	{
// 		printf("%c\n", input[i]);
// 		if (strncmp(input + i, "<<", 2) == 0)
// 			printf("heredoc!!\n");
// 		else if (strncmp(input + i, ">>", 2) == 0)
// 			printf("redirection!!\n");
// 		else if (input[i] == '>' || input[i] == '<')
// 			printf("redirection!!\n");
// 		else if (input[i] == '|')
// 			printf("pipe!!\n");
// 		else if (input[i] == '\'' || input[i] == '\"')
// 			printf("qoute!!\n");
// 		i++;
// 	}
// 	return ;
// }

