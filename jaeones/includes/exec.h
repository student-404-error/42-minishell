/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:40:18 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/19 17:44:15 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_data	t_data;
typedef struct s_env	t_env;

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}	t_args;

typedef struct s_file
{
	char			*path;
	t_tok_type	type;
	struct s_file	*next;
}	t_file;

typedef struct s_exec
{
	char			*cmd;
	t_args			*args;
	t_file		*redirs;
	struct s_exec	*next;
	int				fd_in;
	int				fd_out;
}	t_exec;

/* exec */
int		ex_run_exec(t_data *data);
int		ex_run_pipeline(t_data *data);
void	ex_backup_restore_fds(t_data *data, int mode);
void	ex_close_all_fds(t_data *data, int pipe[]);
void	ex_close(int *fd);
void	ex_wait_child(t_data *data);

/* redirect */
int		ex_init_redir(t_exec *exec);
int		ex_handle_redir(t_exec *exec);
void	ex_redirection(t_exec *exec, t_file *file);

/* pipe */
void	ex_create_pipe(int fd_pipe[2]);
void	ex_setup_child(t_data *data, t_exec *exec);
void	ex_execute_child(t_data *data, t_exec *exec, int fd_pipe[]);
void	ex_dup2_close(int fd1, int fd2);
int		ex_is_abs_path(char *file);

/* child_utils */
int		ex_do_exec(t_data *data, char *cmd, t_args *args);
char	*ex_get_path(char *file, t_env *env);
char	*ex_get_exec(char **paths, char *file);
char	**ex_get_cmds(char *cmd, t_args *args);
char	**ex_get_envs(t_env *env);

/* errors */
void	ex_err_open(int err_no, char *file);
void	ex_err_pipe(int err_no);
void	ex_err_fork(int err_no);
void	ex_err_exec(char *path, int err_no);
void	ex_err_coredump(int pid);
void	ex_unlink_heredoc(t_data *data);

#endif