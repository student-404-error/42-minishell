/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:15:12 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/19 18:37:56 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_error_export(char *var)
{
	int	tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: export: %s: not a valid identifier\n", P_NAME, var);
	ex_dup2_close(tmp_fd, STDOUT_FILENO);
	return (1);
}

void	bi_error_exit(char *value)
{
	int	tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: exit: %s: numeric argument required\n", P_NAME, value);
	ex_dup2_close(tmp_fd, STDOUT_FILENO);
}

void	bi_error_env(char *filename)
{
	int	tmp_fd;

	tmp_fd = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("env: %s: No such file or directory\n", filename);
	ex_dup2_close(tmp_fd, STDOUT_FILENO);
}

void	bi_error_cd(int err_no, char *filename)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (filename && ft_strcmp(filename, "HOME") == 0)
		printf("%s: cd: %s not set\n", P_NAME, filename);
	else
		printf("%s: cd: %s: %s\n", P_NAME, filename, strerror(err_no));
	ex_dup2_close(fd_tmp, STDOUT_FILENO);
}

void	bi_error_pwd(char *option)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: pwd: %s: invalid option\n", P_NAME, option);
	ex_dup2_close(fd_tmp, STDOUT_FILENO);
}
