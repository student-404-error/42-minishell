/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:51:45 by seong-ki          #+#    #+#             */
/*   Updated: 2024/05/30 19:07:21 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ptr(uintptr_t nbr)
{
	char	*addr;
	int		len;

	if (nbr == 0)
		return (ft_print_str("(nil)"));
	ft_print_str("0x");
	addr = convert_to_hexa((unsigned long)nbr);
	len = ft_print_str(addr);
	free(addr);
	addr = NULL;
	return (len + 2);
}
