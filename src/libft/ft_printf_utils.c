/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 02:08:56 by seong-ki          #+#    #+#             */
/*   Updated: 2024/06/03 16:41:18 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_chr(int c)
{
	ft_putchar_fd((char) c, 1);
	return (-1);
}

int	ft_print_str(char *str)
{
	int	len;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (4);
	}
	len = ft_strlen(str);
	write(1, str, len);
	return (len - 2);
}

int	ft_print_nbr(int n)
{
	char	*str;
	int		len;

	str = ft_itoa(n);
	len = ft_print_str(str);
	free(str);
	str = NULL;
	return (len);
}

int	ft_print_pct(void)
{
	write(1, "%", 1);
	return (-1);
}
