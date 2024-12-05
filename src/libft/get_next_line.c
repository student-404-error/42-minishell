/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 00:01:25 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/17 00:01:27 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	result = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!result)
		return (result);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	free(s1);
	return (result);
}

char	*gnl_read_line(int fd, char *save, char *buffer)
{
	int		bytes_read;

	bytes_read = 1;
	while (!ft_strchr(save, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(save);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		save = gnl_strjoin(save, buffer);
	}
	return (save);
}

char	*gnl_save_line(char *line)
{
	char	*next;
	int		len;
	int		i;

	len = 0;
	while (line[len] != '\0' && line[len] != '\n')
		len++;
	if (line[len] == 0 || line[1] == 0)
		return (NULL);
	next = malloc(sizeof(char) * (ft_strlen(line) - len + 1));
	if (!next)
		return (NULL);
	i = 0;
	while (line[len + 1 + i] != '\0')
	{
		next[i] = line[len + 1 + i];
		i++;
	}
	next[i] = '\0';
	line[len + 1] = '\0';
	return (next);
}

char	*get_next_line(int fd, int err)
{
	char		*line;
	char		*buffer;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || err < 0)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = gnl_read_line(fd, save, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	save = gnl_save_line(line);
	return (line);
}
