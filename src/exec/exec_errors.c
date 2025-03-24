/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:10:21 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/24 15:22:39 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_err_open(int err_no, char *file)
{
	int		fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s: %s\n", P_NAME, file, strerror(err_no));
	ex_dup2_close(fd_tmp, STDOUT_FILENO);
}

void	ex_err_pipe(int err_no)
{
	int		fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s\n", P_NAME, strerror(err_no));
	ex_dup2_close(fd_tmp, STDOUT_FILENO);
	exit(2);
}

void	ex_err_fork(int err_no)
{
	int		fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s: %s\n", P_NAME, strerror(err_no));
	ex_dup2_close(fd_tmp, STDOUT_FILENO);
	exit(3);
}

void	ex_err_exec(char *path, int err_no)
{
	int				fd_tmp;
	struct stat		stats;

	fd_tmp = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	if (err_no == 13 && stat(path, &stats) != -1)
	{
		if (S_ISDIR(stats.st_mode) == 1)
			printf("%s: %s: Is a directory\n", P_NAME, path);
		else
			printf("%s: %s: %s\n", P_NAME, path, strerror(err_no));
	}
	else
		printf("%s: %s: command not found\n", P_NAME, path);
	ex_dup2_close(fd_tmp, STDOUT_FILENO);
}

void	ex_unlink_heredoc(t_data *data)
{
	t_exec	*exec;
	t_file	*tmp;

	exec = data->exec;
	while (exec)
	{
		tmp = exec->redirs;
		while (tmp)
		{
			if (tmp->type == TOKEN_HEREDOC_END)
				unlink(tmp->path);
			tmp = tmp->next;
		}
		exec = exec->next;
	}
}
