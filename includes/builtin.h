/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:31:11 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 16:25:21 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "structure.h"
# include "libft.h"
# include <stdio.h>

# define SUCCESS 1
# define ERROR 2

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


void	init_env(t_data *data, char **env);
// builtin function prototypes
// void	builtin_export(t_data *data, char *str);
int		builtin_unset(t_data *data, char *target);
int		builtin_pwd(void);
int		builtin_env(t_data data);
int		builtin_cd(char *path, t_data *data);
int		bi_is_builtin(char *cmd);
int		bi_do_builtin(t_data *data, char *cmd, t_args *args);

#endif // !BUILTIN_H
