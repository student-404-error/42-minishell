/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:36:21 by jaoh              #+#    #+#             */
/*   Updated: 2025/01/23 11:36:22 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *s)
{
	int		count;
	char	*tmp;

	if (!s)
		tmp = "(null)";
	else
		tmp = s;
	count = 0;
	count += write(STDOUT_FILENO, tmp, ft_strlen(tmp));
	return (count);
}
