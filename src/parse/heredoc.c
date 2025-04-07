/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:37:51 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/07 14:54:06 by jaoh             ###   ########.fr       */
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

static int	ft_handle_line(char **input, char *line, char *eof, int fd)
{
    char	*new_line;

    new_line = ft_strjoin(*input, "\n");
    if (!new_line)
        return (1);
    free(*input);
    *input = ft_strjoin(new_line, line);
    free(new_line);
    if (!*input)
        return (1);
    if (!ft_strcmp(line, eof) || g_signals.eof == 1)
        return (1);
    if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
    {
        perror("write");
        return (1);
    }
    return (0);
}

int	ft_init_heredoc(char **input, int fd, char *eof)
{
    char	*line;
    void	(*prev_sigint_handler)(int);

    prev_sigint_handler = signal(SIGINT, sg_heredoc_handler);
    line = readline(">");
    if (!line)
    {
        ft_putstr_fd("minishell: here_doc: no input\n", 2);
        signal(SIGINT, prev_sigint_handler);
        return (1);
    }
    while (line)
    {
        if (ft_handle_line(input, line, eof, fd))
        {
            free(line);
            break ;
        }
        free(line);
        line = readline(">");
    }
    signal(SIGINT, prev_sigint_handler);
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

int	ft_handle_heredoc(t_token *token, char **input)
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
			if (ft_init_heredoc(input, fd, token->next->value) != 0)
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
