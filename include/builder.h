/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:34:10 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/11 15:22:03 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILDER_H
# define BUILDER_H
# include "structure.h"

/* builder.c */
t_exec	*builder(t_token *token);
t_exec	*bd_init(void);
void	bd_free(t_exec *exec);
int		bd_lstsize(t_exec *exec);
void	bd_debug(t_exec *exec);

/* file.c */
void	file_free(t_file *filenames);
t_file	*file_create(char *path, t_token_type type);
t_file	*file_last(t_file *filename);
int		file_add_back(t_file **head, t_file *new);
int		file_lstsize(t_file *filename);

/* args.c */
void	arg_free(t_args *args);
t_args	*arg_create(char *value);
t_args	*arg_last(t_args *args);
int		arg_add_back(t_args **head, t_args *new);
int		arg_lstsize(t_args *args);

#endif