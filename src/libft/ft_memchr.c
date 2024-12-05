/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:52:06 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/10 21:27:44 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	chr;
	size_t			i;

	str = (unsigned char *) s;
	chr = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (str[i] == chr)
			return ((void *)(str + i));
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char s[] = {0,1,2,3,4,5};
	printf("22%s\n\n", s);
	printf("%s\n", ft_memchr(s, 2, 3));
	printf("%s\n", ft_memchr(s, 0, 1));
	printf("%s\n", ft_memchr(s, 2 + 256, 3));
	printf("%s\n", memchr(s, 2, 3));
	printf("%s\n", memchr(s, 0, 1));
	printf("%s\n", memchr(s, 2 + 256, 3));
}*/
