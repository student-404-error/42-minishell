/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:51:43 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/22 19:13:38 by jaoh             ###   ########.fr       */
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
	t_file	*file;
	char	*new;
	
	file = malloc(sizeof(t_file));
	if (file == NULL)
		return (NULL);
	new = ft_strdup(path);
	if (!new)
	{
		free(file);
		return (NULL);
	}
	file->path = new;
	file->type = type;
	file->next = NULL;
	return (file);	
}

t_file	*file_last(t_file *file)
{
	while (file->next != NULL)
		file = file->next;
	return (file);
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

int	file_lstsize(t_file *file)
{
	int	i;

	i = 0;
	while (file)
	{
		i++;
		file = file->next;
	}
	return (i);
}
