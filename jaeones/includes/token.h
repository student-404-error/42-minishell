/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:00:41 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/20 15:54:16 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef struct s_data	t_data;

typedef enum e_token_type
{
	INFILE,
	OUTFILE,
	HEREDOC,
	N_HEREDOC,
	APPEND,
	PIPE,
	STRING,
	SINGLEQUOTE,
	DOUBLEQUOTE,
	COMMAND,
	FILENAME,
	ARGUMENT
}	t_tok_type;

typedef struct s_token
{
	char			*value;
	t_data			*data;
	t_tok_type		type;
	struct s_token	*next;
}	t_token;

t_token			*tok_get_token(char *str, t_data *data);
t_token			*tokenize(t_data *data, char *line);
void			tok_free(t_token *token);
void			tok_free_list(t_token *token);
t_token			*tok_create(char *value, int n, t_tok_type type, t_data *data);
t_token			*tok_get_last(t_token *token);
int				tok_append(t_token **head, t_token *new);
int				tok_quote_len(char *str, char quote);
int				tok_strlen(char *str);
int				tok_get_len(char *str, t_tok_type type);
t_tok_type		tok_get_type(char *str);
int				tok_is_operator(char c);

#endif