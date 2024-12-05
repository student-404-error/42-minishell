/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:50:19 by seong-ki          #+#    #+#             */
/*   Updated: 2024/05/21 10:50:21 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	printf("%d\n", isdigit(48));
	printf("%d\n", isdigit(2));
	printf("%d\n", isdigit(1));
	printf("%d\n", isdigit(55));
	printf("%d\n", ft_isdigit(48));
	printf("%d\n", ft_isdigit(2));
	printf("%d\n", ft_isdigit(1));
	printf("%d\n", ft_isdigit(55));
}*/
