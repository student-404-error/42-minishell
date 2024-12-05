/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:50:03 by seong-ki          #+#    #+#             */
/*   Updated: 2024/05/21 10:50:05 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
/*
#include <stdio.h>
#include <ctype.h>

int main(void)
{
	printf("%d\n", toupper(98));
	printf("%d\n", ft_toupper(98));
	printf("%d\n", toupper(38));
	printf("%d\n", ft_toupper(38));
}*/
