/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 15:36:18 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/20 15:39:36 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_env	t_env;

// builtin.c
int		bi_do_builtin(t_data *data, char *cmd, t_args *args);
int		bi_is_builtin(char *cmd);
int		bi_echo(t_args *args);
int		bi_export(t_data *data, t_args *args);
int		bi_env(t_data *data, t_args *args);
int		bi_unset(t_data *data, t_args *args);
int		bi_exit(t_data *data, t_args *args);

// bi_utils.c
int		bi_print_export(t_env *env);
int		bi_add_var(char *value, t_env **env);
int		bi_delete_var(char *value, t_env **env);

// bi_check.c
int		bi_check_id(char *id);
int		bi_check_exitcode(char *value);

// bi_errors.c
int		bi_err_export(char *var);
void	bi_err_exit(char *val);
void	bi_err_env(char *file);

#endif
