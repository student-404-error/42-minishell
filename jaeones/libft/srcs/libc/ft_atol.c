/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:17:54 by jaoh              #+#    #+#             */
/*   Updated: 2025/01/22 17:17:57 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isblank(char c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v')
		return (1);
	return (0);
}

long	ft_atol(const char *nptr)
{
	int		i;
	long	sign;
	long	num;

	i = 0;
	sign = 1;
	num = 0;
	while (ft_isblank(nptr[i]) == 1)
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= (-1);
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = ((num * 10) + (nptr[i] - '0'));
		i++;
	}
	return ((num * sign));
}