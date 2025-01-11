/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:07:50 by seong-ki          #+#    #+#             */
/*   Updated: 2024/12/30 18:19:59 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

e_token_type check_token_type(char *value, t_tokenizer *state) {
    // 연산자는 항상 고유한 타입
    if (ft_strcmp(value, "<<") == 0)
        return (TOKEN_HEREDOC);
    else if (ft_strcmp(value, "<") == 0 || ft_strcmp(value, ">") == 0)
        return (TOKEN_REDIRECTION);
    else if (ft_strcmp(value, ">>") == 0)
        return (TOKEN_REDIRECTION_APPEND);
    else if (ft_strcmp(value, "|") == 0)
        return (TOKEN_PIPE);
	else if (ft_strcmp(value, " ") == 0)
		return (TOKEN_SPACE);

    // 첫 번째 토큰 또는 연산자 이후의 토큰은 명령어
	if (state->after_operator == 3)
		return (TOKEN_EOF);
	if (state->after_operator == 2)
		return (TOKEN_FILENAME);
    if (state->is_first_token || state->after_operator == 1)
        return (TOKEN_COMMAND);

    // 기본적으로 일반 문자열
    return (TOKEN_STRING);
}

t_token	*ft_new_token(char *value, t_tokenizer *state)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);		// malloc 할당 에러
	token->type = check_token_type(value, state);
	state->is_first_token = 0;
	token->value = ft_strdup(value); // 여기서 strdup안 쓰고 그냥 value 할당 후 free해도 될 수도.
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
	printf("token: -%s- type : -%u-\n", new->value, new->type);
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

// void	remove_quote(t_token **tklst)
// {
// 	t_token	*inst_lst;
//
// 	inst_lst = *tklst;
// 	while (inst_lst)
// 	{
// 		if (inst_lst->type < 2)
// 		{
// 			if (inst_lst->value[0] == '\'' || inst_lst->value[0] == '\"')	
// 			{
// 				// free(inst_lst->value);
// 				// inst_lst->value = ft_strtrim();
// 			}
// 			// new token->value(str) malloc -> ft_strtrim
// 			// current token->value(str) free -> free()
// 			// token change
// 		}
// 		inst_lst = inst_lst->next;
// 	}
// }

// idx, start, tklst -> state->* change;
void handle_quote_token(char *input, t_tokenizer *state) {
    char quote = input[state->idx];  // Current quote character
    t_token *token;

    // Tokenize the substring before the quote
    if (state->idx != state->start) {
        token = ft_new_token(ft_substr(input, state->start, state->idx - state->start), state);
        ft_token_add_back(&state->tklst, token);
    }

    // Process the quoted string
    state->start = ++state->idx;  // Skip the opening quote
    while (input[state->idx] && input[state->idx] != quote)
        state->idx++;

    if (input[state->idx] == quote) {
        token = ft_new_token(ft_substr(input, state->start - 1, state->idx - state->start + 2), state);
        ft_token_add_back(&state->tklst, token);
        state->start = ++state->idx;  // Move past the closing quote
    } else {
        printf("Error: Unclosed quote detected.\n");
        // Handle error appropriately (e.g., set error flag in state or exit)
    }
}

void	check_state(t_tokenizer *state)
{
	t_token *last_token;

	if (state->tklst == NULL)
		return ;
	last_token = ft_tklast(state->tklst);
	if (last_token->type == TOKEN_SPACE && state->is_first_token == 0)
	{
		if (last_token->prev == NULL || (last_token->prev->type == 4 || last_token->prev->type == 5))
			state->after_operator = 1; // bigyo
		else if (last_token->prev == NULL || last_token->prev->type == 6 || last_token->prev->type == 7)
			state->after_operator = 2;
		else if (last_token->prev == NULL || last_token->prev->type == 8)
			state->after_operator = 3;
		else
			state->after_operator = 0;
	}
	else if (last_token->type == 4 || last_token->type == 5) // STRING or COMMAND
		state->after_operator = 1;
	else if (last_token->type == 6 || last_token->type == 7)
		state->after_operator = 2;
	else if (last_token->type == 8)
		state->after_operator = 3;							// TOKEN_EOF
	else
		state->after_operator = 0;
}

t_token*	tokenize(t_data *data, char *input)
{
	t_tokenizer	state;

	state.idx = 0;
	state.start = 0;
	state.is_first_token = 1;
	state.after_operator = 0;
	state.tklst = NULL;
	while (input[state.idx])
	{
		// 공백 처리
		if (input[state.idx] == ' '/* && input[idx + 1] != '\0'*/)
		{
			if (state.idx != state.start)
				ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));
			while (input[state.idx] == ' ') state.idx++;
			ft_token_add_back(&state.tklst, ft_new_token(ft_strdup(" "), &state));
			state.start = state.idx;
		}
		// 따옴표 처리
		else if (input[state.idx] == '\'' || input[state.idx] == '\"')
			handle_quote_token(input, &state);
		// 연속된 특수 문자 처리 (<<, >>)
		else if (!ft_strncmp(input + state.idx, "<<", 2) || !ft_strncmp(input + state.idx, ">>", 2))
		{
			if (state.idx != state.start)
				ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));
			ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.idx, 2), &state));
			state.start = (state.idx += 2);
		}
		// 단일 특수 문자 처리 (<, >, |)
		else if (input[state.idx] == '<' || input[state.idx] == '>' || input[state.idx] == '|')
		{
			if (state.idx != state.start)
				ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));
			ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.idx, 1), &state));
			state.start = ++state.idx;
		}
		// 일반 문자열
		else
			state.idx++;
		// change is_first_token, after_operator here
		// 상태 관리: 연산자 후에는 명령어가 와야 함
		check_state(&state);
	}
    // 마지막 남은 문자열 처리
    if (state.idx != state.start)
        ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));

    // 환경 변수 치환 처리
    change_env_vari(data, &state.tklst);
	return (state.tklst);
}
