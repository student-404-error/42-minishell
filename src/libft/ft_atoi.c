/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:46:50 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/10 21:25:34 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(char *str)
{
	long	n;
	int		sign;

	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	n = 0;
	while (ft_isdigit(*str))
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	return (n * sign);
}
/*
#include <stdlib.h>
#include <stdio.h>
int	main(void)
{
	printf("%d\n", atoi(" \t   -10 "));
	printf("%d\n", ft_atoi(" \t   -10 "));
	printf("%d\n", atoi(" \t   +-10"));
	printf("%d\n", ft_atoi(" \t   +-10"));
}*/
