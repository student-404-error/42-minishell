/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:36:07 by jaoh              #+#    #+#             */
/*   Updated: 2025/01/23 11:36:08 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_digit(long nbr, char *base)
{
	int		count;
	long	base_len;

	count = 0;
	base_len = (long)ft_strlen(base);
	if (nbr < 0)
	{
		count += write(STDOUT_FILENO, "-", 1);
		nbr *= (-1);
	}
	if (nbr >= base_len)
		count += ft_print_digit((nbr / base_len), base);
	count += ft_print_char(base[(nbr % base_len)]);
	return (count);
}
