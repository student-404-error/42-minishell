/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:40:02 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/29 16:28:54 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <string.h>
# include <unistd.h>
# include <errno.h>
# include <ncurses.h>
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "builtin.h"
# include "exec.h"
# include "builder.h"
# include "signals.h"
# include "parsing.h"
# include "structure.h"
# include "libft.h"

# define P_NAME "charles mishell"
# define BROWN_A    "\033[1;33m"
# define MAGENTA_A "\033[1;35m"
# define CYAN_A    "\033[1;36m"

# define ESC_F "\001"
# define ESC_S "\002"
# define C_RESET "\033[0m"

# define IS_A_DIRECTORY 126
# define COMMAND_NOT_FOUND 127
# define SIGNAL_OFFSET 128

# define RND_OFFSET 14695981039346656037UL
# define RND_PRIME 1099511628211UL

# define PROMPT "\001\033[1;33m\002charles mishell >$ \001\033[0m\002"
# define DEF_ENV "SHELL=charles mishell"

extern t_signals	g_signals;

/* minishell 주요 함수 */
int		ft_setup_exec(t_data *data, t_token **token);
int		handle_pipeline(t_data *data, char *line);
int		handle_loop(t_data *data);
int		parser(t_token **token);
t_data	*ms_init_data(char **envp);
void	ms_free_all(t_data *data);
int		ms_check_line(char *line);
void	ms_clear(t_data *data, t_token *token);
t_env	*ms_env_dup(char **envp);
void	*ms_free_double(char **value);
t_env	*ms_getenv(char *path, t_env *envp);

/* t_env 함수 */
t_env	*env_create(char *key, char *value, char *raw);
t_env	*env_default_env(void);
void	env_del_one(t_env *env);
void	env_free(t_env *env);
int		env_add_back(t_env **head, t_env *new);
char	*env_create_id(char *raw);
char	*env_create_value(char	*raw);
int		env_lstsize(t_env *env);

/* parsing 주요 함수 */
t_token	*tokenize(t_data *data, char *input);
int		handle_single_char_operators(t_tokenizer *state, char *input);
int		handle_special_operators(t_tokenizer *state, char *input);
int		handle_env_variable(t_tokenizer *state, char *input);
int		handle_whitespace(t_tokenizer *state, char *input);
int		handle_quote_token(t_tokenizer *state, char *input);
void	remove_quote(t_token **tklst);
void	concat_token(t_token **tklst);
void	expand_env_vari(t_data *data, t_token **tklst);
void	remove_space_token(t_token **tklst);
void	change_env_to_cmd(t_token *tklst);
char	*get_env_key(char *str);
char	*get_env_value(t_data *data, char *key);
int		get_dollar_idx(char *s);
int		get_env_value_len(t_data *data, char *key);
int		count_total_length(t_data *data, char *token);
t_token	*ft_new_token(char *value, t_tokenizer *state);
t_token	*ft_tklast(t_token *tklst);
void	ft_token_add_back(t_token **tklst, t_token *new);
void	ft_free_token_list(t_token *token);
void	ft_free_token(t_token *token);
void	check_state(t_tokenizer *state);
t_token_type	check_token_type(char *value, t_tokenizer *state);
#endif
