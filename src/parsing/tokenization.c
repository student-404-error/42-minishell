/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:31:15 by seong-ki          #+#    #+#             */
/*   Updated: 2024/09/11 16:42:48 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	is_whitespace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_cntword(const char *input)
{
	int	count;

	count = 0;
	while (*input)
	{
		while (is_whitespace(*input) && *input)
			input++;
		if (*input)
		{
			count++;
			while (!is_whitespace(*input) && *input)
				input++;
		}
	}
	return (count);
}

int	ft_token_len(int start, const char *input)
{
	int	token_length;

	token_length = 0;
	while (input[start] != '\0' && input[start] != ' ')
	{
		token_length++;
		start++;
	}
	return (token_length);
}

// char	*qoute_process(char *input)
// {
// 	int		single_qoute_flag;
// 	int		double_qoute_flag;
// 	int		i;
// 	int		size = 0;
// 	char	*ret;
//
// 	single_qoute_flag = -1;
// 	double_qoute_flag = -1;
// 	ret = NULL;
// 	i = 0;
// 	while (input[i])
// 	{
// 		if (input[i] == '\'' && double_qoute_flag == -1)
// 		{
// 			single_qoute_flag *= -1;
// 			size -= 2;
// 		}
// 		else if (input[i] == '\"' && single_qoute_flag == -1)
// 		{
// 			double_qoute_flag *= -1;
// 			size -= 2;
// 		}
// 		else if (input[i] == ' ' && single_qoute_flag == -1 && double_qoute_flag == -1)
// 			break;
// 		printf("char: %c\ni: %d\nsqf: %d\ndqf: %d\n", input[i], i,single_qoute_flag,double_qoute_flag);
// 		i++;
// 	}
// 	printf("length %d\n", i);
// 	return (NULL);
// 	if (single_qoute_flag != -1 || double_qoute_flag != -1)
// 	{
// 		printf("syntax error: you can't use open qoutes\n");
// 		return (NULL);
// 	}
// 	ret = malloc(sizeof(char) * (i + 1));
// 	size = 0;
// 	while (size < i)
// 	{
// 		if (*input == '\'' && double_qoute_flag == -1)
// 			single_qoute_flag *= -1;
// 		else if (*input == '\"' && single_qoute_flag == -1)
// 			double_qoute_flag *= -1;
// 		ret[size++] = *input;
// 		input++;
// 		printf("%c %c\n", *input, ret[size - 1]);
// 	}
// 	ret[size] = '\0';
// 	return (ret);
// }

char *process_quotes(const char *input) {
    int single_quote_flag = 0;
    int double_quote_flag = 0;
    char *result;
    int i = 0;
	int	j = 0;

	if (!input)
		return (NULL);			//	입력이 NULL이면 에러
	result = malloc(strlen(input) + 1);
	if (!result)
		return (NULL);			// malloc 에러
    while (input[i]) {
        if (input[i] == '\'' && double_quote_flag == 0) {
            // Toggle single quote flag
            single_quote_flag = !single_quote_flag;
            i++;
            continue;
        }
        if (input[i] == '\"' && single_quote_flag == 0) {
            // Toggle double quote flag
            double_quote_flag = !double_quote_flag;
            i++;
            continue;
        }
        result[j++] = input[i++];
    }
    result[j] = '\0'; // Null-terminate the result

    return (result);
}
char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > strlen(s))
		return (malloc(1));
	if (len > strlen(s + start))
		len = strlen(s + start);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}


t_tokenlist	tokenize(char *input)
{
	t_tokenlist	tklist;
	int		start;
	int		i;
	t_token	*new_token;
	char	*str;

	str = process_quotes(input);
	tklist.size = ft_cntword(input);
	start = 0;
	i = 0;
	while (i < tklist.size)
	{
		new_token = ft_new_token(ft_substr(str, start, ft_token_len(start, str)));
		start = ft_token_len(start, str) + 1;
		// ft_add_token(&tklist, new_token);
		i++;
	}
	/*
	 * 일단 한글자씩 넣으면서 공백을 만나면 공백 싹 넘기고 글자만 담고 하면 될 듯 한디
	 * while (*input)
	 * {
	 *		token[j] = input[i];
	 *		j++;
	 *		i++;
	 *		if (is_whitespace(input[i]))
	 *		{
	 *			token[j] = '\0';
	 *			
	 *		}
	 * }*/
	return (tklist);
}

void	syntax_process(char *token)
{
	if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	else if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, "<") == 0 | ft_strcmp(token, ">>") == 0)
		return (TOKEN_REDIRECTION);
	else if (ft_strcmp(token, "<<") == 0)
		// heredoc 처리
		return (TOKEN_HEREDOC);
	else if (ft_strcmp(token, "&&") == 0)
		// && 연산 처리
		return (TOKEN_OPER);
	else if (ft_strcmp(token, "||") == 0)
		// || 연산 처리
		return (TOKEN_OPER);
}

int main(int argc, char *argv[])
{
	tokenize(argv[1]);
	return EXIT_SUCCESS;
}
