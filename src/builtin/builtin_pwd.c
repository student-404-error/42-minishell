/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:28:39 by seong-ki          #+#    #+#             */
/*   Updated: 2024/09/11 14:37:02 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd()
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX))
	{
		printf("%s\n", path);
		return (0);
	}
	else 
	{
		perror("pwd");
		return (1);
	}
}
