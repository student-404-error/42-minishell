/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:04:27 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/20 15:31:19 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_free(t_args *args)
{
	t_args	*tmp;

	while (args != NULL)
	{
		tmp = args;
		if (args->value)
			free(args->value);
		args = args->next;
		free(tmp);
	}
}

t_args	*arg_create(char *value)
{
	t_args	*args;
	char	*new;

	args = malloc(sizeof(t_args));
	if (args == NULL)
		return (NULL);
	new = ft_strdup(value);
	if (!new)
	{
		free(args);
		return (NULL);
	}
	args->value = new;
	args->next = NULL;
	return (args);
}

t_args	*arg_last(t_args *args)
{
	while (args->next != NULL)
		args = args->next;
	return (args);
}

int	arg_add_back(t_args **head, t_args *new)
{
	if (new == NULL)
		return (1);
	if (*head == NULL)
		*head = new;
	else
		arg_last(*head)->next = new;
	return (0);
}

int	arg_lstsize(t_args *args)
{
	int	i;

	i = 0;
	while (args)
	{
		i++;
		args = args->next;
	}
	return (i);
}
