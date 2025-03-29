/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:42:39 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/29 18:16:51 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (!ft_strchr(args->value, '='))
				exit_code = 0;
			else if (bi_add_var(args->value, &(data->envp)))
				exit_code = 1;
			args = args->next;
		}
	}
	return (exit_code);
}

int	bi_unset(t_data *data, t_args *args)
{
	if (!args)
		return (0);
	else
	{
		while (args)
		{
			if (!ft_strcmp(args->value, "_"))
				args = args->next;
			if (bi_delete_var(args->value, &(data->envp)))
				return (1);
			args = args->next;
		}
	}
	return (0);
}

int	bi_env(t_data *data, t_args *args)
{
	t_env	*tmp;

	tmp = data->envp;
	if (!ms_getenv("PATH", data->envp))
	{
		bi_error_env("env");
		return (127);
	}
	if (args)
	{
		bi_error_env(args->value);
		return (127);
	}
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

// 인자가 숫자가 아니면 오류 처리
// 인자가 두 개 이상이면 오류 처리
// 정상적으로 종료 코드 설정 후 종료
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
		bi_error_exit(args->value);
		exit_code = 2;
	}
	ex_close_all_fds(data, NULL);
	ms_free_all(data);
	exit(exit_code);
}
