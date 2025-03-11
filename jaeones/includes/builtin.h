/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 14:00:41 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/10 21:18:52 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define SUCCESS 1
# define ERROR 2
# define PATH_MAX 4096

typedef struct s_data	t_data;

typedef enum e_ast_node_type {
	AST_COMMAND,
	AST_PIPE,
	AST_REDIRECTION_IN,
	AST_REDIRECTION_OUT,
	AST_REDIRECTION_APPEND,
	AST_HEREDOC,
}	t_ast_node_type;

typedef struct s_ast_node {
	t_ast_node_type		type;
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

typedef enum e_token_type {
	TOKEN_COMMAND,
	TOKEN_STRING,
	TOKEN_FILENAME,
	TOKEN_SPACE,
	TOKEN_PIPE,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_OUT,
	TOKEN_REDIRECTION_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VARI,
	TOKEN_EOF,
}	t_tok_type;

typedef struct s_token {
	t_tok_type		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

void	init_env(t_data *data, char **env);
// builtin function prototypes
// void	builtin_export(t_data *data, char *str);
int		builtin_unset(t_data *data, char *target);
int		builtin_pwd(void);
int		builtin_env(t_data *data);
int		builtin_cd(char *path, t_data *data);
int		bi_is_builtin(char *cmd);

#endif // !BUILTIN_H
