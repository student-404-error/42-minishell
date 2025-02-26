/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:48:24 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/20 16:09:23 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") ||
		!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export") ||
		!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (2);
	return (0);
}


int	bi_do_builtin(t_data *data, char *cmd, t_args *args)
{
	if (!ft_strcmp(cmd, "echo"))
		return (bi_echo(args));
	/*if (!ft_strcmp(cmd, "cd"))
		return (bi_cd(data, args));
	if (!ft_strcmp(cmd, "pwd"))
		return (bi_pwd(args));*/
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
	while (args)
	{
		printf("%s", args->value);
		if (args->next)
			printf("%s", " ");
		args = args->next;
	}
	printf("%s", "\n");
	return (0);
}

// int	bi_cd(t_data *data, t_args *args){}
// int	bi_pwd(t_args *args){}

// 인자가 없으면 환경 변수 목록 출력
// 인자가 있으면 환경 변수 추가
int	bi_export(t_data *data, t_args *args)
{
	int	exit_code;

	exit_code = 0;
	if (!args)
	{
		if (bi_print_export(data->envp))
			exit_code = 1;
	}
	else
	{
		while (args)
		{
			if (bi_add_var(args->value, &(data->envp)))
				exit_code = 1;
			args = args->next;
		}
	}
	return (exit_code);
}

// 환경 변수 삭제
int	bi_unset(t_data *data, t_args *args)
{
	if (!args)
		return (0);
	else
	{
		while (args)
		{
			if (bi_delete_var(args->value, &(data->envp)))
				return (1);
			args = args->next;
		}
	}
	return (0);
}

// 환경 변수 목록 출력
int	bi_env(t_data *data, t_args *args)
{
	t_env	*tmp;

	tmp = data->envp;
	if (args)
	{
		bi_err_env(args->value);
		return (127);
	}
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->id, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

/*
인자가 숫자가 아니면 오류 처리
인자가 두 개 이상이면 오류 처리
정상적으로 종료 코드 설정 후 종료
*/
int	bi_exit(t_data *data, t_args *args)
{
	int		exit_code;

	if (args && args->next && !bi_check_exitcode(args->value))
		return (ft_putstr_fd("minishell: exit: too many arguments\n",
				STDERR_FILENO), 1);
	exit_code = 0;
	if (args && !bi_check_exitcode(args->value))
		exit_code = ft_atoi(args->value);
	else if (args && bi_check_exitcode(args->value))
	{
		bi_err_exit(args->value);
		exit_code = 2;
	}
	ex_close_all_fds(data, NULL);
	ms_free_all(data);
	exit(exit_code);
}