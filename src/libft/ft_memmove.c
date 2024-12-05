/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 10:50:44 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/10 21:28:16 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_mem(unsigned char *d, unsigned char *s, size_t len)
{
	size_t	i;

	i = 0;
	if (s < d)
	{
		while (i < len)
		{
			d[len - i - 1] = s[len - i - 1];
			i++;
		}
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
}

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *) dst;
	s = (unsigned char *) src;
	if (dst == NULL && src == NULL)
		return (dst);
	ft_mem(d, s, len);
	return (dst);
}
/*
int main()
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	*dest;
	dest = src + 1;
      
	memmove(dest, NULL, 8); 
	write(1, src, 22); 
	write(1, "\n", 1);
	return 0;
}
*/
// orem ipsum dolor sit amet
// lorem ip
// 	   um dolor sit amet
