/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_advanced_sort_string_tab.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 17:12:56 by jaoh              #+#    #+#             */
/*   Updated: 2025/01/22 17:13:53 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_swap_pointer(char **a1, char **a2)
{
	char	*temp;

	temp = *a1;
	*a1 = *a2;
	*a2 = temp;
}

void	ft_advanced_sort_string_tab(char **tab,
	int (*cmp)(const char *, const char *))
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 1;
		while (tab[i + j])
		{
			if (cmp(tab[i], tab[i + j]) > 0)
				ft_swap_pointer(&tab[i], &tab[i + j]);
			j++;
		}
		i++;
	}
}