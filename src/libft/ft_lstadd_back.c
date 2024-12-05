/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:48:44 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/06 20:10:43 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last_node;

	last_node = ft_lstlast(*lst);
	if (!new)
		return ;
	if (last_node)
	{
		new->prev = last_node;
		last_node->next = new;
	}
	else
	{
		new->prev = NULL;
		*lst = new;
	}
	new->next = NULL;
}
