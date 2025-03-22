/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 15:37:51 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/22 17:42:06 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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

void	ft_unlink_err(t_data *data)
{
	while (data->tklst)
	{
		if (data->tklst->type == TOKEN_HEREDOC_END)
			unlink(data->tklst->next->value);
		data->tklst = data->tklst->next;
	}
}

int	ft_handle_heredoc(t_data *data)
{
	char	*filename;
	int		fd;
	int		end;

	end = 0;
	while (data->tklst != NULL && end == 0)
	{
		if (data->tklst->type == TOKEN_HEREDOC)
		{
			filename = ft_gen_random();
			if (!filename)
				return (1);
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (!fd)
				return (1);
			if (ft_init_here_doc(fd, data->tklst->next->value) != 0)
				end = 1;
			close(fd);
			free(data->tklst->next->value);
			data->tklst->next->value = filename;
		}
		data->tklst = data->tklst->next;
	}
	return (end);
}
