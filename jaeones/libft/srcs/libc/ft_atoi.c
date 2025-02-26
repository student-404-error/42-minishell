/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:10:39 by jaoh              #+#    #+#             */
/*   Updated: 2024/08/01 18:10:39 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isblank(char a);

static	int	ft_error(int sign);

int	ft_atoi(const char *str)
{
	int	nbr;
	int	sign;
	int	nbr_len;

	nbr = 0;
	sign = 1;
	nbr_len = 0;
	while (ft_isblank(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		if (++nbr_len == 20)
			return (ft_error(sign));
		nbr = (*str - 48) + nbr * 10;
		str++;
	}
	return (nbr * sign);
}

static	int	ft_isblank(char a)
{
	return ((a == '\n')
		|| (a == '\v')
		|| (a == '\f')
		|| (a == '\t')
		|| (a == '\r')
		|| (a == ' '));
}

static	int	ft_error(int sign)
{
	if (sign > 0)
		return (-1);
	else
		return (0);
}
