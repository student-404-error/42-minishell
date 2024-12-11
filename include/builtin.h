/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:31:11 by seong-ki          #+#    #+#             */
/*   Updated: 2024/09/11 14:32:48 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include <stdio.h>

# define SUCCESS 1
# define ERROR 2
# define PATH_MAX 1024

typedef struct s_data {
	t_env	*env;
	int		last_ret;
}	t_data;

void	init_env(t_data *data, char **env);
// builtin function prototypes
// void	builtin_export(t_data *data, char *str);
int		builtin_unset(t_data *data, char *target);
int		builtin_pwd(void);
int		builtin_env(t_data data);
int		builtin_cd(char *path, t_data *data);
#endif // !BUILTIN_H