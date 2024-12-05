/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 17:34:11 by seong-ki          #+#    #+#             */
/*   Updated: 2024/09/17 17:41:01 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "builtin.h"
#include "libft.h"

// void	update_pwd()
// {
//
// }
// void	update_old_pwd()
// {
//
// }

int	builtin_cd(char *path/*추후에 argument로 옵션, 아규먼트 다 넘길 예정*/, t_data *data)
{
	int	ret;

	(void) data;
	if (path == NULL)
	{
		perror("cd");
		return (-1);
	}
	ret = chdir(path);
	if (ret != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}
