/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:50:37 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/06 20:10:59 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*list_ptr;

	list_ptr = lst;
	len = 0;
	while (list_ptr)
	{
		list_ptr = list_ptr->next;
		len++;
	}
	return (len);
}
