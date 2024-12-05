/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:48:15 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/10 21:29:35 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *s, int c)
{
	int	i;

	while (c > 255)
		c -= 256;
	i = 0;
	while (s[i])
		i++;
	while (i >= 0 && s[i] != c)
		i--;
	if (i == -1)
		return (0);
	return ((char *)s + i);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%p\n", strrchr("teste", '\0'));
	printf("%p\n", ft_strrchr("teste", '\0'));
}
*/
