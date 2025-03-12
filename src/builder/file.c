/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:51:43 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/11 15:06:52 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_free(t_file *file)
{
	t_file	*tmp;

	while (file != NULL)
	{
		tmp = file;
		if (file->path)
			free(file->path);
		file = file->next;
		free(tmp);
	}
}

t_file	*file_create(char *path, t_token_type type)
{
	t_file	*filename;
	char	*new;

	filename = malloc(sizeof(t_file));
	if (filename == NULL)
		return (NULL);
	new = ft_strdup(path);
	if (!new)
	{
		free(filename);
		return (NULL);
	}
	filename->path = new;
	filename->type = type;
	filename->next = NULL;
	return (filename);
}

t_file	*file_last(t_file *filename)
{
	while (filename->next != NULL)
		filename = filename->next;
	return (filename);
}

int	file_add_back(t_file **head, t_file *new)
{
	if (new == NULL)
		return (1);
	if (*head == NULL)
		*head = new;
	else
		file_last(*head)->next = new;
	return (0);
}

int	file_lstsize(t_file *filename)
{
	int	i;

	i = 0;
	while (filename)
	{
		i++;
		filename = filename->next;
	}
	return (i);
}
