/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:37:51 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/01 15:12:40 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_gen_random_name(char *str)
{
	unsigned long	rand;
	int				i;
	char			*new;

	if (!str)
		return (NULL);
	new = ft_calloc(sizeof(char), 17);
	if (!new)
		return (NULL);
	rand = (unsigned long)str;
	ft_strlcpy(new, "/tmp/hd_", 9);
	i = 8;
	while (i < 16)
	{
		rand *= RND_OFFSET + RND_PRIME;
		new[i] = 'a' + (rand % 26);
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_init_here_doc(int fd, char *eof)
{
	char	*line;

	signal(SIGINT, sg_heredoc_handler);
	while (1)
	{
		line = readline(">");
		if (!line)
		{
			ft_putstr_fd("minishell: here_doc: no input\n", 2);
			break ;
		}
		if (!ft_strcmp(line, eof) || g_signals.eof == 1)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	if (g_signals.eof == 1)
		return (g_signals.eof = 0, 1);
	return (0);
}

void	ft_unlink_err(t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_HEREDOC_END)
			unlink(token->next->value);
		token = token->next;
	}
}

int	ft_handle_heredoc(t_token *token)
{
	char	*filename;
	int		fd;
	int		end;

	end = 0;
	while (token != NULL && end == 0)
	{
		if (token->type == TOKEN_HEREDOC)
		{
			filename = ft_gen_random_name(token->next->value);
			if (!filename)
				return (1);
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (!fd)
				return (1);
			if (ft_init_here_doc(fd, token->next->value) != 0)
				end = 1;
			close(fd);
			free(token->next->value);
			token->next->value = filename;
			token->type = TOKEN_HEREDOC_END;
		}
		token = token->next;
	}
	return (end);
}
