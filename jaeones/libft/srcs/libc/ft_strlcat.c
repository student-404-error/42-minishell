/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 18:16:45 by jaoh              #+#    #+#             */
/*   Updated: 2024/08/01 18:16:45 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dest_size)
{
	size_t	i;
	size_t	dest_length;
	size_t	src_length;
	size_t	expected_dest_size;

	i = 0;
	dest_length = ft_strlen(dest);
	src_length = ft_strlen(src);
	if (dest_size > dest_length)
	{
		expected_dest_size = dest_length + src_length;
		while (src[i] && dest_length < dest_size - 1)
			dest[dest_length++] = src[i++];
		dest[dest_length] = 0;
		return (expected_dest_size);
	}
	else
		return (src_length + dest_size);
}
