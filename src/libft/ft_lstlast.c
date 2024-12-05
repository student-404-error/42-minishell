/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:47:20 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/06 20:10:17 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*list_ptr;

	if (!lst)
		return (NULL);
	list_ptr = lst;
	while (list_ptr->next)
		list_ptr = list_ptr->next;
	return (list_ptr);
}
