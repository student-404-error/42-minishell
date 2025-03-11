/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:34:11 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/11 15:33:16 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	update_pwd()
// {
//
// }
// void	update_old_pwd()
// {
//
// }

int	bi_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (2);
	else
		return (0);
}

int	bi_do_builtin(t_data *data, char *cmd, t_args *args)
{
	// if (!ft_strcmp(cmd, "echo"))
	// 	return (builtin_echo(args));
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(data, args));
	else if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd(args));
	// else if (!ft_strcmp(cmd, "export"))
	// 	return (bi_export(data, args));
	else if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(data, args));
	else if (!ft_strcmp(cmd, "env"))
		return (builtin_env(data, args));
	// else if (!ft_strcmp(cmd, "exit"))
	// 	return (bi_exit(data, args));
	else
		return (0);
}

int	builtin_cd(char *path/*추후에 argument로 옵션, 아규먼트 다 넘길 예정*/, t_data *data)
{
	int	ret;

	(void) data;
	if (path == NULL)
	{
		perror("cd");
		return (-1);
	}
	ret = chdir(path);
	if (ret != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}
