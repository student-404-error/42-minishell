/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:49:01 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/10 21:28:07 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(((unsigned char *) dst) + i) = *(((unsigned char *) src) + i);
		i++;
	}
	return (dst);
}
/*
#include <stdio.h>
int	main(void)
{
	void * dst;
	printf("%s\n", (char *) ft_memcpy(dst, "hello", 3));
}*/
