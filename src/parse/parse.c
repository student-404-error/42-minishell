/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:07:50 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/17 15:41:18 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
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
*/

// 공백 토큰 제거를 먼저 하느냐. 아니면 나중에 하느냐 아예 안 하느냐.

void	ft_print_tokens(t_token *tklst)
{
	t_token	*list_ptr;

	if (!tklst)
		return ;
	list_ptr = tklst;
	printf("\n\n===========RESULT===========\n");
	while (list_ptr)
	{
		printf("lexing: token: %s | type: %d\n", list_ptr->value, list_ptr->type);
		list_ptr = list_ptr->next;
	}
	printf("\n\n");
	return ;
}

void	state_init(t_tokenizer *state)
{
	state->idx = 0;
	state->start = 0;
	state->is_first_token = 1;
	state->after_operator = 0;
	state->tklst = NULL;
}

t_token	*tokenize(t_data *data, char *input)
{
	t_tokenizer	state;

	state_init(&state);
	while (input[state.idx])
	{
		if (handle_whitespace(&state, input))
			continue ;
		if (handle_env_variable(&state, input))
			continue ;
		if (handle_quote_token(&state, input))
			continue ;
		if (handle_special_operators(&state, input))
			continue ;
		if (handle_single_char_operators(&state, input))
			continue ;
		state.idx++;
	}
	if (state.idx != state.start)
		ft_token_add_back(&state.tklst,
			ft_new_token(ft_substr(input, state.start,
					state.idx - state.start), &state));
	remove_quote(&state.tklst);
	expand_env_vari(data, &state.tklst);
	concat_token(&state.tklst);
	return (state.tklst);
}
