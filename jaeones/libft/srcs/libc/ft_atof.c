/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:46:34 by jaoh              #+#    #+#             */
/*   Updated: 2025/01/23 11:46:36 by jaoh             ###   ########.fr       */
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

static double	ft_power(double base, int power, double output)
{
	if (power < 0)
		return (0.0);
	if (!power)
		return (output);
	else
		return (ft_power(base, power - 1, output * base));
}

static void	ft_handler(double *num, int i, const char *nptr)
{
	int	j;

	j = 1;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		*num = *num + (nptr[i] - 48) * ft_power(0.1, j++, 1);
		i++;
	}
}

double	ft_atof(const char *nptr)
{
	int		i;
	double	sign;
	double	num;

	i = 0;
	sign = 1.0;
	num = 0.0;
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
		num = ((num * 10) + (nptr[i] - 48));
		i++;
	}
	if (nptr[i] == '.')
		ft_handler(&num, ++i, nptr);
	return ((num * sign));
}