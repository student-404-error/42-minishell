/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:31:23 by jaoh              #+#    #+#             */
/*   Updated: 2025/04/01 18:33:19 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_check_id(char *id)
{
	int	i;

	i = 0;
	if (!*id)
		return (0);
	while (id[i])
	{
		if (i == 0 && ft_isalpha(id[i]) == 0 && id[i] != '_')
			return (0);
		if (ft_isalnum(id[i]) == 0 && id[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	bi_check_exitcode(char *value)
{
	char	*tmp;
	long	num;

	tmp = value;
	if ((*tmp == '+' || *tmp == '-') && *(tmp + 1))
		tmp++;
	while (*tmp)
	{
		if (!ft_isdigit(*tmp++))
			return (1);
	}
	num = ft_atoi(value);
	if (num > LONG_MAX || num < LONG_MIN)
		return (1);
	printf("--------num :%ld::-------\n", num);
	return (0);
}
