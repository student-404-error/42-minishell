/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 19:33:41 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/10 21:29:12 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str1;
	char	*str2;

	str1 = "test\377";
	str2 = "test\0";
	printf("%d %d", ft_strncmp(str1, str2, 6), strncmp(str1, str2, 6));
}*/
