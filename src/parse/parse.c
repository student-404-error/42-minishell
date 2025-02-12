/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:07:50 by seong-ki          #+#    #+#             */
/*   Updated: 2025/01/24 18:39:54 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_env_variable(char *value)
{
	// If value is not env_variable, It will return 0.
	// If value begin with single quote -> return 0.
	// And if doesn't exist dollor sign, return 0.
	if (*value == '\'')
		return (0);
	// Else check all characters and if dollor is found, return 1.
	// If value is env_variable, It will return 1.
	if (ft_strchr(value, '$') != NULL) // If return NULL -> can't find
		return (1);
	return (0);
}

void check_state_after_space(t_tokenizer *state, t_token *last_token)
{
	if (last_token->prev == NULL || (last_token->prev->type == TOKEN_PIPE))
		state->after_operator = 1; // Command expected
	else if (last_token->prev->type == TOKEN_REDIRECTION_IN ||
			 last_token->prev->type == TOKEN_REDIRECTION_OUT ||
			 last_token->prev->type == TOKEN_REDIRECTION_APPEND)
		state->after_operator = 2; // Filename expected
	else if (last_token->prev->type == TOKEN_HEREDOC)
		state->after_operator = 3; // EOF expected
	else
		state->after_operator = 0; // No special state
}

void check_state(t_tokenizer *state)
{
	t_token *last_token;

	if (state->tklst == NULL)
		return ;

	last_token = ft_tklast(state->tklst);

	if (last_token->type == TOKEN_SPACE && state->is_first_token == 0)
		check_state_after_space(state, last_token);
	else if (last_token->type == TOKEN_PIPE)
		state->after_operator = 1;
	else if (last_token->type == TOKEN_REDIRECTION_IN ||
			 last_token->type == TOKEN_REDIRECTION_OUT ||
			 last_token->type == TOKEN_REDIRECTION_APPEND)
		state->after_operator = 2;
	else if (last_token->type == TOKEN_HEREDOC)
		state->after_operator = 3;
	else
		state->after_operator = 0;
}

e_token_type check_token_directly(char *value)
{
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strcmp(value, "<") == 0)
		return (TOKEN_REDIRECTION_IN);
	else if (ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIRECTION_OUT);
	else if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIRECTION_APPEND);
	else if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(value, " ") == 0)
		return (TOKEN_SPACE);
	else
		return (TOKEN_UNKNOWN); // 안전한 처리
}

e_token_type check_token_type(char *value, t_tokenizer *state)
{
	e_token_type direct_type = check_token_directly(value);
	if (direct_type != TOKEN_UNKNOWN)
		return (direct_type);

	// Handle dynamic or state-dependent tokens
	if (is_env_variable(value))
		return (TOKEN_ENV_VARI);
	else if (state->after_operator == 3)
		return (TOKEN_EOF);
	else if (state->after_operator == 2)
		return (TOKEN_FILENAME);
	else if (state->is_first_token || state->after_operator == 1)
		return (TOKEN_COMMAND);
	else
		return (TOKEN_STRING);
}

/*
e_token_type check_token_type(char *value, t_tokenizer *state)
{
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_HEREDOC);
	else if (ft_strcmp(value, "<") == 0 || ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIRECTION);
	else if (ft_strcmp(value, "&&") == 0 || ft_strcmp(value, "||") == 0)
		return (TOKEN_OPERATOR);
	else if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIRECTION_APPEND);
	else if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(value, " ") == 0)
		return (TOKEN_SPACE);

	// 첫 번째 토큰 또는 연산자 이후의 토큰은 명령어
	if (is_env_variable(value))
		return (TOKEN_ENV_VARI);
	if (state->after_operator == 3)
		return (TOKEN_EOF);
	if (state->after_operator == 2)
		return (TOKEN_FILENAME);
	if (state->is_first_token || state->after_operator == 1)
		return (TOKEN_COMMAND);

	// 기본적으로 일반 문자열
	return (TOKEN_STRING);
}*/

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
	// ft_strdup 안해도 됨.
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

char	*find_env_key(char *str)
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

	if (ft_strcmp(key, "") == 0)
		return (ft_strdup("$"));
	env = data->env;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (ft_strdup(env->value));
			// return (env->key + (ft_strlen(key) + 1)); //이렇게 되면 반환값이 메모리가 어떻게 되는건지 모르겠음.
		env = env->next;
	}
	return (ft_strdup(""));
}

void	change_env_vari(t_data *data, t_token **tklst)
{
	int		dollor_idx;
	char	ret[2048];
	t_token	*inst_lst;

	inst_lst = *tklst;
	while (inst_lst)
	{
		ft_memset(ret, 0, sizeof(ret));
		// "$" <- 이 입력이 들어오면 그냥 "$"가 되어야함.
		// 지금 내 코드는 맨 앞의 "만 저장함
		// 지금 해줘야할 것은 $만 있으면 환경변수가 아닌 $로 냅두는 기능
		// "$PATH dfkj"일 때 dfkj를 뒤에 붙여주는 기능
		// 두개를 만들어야함.
		dollor_idx = ft_dollor_idx(inst_lst->value);
		if (dollor_idx >= 0)
		{
			ft_strlcpy(ret, inst_lst->value, dollor_idx - 1);
			// 1. 첫번째 dollor 전까지 str에 복사.
			// printf("value: %s\n", get_env_key(inst_lst->value + dollor_idx));
			// 2. dollor 환경변수 값 조회 후 join.
			ft_strlcpy(ret + ft_strlen(ret), get_env_value(data, find_env_key(inst_lst->value + dollor_idx)), sizeof(ret) - ft_strlen(ret));
			// 3. 남은 dollor 확인하러 아래의 while문 입장.
			while (1)
			{
				// 5. dollor가 더 이상 없으면 break;
				if (ft_dollor_idx(inst_lst->value + dollor_idx) == -1)
					break;
				else {
					dollor_idx += ft_dollor_idx(inst_lst->value + dollor_idx);
					ft_strlcpy(ret + ft_strlen(ret), get_env_value(data, find_env_key(inst_lst->value + dollor_idx)), sizeof(ret) - ft_strlen(ret));
					// 4. dollor 환경변수 값 조회 후 str에 join.
					// printf("value: %s\n", get_env_key(inst_lst->value + dollor_idx));
				}
			}
			while (*(inst_lst->value + dollor_idx) != ' ')
				dollor_idx++;
			ft_strlcpy(ret + ft_strlen(ret), inst_lst->value + dollor_idx, ft_strlen(inst_lst->value));
			// 남은 문자열 다 넣기.
			free(inst_lst->value);
			inst_lst->value = ft_strdup(ret);
		}
		inst_lst = inst_lst->next;
	}
	// 6. break 후 inst_lst->value를 str로 update;
	// return (ret);
}

//
// void	change_env_vari(t_data *data, t_token **tklst)
// {
// 	int		dollor_idx;
// 	char	*str;
// 	char	*ret;
// 	t_token	*inst_lst;
//
// 	inst_lst = *tklst;
// 	while (inst_lst)
// 	{
// 		// "$" <- 이 입력이 들어오면 그냥 "$"가 되어야함. 
// 		// 지금 내 코드는 맨 앞의 "만 저장함
// 		// 지금 해줘야할 것은 $만 있으면 환경변수가 아닌 $로 냅두는 기능
// 		// "$PATH dfkj"일 때 dfkj를 뒤에 붙여주는 기능
// 		// 두개를 만들어야함.
// 		dollor_idx = ft_dollor_idx(inst_lst->value);
// 		if (dollor_idx >= 0)
// 		{
// 			ret = ft_substr(inst_lst->value, 0, dollor_idx - 1); // ret malloc됨.
// 			// 1. 첫번째 dollor 전까지 str에 복사.
// 			// printf("value: %s\n", get_env_key(inst_lst->value + dollor_idx));
// 			// 2. dollor 환경변수 값 조회 후 join.
// 			str = ret;
// 			ret = ft_strjoin(ret, get_env_value(data, find_env_key(inst_lst->value + dollor_idx)));
// 			free(str);
// 			// 3. 남은 dollor 확인하러 아래의 while문 입장.
// 			while (1)
// 			{
// 				// 5. dollor가 더 이상 없으면 break;
// 				if (ft_dollor_idx(inst_lst->value + dollor_idx) == -1)
// 					break;
// 				else {
// 					dollor_idx += ft_dollor_idx(inst_lst->value + dollor_idx);
// 					str = ret;
// 					ret = ft_strjoin(ret, get_env_value(data, find_env_key(inst_lst->value + dollor_idx)));
// 					free(str);
// 					// 4. dollor 환경변수 값 조회 후 str에 join.
// 					// printf("value: %s\n", get_env_key(inst_lst->value + dollor_idx));
// 				}
// 			}
// 			printf("return: =%s=\n", ret);
// 			// 남은 문자열 다 넣기.
//
// 			free(inst_lst->value);
// 			inst_lst->value = ret;
// 		}
// 		inst_lst = inst_lst->next;
// 	}
// 	// 6. break 후 inst_lst->value를 str로 update;
// 	// return (ret);
// }
//
//
// to-do
// 1. 양 끝에 있는 쿼트 제거 함수 구현 ->> 구현 완료.
// 2. enum TOKEN 정해주는 함수 구현    ->> 구현 완료.
// 2.5 치환해야하는 환경 변수인지 아닌지 구분하는 변수를 넣어둬야함.
// 일단 지금 어케 나누지? 와우 이거 또 복잡해지나?
// 아니 근데 일단 그냥
// 큰 따옴표 안에 들어있으면 무조건 환경변수 몇개든간에 1이고
// 그냥 환경변수만 따로 있으면 그냥 1이고
// 작은 따옴표(문자열취급)만 0이면 되는거고.
// 나머지, 환경변수가 아닌 것들은 바꾸지 않으면 되는거니까
// 그러면 그냥 모든 토큰 반복하면서 (스페이스 건너뜀)
// 아니면 이렇게 하지말고 그냥 enum type을 새로 하나 만들어서
// TOKEN_ENV_VARI로 만든다음에 위와 동일하게 1인경우 type설정만 해주고
// 실행 파트일 때 그냥 type만 보고 변경하든 말든 하면 될 듯 한데?
//
// 아마 enum타입을 새로 만들 듯?
//
// 추가 구현 함수
// 1. 환경변수 치환해야하는지 검사하는 함수 구현 완료
//
// 2. 에러 검사 함수
// 3. free함수
// 4. 재귀 하향 파싱 함수
// 5. AST구현 함수
//

/*
 * [x]모든 토큰 반복하면서 '," 제거하기
 * 제거 한 후
 * 모든 토큰 반복하면서 커맨드, 스트링 이어붙이기
 * 이어 붙인 후
 * 모든 토큰 반복하면서 공백 제거? ** 미정
 *
 * ->
 * 에러 검사.
 *
 *
 * 
 */

// 공백 토큰 제거를 먼저 하느냐. 아니면 나중에 하느냐 아예 안 하느냐.

t_token	*ft_print_tokens(t_token *tklst)
{
	t_token	*list_ptr;

	if (!tklst)
		return (NULL);
	list_ptr = tklst;
	printf("\n\n===========RESULT===========\n");
	while (list_ptr)
	{
		printf("lexing: token: %s | type: %d\n", list_ptr->value, list_ptr->type);
		list_ptr = list_ptr->next;
	}
	printf("\n\n");
	return (list_ptr);
}

void	join_cmd_str(t_token **tklst)
{
	t_token	*now_token;
	t_token	*prev_token;
	char	*new_str;

	now_token = (*tklst)->next;
	if (now_token != NULL)
		prev_token = now_token->prev;
	else
		prev_token = NULL;
	while (now_token)
	{
		if (prev_token && prev_token->type < 3 && now_token->type < 3)
		{
			new_str = ft_strjoin(prev_token->value, now_token->value);
			if (prev_token->prev == NULL)
			{
				*tklst = now_token;
				now_token->prev = NULL;
			}
			else
			{
				prev_token->prev->next = now_token;
				now_token->prev = prev_token->prev;
			}
			free(prev_token->value);
			now_token->type = prev_token->type; 
			free(prev_token);
			free(now_token->value);
			now_token->value = new_str;
		}
		prev_token = now_token;
		now_token = now_token->next;
	}
}

void	remove_quote(t_token **tklst)
{
	t_token	*inst_lst;
	char	*new_value;

	inst_lst = *tklst;
	while (inst_lst)
	{
		if (inst_lst->type < 3)
		{
			if (inst_lst->value[0] == '\'' || inst_lst->value[0] == '\"')	
			{
				new_value = ft_substr(inst_lst->value, 1, ft_strlen(inst_lst->value) - 2);
				free(inst_lst->value);
				inst_lst->value = new_value;
			}
			printf("remove_quote: %s\n", inst_lst->value);
		}
		inst_lst = inst_lst->next;
	}
}

// idx, start, tklst -> state->* change;
void	handle_quote_token(char *input, t_tokenizer *state)
{
	char	quote;
	t_token	*token;

	quote = input[state->idx];  // Current quote character
	if (state->idx != state->start)
	{
		token = ft_new_token(ft_substr(input, state->start, state->idx - state->start), state);
		ft_token_add_back(&state->tklst, token);
	}

	state->start = ++state->idx;  // Skip the opening quote
	while (input[state->idx] && input[state->idx] != quote)
	state->idx++;

	if (input[state->idx] == quote)
	{
		token = ft_new_token(ft_substr(input, state->start - 1, state->idx - state->start + 2), state);
		ft_token_add_back(&state->tklst, token);
		state->start = ++state->idx;  // Move past the closing quote
	}
	else
		printf("Error: Unclosed quote detected.\n");
}
/*
void	check_state(t_tokenizer *state)
{
	t_token	*last_token;

	if (state->tklst == NULL)
		return ;
	last_token = ft_tklast(state->tklst);
	if (last_token->type == TOKEN_SPACE && state->is_first_token == 0)
	{
		if (last_token->prev == NULL || (last_token->prev->type >= 4 || last_token->prev->type <= 6))
			state->after_operator = 1; // bigyo
		else if (last_token->prev == NULL || last_token->prev->type >= 7 || last_token->prev->type <= 9) // last_token->prev == NULL은 굳이 여기선 비교 안해도 될 듯
			state->after_operator = 2;
		else if (last_token->prev == NULL || last_token->prev->type == 10)
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
*/
t_token* tokenize(t_data *data, char *input)
{
	t_tokenizer state;

	state.idx = 0;
	state.start = 0;
	state.is_first_token = 1;
	state.after_operator = 0;
	state.tklst = NULL;
	while (input[state.idx])
	{
		// 공백 처리
		if ((input[state.idx] >= 9 && input[state.idx] <= 13) || input[state.idx] == ' '/* && input[idx + 1] != '\0'*/)
		{
			if (state.idx != state.start)
				ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));
			while ((input[state.idx] >= 9 && input[state.idx] <= 13) || input[state.idx] == ' ') state.idx++;
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
	change_env_vari(data, &state.tklst);
	remove_quote(&state.tklst);
	join_cmd_str(&state.tklst);
	ft_print_tokens(state.tklst);
    // 환경 변수 치환 처리 -> 실행 파트에서 치환 하는 걸로.
	// 환경변수 치환 처리 실행파트에서 하려고 했는데그냥 파싱에서 하고 넘겨도 될 듯 함
	// 보너스파트 안 할거면 그냥 실행에서 하든지 파싱파트에서 하든지 아무상관없을듯
	// 보너스파트 안할거니까 그냥 넘기기.
	// 바로 ast만들어서 넘겨주기
	return (state.tklst);
}
//
// t_token*	tokenize(t_data *data, char *input)
// {
// 	t_tokenizer	state;
//
// 	state.idx = 0;
// 	state.start = 0;
// 	state.is_first_token = 1;
// 	state.after_operator = 0;
// 	state.tklst = NULL;
// 	while (input[state.idx])
// 	{
// 		// 공백 처리
// 		if (input[state.idx] == ' '/* && input[idx + 1] != '\0'*/)
// 		{
// 			if (state.idx != state.start)
// 				ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));
// 			while (input[state.idx] == ' ') state.idx++;
// 			ft_token_add_back(&state.tklst, ft_new_token(ft_strdup(" "), &state));
// 			state.start = state.idx;
// 		}
// 		// 따옴표 처리
// 		else if (input[state.idx] == '\'' || input[state.idx] == '\"')
// 			handle_quote_token(input, &state);
// 		// 연속된 특수 문자 처리 (<<, >>)
// 		else if (!ft_strncmp(input + state.idx, "<<", 2) || !ft_strncmp(input + state.idx, ">>", 2))
// 		{
// 			if (state.idx != state.start)
// 				ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));
// 			ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.idx, 2), &state));
// 			state.start = (state.idx += 2);
// 		}
// 		// 단일 특수 문자 처리 (<, >, |)
// 		else if (input[state.idx] == '<' || input[state.idx] == '>' || input[state.idx] == '|')
// 		{
// 			if (state.idx != state.start)
// 				ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));
// 			ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.idx, 1), &state));
// 			state.start = ++state.idx;
// 		}
// 		// 일반 문자열
// 		else
// 			state.idx++;
// 		// change is_first_token, after_operator here
// 		// 상태 관리: 연산자 후에는 명령어가 와야 함
// 		check_state(&state);
// 	}
//     // 마지막 남은 문자열 처리
// 	if (state.idx != state.start)
// 		ft_token_add_back(&state.tklst, ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));
// 	remove_quote(&state.tklst);
// 	join_cmd_str(&state.tklst);
// 	ft_print_tokens(state.tklst);
//     // 환경 변수 치환 처리 -> 실행 파트에서 치환 하는 걸로.
// 	// 환경변수 치환 처리 실행파트에서 하려고 했는데그냥 파싱에서 하고 넘겨도 될 듯 함
// 	//
// 	// 보너스파트 안 할거면 그냥 실행에서 하든지 파싱파트에서 하든지 아무상관없을듯
// 	// 보너스파트 안할거니까 그냥 넘기기.
// 	// 바로 ast만들어서 넘겨주기
// 	//
// 	// change_env_vari(data, &state.tklst);
// 	printf("%d\n", data->last_ret);
// 	return (state.tklst);
// }
