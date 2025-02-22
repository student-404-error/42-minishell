/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:15:12 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/20 15:35:01 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_err_export(char *var)
{
	int	tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: export: %s: not a valid identifier\n", P_NAME, var);
	ex_dup2_close(tmp_fd, STDOUT_FILENO);
	return (1);
}

void	bi_err_exit(char *val)
{
	int	tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: exit: %s: numeric argument required\n", P_NAME, val);
	ex_dup2_close(tmp_fd, STDOUT_FILENO);
}

void	bi_err_env(char *file)
{
	int	tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("env: %s: No such file or directory\n", file);
	ex_dup2_close(tmp_fd, STDOUT_FILENO);
}
