/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:51:47 by seong-ki          #+#    #+#             */
/*   Updated: 2024/05/21 10:51:48 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	printf("%d\n", isalnum(48));
	printf("%d\n", isalnum(97));
	printf("%d\n", isalnum(65));
	printf("%d\n", isalnum(55));
	printf("%d\n", ft_isalnum(48));
	printf("%d\n", ft_isalnum(97));
	printf("%d\n", ft_isalnum(65));
	printf("%d\n", ft_isalnum(55));
}
*/
