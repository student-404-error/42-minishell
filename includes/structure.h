/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:28:29 by seong-ki          #+#    #+#             */
/*   Updated: 2025/03/29 17:28:31 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H
# include <sys/types.h>

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_STRING,
	TOKEN_DOUBLE_Q,
	TOKEN_FILENAME,
	TOKEN_ENV_VARI,
	TOKEN_SPACE,
	TOKEN_PIPE,
	TOKEN_REDIRECTION_IN,
	TOKEN_REDIRECTION_OUT,
	TOKEN_REDIRECTION_APPEND,
	TOKEN_HEREDOC,
	TOKEN_HEREDOC_END,
}	t_token_type;

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}	t_args;

typedef struct s_file
{
	char			*path;
	t_token_type	type;
	struct s_file	*next;
}	t_file;

typedef struct s_exec
{
	char			*cmd;
	t_args			*args;
	t_file			*redirs;
	struct s_exec	*next;
	int				fd_in;
	int				fd_out;
}	t_exec;

typedef struct s_signals
{
	int	signal_code;
	int	eof;
}	t_signals;

typedef struct s_env
{
	char			*key;
	char			*value;
	char			*raw;
	int				len;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_data
{
	int				def_in;
	int				def_out;
	int				exec_count;
	int				exit_code;
	pid_t			*pids;
	int				pid_count;
	t_exec			*exec;
	t_env			*envp;
	t_token			*tklst;
}	t_data;

#endif
