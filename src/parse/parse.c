/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:07:50 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 16:06:56 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_env_variable(char *value)
{
	if (*value == '\'')
		return (0);
	if (ft_strchr(value, '$') != NULL) 
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

t_token_type check_token_type(char *value, t_tokenizer *state)
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
	else if (is_env_variable(value))
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

int	get_dollar_idx(char *s)
{
	int	i;

	if (s == NULL)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_env_key(char *str)
{
	int	len;
	char	*key;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
		len++;
	key = malloc(sizeof(char) * len + 1);
	if (key == NULL)
		return (NULL);
	ft_strlcpy(key, str, len + 1);
	return (key);
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
		env = env->next;
	}
	return (ft_strdup(""));
}

int	get_env_value_len(t_data *data, char *key)
{
	t_env	*env;

	if (ft_strcmp(key, "") == 0)
		return (0);
	env = data->env;
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env->len);
		env = env->next;
	}
	return (-1);
}

int	count_total_length(t_data *data, char *token)
{
	int	length;
	int	idx;
	char	*key;

	idx = -1;
	length = 0;
	while (get_dollar_idx(token + idx + 1) != -1)
	{
		length += get_dollar_idx(token + idx + 1);
		idx += get_dollar_idx(token + idx + 1) + 1;
		key = get_env_key(token + idx + 1);
		length += get_env_value_len(data, key);
		idx += ft_strlen(key);
		free(key);
	}
	return (length);
}
char	*expand_env_vari(t_data *data, char *token)
{
	char	*ret;
	char	*key;
	char	*value;
	int	start;
	int	idx;

	ret = malloc(sizeof(char) * (count_total_length(data, token) + 1));
	if (ret == NULL)
		return (NULL);
	ft_bzero(ret, count_total_length(data, token) + 1);
	start = -1;
	idx = -1;
	while (get_dollar_idx(token + start + 1) != -1)
	{
		printf("dollar: %d\n", get_dollar_idx(token + start + 1));
		idx = get_dollar_idx(token + start + 1);
		printf("idx: %d\n", idx);
		key = ft_substr(token, start + 1, idx);
		printf("key: %s\n", key);
		ft_strlcpy(ret + ft_strlen(ret), key, idx + 1);
		free(key);
		key = get_env_key(token + start + idx + 2);
		printf("key: %s\n", key);
		value = get_env_value(data, key);
		printf("value: %s\n", value);
		ft_strlcpy(ret + ft_strlen(ret), value, ft_strlen(value) + 1);
		start += idx + ft_strlen(key) + 1;
		printf("start: %d\n", start);
		free(key);
		free(value);
	}
	return (ret);
}
void	change_env_vari(t_data *data, t_token **tklst)
{
	t_token	*inst_lst;
	char	*old_str;

	inst_lst = *tklst;
	while (inst_lst)
	{
		if (inst_lst->type == 9)
		{
			old_str = inst_lst->value;
			inst_lst->value = expand_env_vari(data, old_str);
			free(old_str);
		}
		inst_lst = inst_lst->next;
	}
}

void print_ast(t_ast_node *node, int level)
{
	if (!node)
		return;
	
	for (int i = 0; i < level; i++)
		printf("  ");
	
	// 노드 타입과 값 출력
	printf("[%d] %s\n", node->type, node->value ? node->value : "NULL");
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

t_ast_node	*new_ast_node(t_ast_node_type type, char *value, t_ast_node *left, t_ast_node *right)
{
	t_ast_node *node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		fprintf(stderr, "Memory allocation error in new_ast_node\n");
		exit(EXIT_FAILURE);
	}
	node->type = type;
	if (value)
	{
		node->value = ft_strdup(value);
		if (!node->value)
		{
			fprintf(stderr, "Memory allocation error in new_ast_node (value)\n");
			exit(EXIT_FAILURE);
		}
	}
	else
		node->value = NULL;
	node->left = left;
	node->right = right;
	return (node);
}


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
		if (inst_lst->type < 3 || inst_lst->type == 9)
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

int	handle_quote_token(t_tokenizer *state, char *input)
{
	char	quote;
	t_token	*token;

	if (input[state->idx] == '\'' || input[state->idx] == '"')
	{
		quote = input[state->idx];
		if (state->idx != state->start)
		{
			token = ft_new_token(ft_substr(input, state->start, state->idx - state->start), state);
			ft_token_add_back(&state->tklst, token);
		}
		state->start = ++state->idx;  // 여는 인용부호 건너뛰기
		while (input[state->idx] && input[state->idx] != quote)
			state->idx++;
		if (input[state->idx] == quote)
		{
			token = ft_new_token(ft_substr(input, state->start - 1, state->idx - state->start + 2), state);
			ft_token_add_back(&state->tklst, token);
			state->start = ++state->idx;  // 닫는 인용부호를 건너뛰고 다음 문자부터 처리
		}
		else
			exit(1);
		return (1);
	}
	return (0);
}

t_token* tokenize(t_data *data, char *input);
int handle_whitespace(t_tokenizer *state, char *input);
int handle_env_variable(t_tokenizer *state, char *input);
int handle_special_operators(t_tokenizer *state, char *input);
int handle_single_char_operators(t_tokenizer *state, char *input);

int handle_whitespace(t_tokenizer *state, char *input)
{
	if ((input[state->idx] >= 9 && input[state->idx] <= 13) || input[state->idx] == ' ')
	{
		if (state->idx != state->start)
			ft_token_add_back(&state->tklst,
				ft_new_token(ft_substr(input, state->start, state->idx - state->start), state));
		while ((input[state->idx] >= 9 && input[state->idx] <= 13) || input[state->idx] == ' ')
			state->idx++;
		ft_token_add_back(&state->tklst, ft_new_token(ft_strdup(" "), state));
		state->start = state->idx;
		return (1);
	}
	return (0);
}

int handle_env_variable(t_tokenizer *state, char *input)
{
	if (input[state->idx] == '$')
	{
		if (state->idx != state->start)
			ft_token_add_back(&state->tklst,
				ft_new_token(ft_substr(input, state->start, state->idx - state->start), state));
		state->start = state->idx;
		state->idx++;
		while (input[state->idx] && !(input[state->idx] == ' ' || input[state->idx] == '$' ||
			input[state->idx] == '\'' || input[state->idx] == '"' ||
			input[state->idx] == '<' || input[state->idx] == '>' || input[state->idx] == '|'))
			state->idx++;
		ft_token_add_back(&state->tklst,
			ft_new_token(ft_substr(input, state->start, state->idx - state->start), state));
		state->start = state->idx;
		return (1);
	}
	return (0);
}

int handle_special_operators(t_tokenizer *state, char *input)
{
	if (!ft_strncmp(input + state->idx, "<<", 2) || !ft_strncmp(input + state->idx, ">>", 2))
	{
		if (state->idx != state->start)
			ft_token_add_back(&state->tklst,
				ft_new_token(ft_substr(input, state->start, state->idx - state->start), state));
		ft_token_add_back(&state->tklst,
			ft_new_token(ft_substr(input, state->idx, 2), state));
		state->idx += 2;
		state->start = state->idx;
		return (1);
	}
	return (0);
}

int handle_single_char_operators(t_tokenizer *state, char *input)
{
	if (input[state->idx] == '<' || input[state->idx] == '>' || input[state->idx] == '|')
	{
		if (state->idx != state->start)
			ft_token_add_back(&state->tklst,
				ft_new_token(ft_substr(input, state->start, state->idx - state->start), state));
		ft_token_add_back(&state->tklst,
			ft_new_token(ft_substr(input, state->idx, 1), state));
		state->idx++;
		state->start = state->idx;
		return (1);
	}
	return (0);
}

void state_init(t_tokenizer *state)
{
	state->idx = 0;
	state->start = 0;
	state->is_first_token = 1;
	state->after_operator = 0;
	state->tklst = NULL;
}

// 메인 토큰화 함수
t_token* tokenize(t_data *data, char *input)
{
	t_tokenizer state;
	state_init(&state);

	while (input[state.idx])
	{
		if (handle_whitespace(&state, input))
			continue;
		if (handle_env_variable(&state, input))
			continue;
		if (handle_quote_token(&state, input))
			continue;
		if (handle_special_operators(&state, input))
			continue;
		if (handle_single_char_operators(&state, input))
			continue;
		state.idx++;
	}
	if (state.idx != state.start)
		ft_token_add_back(&state.tklst,
			ft_new_token(ft_substr(input, state.start, state.idx - state.start), &state));
	remove_quote(&state.tklst);
	change_env_vari(data, &state.tklst);
	join_cmd_str(&state.tklst);
	ft_print_tokens(state.tklst);
	printf("\n\n%d\n\n", data->last_ret);
	return (state.tklst);
}
