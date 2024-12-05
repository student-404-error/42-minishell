/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 11:25:23 by seong-ki          #+#    #+#             */
/*   Updated: 2024/07/10 21:26:39 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_len(char *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	return (len);
}

static int	ft_cntword(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str)
		{
			count++;
			while (*str != c && *str)
				str++;
		}
	}
	return (count);
}

static char	**make_strs(char *str, char c)
{
	int			i;
	int			word_len;
	char		**strs;

	strs = (char **) malloc(sizeof(char *) * (ft_cntword(str, c) + 1));
	if (!strs)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str == '\0')
			break ;
		word_len = ft_word_len(str, c);
		strs[i] = malloc(sizeof(char) * (word_len + 1));
		if (strs[i] == NULL)
			return (ft_free_split(strs));
		ft_strlcpy(strs[i], str, word_len + 1);
		str += word_len;
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

char	**ft_split(char *s, char c)
{
	if (!s)
		return (NULL);
	return (make_strs(s, c));
}
