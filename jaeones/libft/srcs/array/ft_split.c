/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:28:33 by jaoh              #+#    #+#             */
/*   Updated: 2025/01/23 11:29:12 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strchop(char const *s, int start, int end)
{
	char	*str;

	str = (char *)malloc((end - start) * sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s + start + 1, end - start);
	return (str);
}

static int	ft_assign_arr(char **arr, char const *s, char c, int s_len)
{
	int	i;
	int	j;
	int	anchor;

	i = -1;
	j = 0;
	anchor = i;
	while (++i <= s_len)
	{
		if (s[i] == c || !s[i])
		{
			if (i - anchor > 1)
			{
				arr[j] = ft_strchop(s, anchor, i);
				if (!arr[j++])
				{
					ft_free_all(arr);
					return (0);
				}
			}
			anchor = i;
		}
	}
	arr[j] = 0;
	return (1);
}

static int	ft_count_subset(char const *s, char c, int s_len)
{
	int	i;
	int	cnt;
	int	anchor;

	i = -1;
	cnt = 0;
	anchor = i;
	while (++i <= s_len)
	{
		if (s[i] == c || !s[i])
		{
			if (i - anchor > 1)
				cnt++;
			anchor = i;
		}
	}
	return (cnt);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		s_len;
	int		n_subset;

	s_len = (int)ft_strlen(s);
	n_subset = ft_count_subset(s, c, s_len);
	arr = (char **)malloc((n_subset + 1) * sizeof(char *));
	if (!arr)
		return (0);
	if (ft_assign_arr(arr, s, c, s_len) == 0)
		return (0);
	return (arr);
}
/* Note
 * 1. if s is NULL, it will crash
 * 2. if any of malloc fail, it will return NULL
 * 3. if s is empty, it will return an empty arr with a NULL
 */