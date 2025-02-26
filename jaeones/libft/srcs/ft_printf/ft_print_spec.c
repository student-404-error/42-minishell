/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_spec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:36:16 by jaoh              #+#    #+#             */
/*   Updated: 2025/01/23 11:36:17 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_spec(char c, va_list *ap)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_print_char(va_arg(*ap, int));
	else if (c == 's')
		count += ft_print_str(va_arg(*ap, char *));
	else if (c == 'p')
		count += ft_print_mem(va_arg(*ap, void *));
	else if (c == 'd')
		count += ft_print_digit(va_arg(*ap, int), DEC_TAB);
	else if (c == 'i')
		count += ft_print_digit(va_arg(*ap, int), DEC_TAB);
	else if (c == 'u')
		count += ft_print_digit(va_arg(*ap, unsigned int), DEC_TAB);
	else if (c == 'x')
		count += ft_print_digit(va_arg(*ap, unsigned int), HEX_TAB);
	else if (c == 'X')
		count += ft_print_digit(va_arg(*ap, unsigned int), HEX_TAB_U);
	else if (c == '%')
		count += ft_print_char(c);
	else
		return (count);
	return (count);
}
