/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:50:12 by seong-ki          #+#    #+#             */
/*   Updated: 2024/05/24 18:48:25 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*d;

	if (count * size < size && count * size != 0)
		return (NULL);
	d = malloc(count * size);
	if (d == NULL)
		return (d);
	ft_memset(d, 0, count * size);
	return (d);
}
