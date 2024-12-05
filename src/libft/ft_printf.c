/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:19:11 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/10 21:22:26 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_format(va_list args, char c)
{
	int	total_len;

	total_len = 0;
	if (c == 'c')
		total_len += ft_print_chr(va_arg(args, int));
	else if (c == 's')
		total_len += ft_print_str(va_arg(args, char *));
	else if (c == 'p')
		total_len += ft_print_ptr(va_arg(args, uintptr_t));
	else if (c == 'd' || c == 'i')
		total_len += ft_print_nbr(va_arg(args, int));
	else if (c == 'u')
		total_len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (c == 'x' || c == 'X')
		total_len += ft_print_hex(va_arg(args, unsigned int), c);
	else if (c == '%')
		total_len += ft_print_pct();
	return (total_len);
}

int	ft_printf(char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	va_start(args, format);
	len = ft_strlen(format);
	i = 0;
	while (format[i] != '\0')
	{
		if (format[i] == '%' && ft_strchr("cspdiuxX%", format[i + 1]))
		{
			len += ft_format(args, format[i + 1]);
			i++;
		}
		else
			ft_putchar_fd(format[i], 1);
		i++;
	}
	va_end(args);
	return (len);
}
