/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:47:13 by seong-ki          #+#    #+#             */
/*   Updated: 2024/05/23 19:34:58 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len = 1;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_fill_str(char *s, long n, int len)
{
	s[len] = '\0';
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		len--;
		s[len] = (n % 10) + '0';
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	len = ft_intlen((long) n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	ft_fill_str(s, (long) n, len);
	return (s);
}
/*
int	main(void)
{
	printf("%s\n", ft_itoa(0));
}*/
