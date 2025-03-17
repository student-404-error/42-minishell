/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:31:11 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/17 16:48:06 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

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

typedef struct s_data	t_data;
typedef struct s_env	t_env;
typedef struct s_args	t_args;

int		bi_do_builtin(t_data *data, char *cmd, t_args *args);
int		bi_is_builtin(char *cmd);
int		bi_echo(t_args *args);
int		bi_cd(t_data *data, t_args *args);
int		bi_pwd(t_args *args);
int		bi_exit(t_data *data, t_args *args);
int		bi_env(t_data *data, t_args *args);
int		bi_export(t_data *data, t_args *args);
int		bi_unset(t_data *data, t_args *args);

int		bi_print_export(t_env *env);
int		bi_add_var(char *value, t_env **env);
int		bi_delete_var(char *value, t_env **env);
int		bi_check_id(char *id);
int		bi_check_exitcode(char *value);
int		bi_update_pwd(t_data *data, char *value);
int		bi_nflag(char *flag);

void	bi_error_cd(int err_no, char *filename);
void	bi_error_pwd(char *option);
int		bi_error_export(char *var);
void	bi_error_exit(char *value);
void	bi_error_env(char *filename);

#endif // !BUILTIN_H
