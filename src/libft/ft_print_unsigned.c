/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:19:52 by seong-ki          #+#    #+#             */
/*   Updated: 2024/06/03 16:41:48 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len = 1;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

void	ft_fill_str(char *s, unsigned int n, int len)
{
	s[len] = '\0';
	if (n == 0)
		s[0] = '0';
	while (n)
	{
		len--;
		s[len] = (n % 10) + '0';
		n = n / 10;
	}
}

char	*ft_unitoa(unsigned int n)
{
	char	*s;
	int		len;

	len = ft_intlen(n);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	ft_fill_str(s, n, len);
	return (s);
}

int	ft_print_unsigned(unsigned int n)
{
	char	*str;
	int		len;

	str = ft_unitoa(n);
	len = ft_print_str(str);
	free(str);
	str = NULL;
	return (len);
}
