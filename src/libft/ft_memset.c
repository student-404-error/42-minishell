/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:52:11 by seong-ki          #+#    #+#             */
/*   Updated: 2024/05/21 11:02:43 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*barr;
	unsigned char	chr;

	barr = (unsigned char *) b;
	chr = (unsigned char) c;
	i = 0;
	while (i < len)
	{
		barr[i] = chr;
		i++;
	}
	return (b);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str;
	ft_memset(str, 0, 4);
	//printf("%c\n", ((char *)memset(str, 65, 4))[5]);
	printf("%d\n", str[0]);
	printf("%d\n", str[1]);
	printf("%d\n", str[2]);
	printf("%d\n", str[3]);
}*/
