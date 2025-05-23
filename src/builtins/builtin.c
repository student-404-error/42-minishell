/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:24 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/29 17:43:40 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (2);
	return (0);
}

int	bi_do_builtin(t_data *data, char *cmd, t_args *args)
{
	if (!ft_strcmp(cmd, "echo"))
		return (bi_echo(args));
	if (!ft_strcmp(cmd, "cd"))
		return (bi_cd(data, args));
	if (!ft_strcmp(cmd, "pwd"))
		return (bi_pwd(args));
	if (!ft_strcmp(cmd, "export"))
		return (bi_export(data, args));
	if (!ft_strcmp(cmd, "unset"))
		return (bi_unset(data, args));
	if (!ft_strcmp(cmd, "env"))
		return (bi_env(data, args));
	if (!ft_strcmp(cmd, "exit"))
		return (bi_exit(data, args));
	return (0);
}

int	bi_echo(t_args *args)
{
	int	n_flag;

	n_flag = 0;
	while (args && !bi_nflag(args->value))
	{
		n_flag = 1;
		args = args->next;
	}
	while (args)
	{
		printf("%s", args->value);
		if (args->next)
			printf("%s", " ");
		args = args->next;
	}
	if (!n_flag)
		printf("%s", "\n");
	return (0);
}

int	bi_cd(t_data *data, t_args *args)
{
	int		ac;
	char	*cwd;
	t_env	*home;

	ac = arg_lstsize(args);
	if (ac > 1)
		return (ft_putstr_fd("minishell: cd: too many arguments\n",
				STDERR_FILENO), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("minishell: cd: error no current directory");
	home = ms_getenv("HOME", data->envp);
	if ((!ac || !ft_strcmp(args->value, "--")) && home && home->value)
		chdir(home->value);
	else if ((!ac || !ft_strcmp(args->value, "--")) && (!home || !home->value))
		return (bi_error_cd(errno, "HOME"), free(cwd), 1);
	else if (chdir(args->value) < 0)
	{
		bi_error_cd(errno, args->value);
		return (free(cwd), 1);
	}
	if (bi_update_pwd(data, cwd))
		return (free(cwd), 1);
	return (free(cwd), 0);
}

int	bi_pwd(t_args *args)
{
	char	*cwd;

	if (args && args->value)
	{
		bi_error_pwd(args->value);
		return (2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd: error no current directory");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
