/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 04:54:28 by seong-ki          #+#    #+#             */
/*   Updated: 2024/06/03 16:41:31 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_recu_nbr(char *result, int i, unsigned long nbr, char *hexa)
{
	if (i < 0)
		return ;
	result[i] = hexa[nbr % 16];
	if (nbr >= 16)
		ft_recu_nbr(result, i - 1, nbr / 16, hexa);
}

int	count_length(unsigned long nbr)
{
	unsigned long		i;
	int					cnt;

	if (nbr == 0)
		return (1);
	i = nbr;
	cnt = 0;
	while (i > 0)
	{
		i /= 16;
		cnt++;
	}
	return (cnt);
}

char	*convert_to_hexa(unsigned long nbr)
{
	char	*result;
	int		digits;

	digits = count_length(nbr);
	result = malloc(sizeof(char) * (digits + 1));
	if (!result)
		return (NULL);
	ft_recu_nbr(result, digits - 1, nbr, "0123456789abcdef");
	result[digits] = '\0';
	return (result);
}

int	ft_print_hex(unsigned int n, char c)
{
	char	*str;
	int		len;
	int		i;

	str = convert_to_hexa((unsigned long) n);
	if (c == 'X')
	{
		i = 0;
		while (str[i])
		{
			str[i] = ft_toupper(str[i]);
			i++;
		}
	}
	len = ft_print_str(str);
	free(str);
	str = NULL;
	return (len);
}
