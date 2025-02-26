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

int	ft_dollar_idx(char *s)
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
	int		len;
	char	*env_name;

	len = 0;
	while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
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
		env = env->next;
	}
	return (ft_strdup(""));
}

void	change_env_vari(t_data *data, t_token **tklst)
{
	int		dollar_idx;
	char	*str;
	char	*ret;
	t_token	*inst_lst;

	inst_lst = *tklst;
	while (inst_lst)
	{
		dollar_idx = ft_dollar_idx(inst_lst->value);
		if (dollar_idx >= 0)
		{
			ret = ft_substr(inst_lst->value, 0, dollar_idx - 1); // ret malloc됨.
			str = ret;
			ret = ft_strjoin(ret, get_env_value(data, get_env_key(inst_lst->value + dollar_idx)));
			str = get_env_key(inst_lst->value + dollar_idx + 1);
			dollar_idx += ft_strlen(str);
			free(str);
			while (1)
			{
				if (ft_dollar_idx(inst_lst->value + dollar_idx) == -1)
					break;
				else 
				{
					if (ft_dollar_idx(inst_lst->value + dollar_idx) != 1)
					{
						str = ret;
						ret = ft_strjoin(ret, ft_substr(inst_lst->value, dollar_idx + 1, ft_dollar_idx(inst_lst->value + dollar_idx) - 2));
						dollar_idx += ft_dollar_idx(inst_lst->value + dollar_idx) - 1;
						free(str);
					}
					else
					{
						str = ret;
						ret = ft_strjoin(ret, get_env_value(data, get_env_key(inst_lst->value + dollar_idx + 1)));
						dollar_idx += ft_strlen(get_env_key(inst_lst->value + dollar_idx));
						free(str);
						break ;
					}
				}
			}
			// str = ret;
			// ret = ft_strjoin(ret, inst_lst->value + (ft_strlen(inst_lst->value) - ft_strlen(ft_strrchr(inst_lst->value, '$')) + 0));
			str = ret;
			ret = ft_strjoin(ret, inst_lst->value + dollar_idx + ft_strlen(get_env_key(inst_lst->value + dollar_idx + 1)) + 1);
			free(str);
			free(inst_lst->value);
			inst_lst->value = ret;
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
	// change_env_vari(data, &state.tklst);
	remove_quote(&state.tklst);
	join_cmd_str(&state.tklst);
	ft_print_tokens(state.tklst);
	printf("\n\n%d\n\n", data->last_ret);
	return (state.tklst);
}
