/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:09:44 by seong-ki          #+#    #+#             */
/*   Updated: 2024/05/22 11:09:24 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dest_size;
	size_t	src_size;

	i = 0;
	dest_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dstsize <= dest_size)
		return (src_size + dstsize);
	while (src[i] && i + dest_size < dstsize - 1)
	{
		dst[i + dest_size] = src[i];
		i++;
	}
	dst[i + dest_size] = '\0';
	return (src_size + dest_size);
}
/*
#include <stdio.h>
#include <bsd/string.h>

int	main(void)
{
	char	dest[100] = "123";
	char	sdest[100] = "123";
	char	src[100] = "hello world";

	char	dest1[7] = "hello";
	char	sdest1[7] = "hello";
	char	src1[6] = "world";
	
	printf("ft_lcat = %d\n", ft_strlcat(dest, src, 20));
	printf("stdlcat = %zu\n", strlcat(sdest, src, 20));
	printf("ft_lcat = %d\n", ft_strlcat(dest1, src1, 7));
	printf("stdlcat = %zu\n", strlcat(sdest1, src1, 7));
}*/
