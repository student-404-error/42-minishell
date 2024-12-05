/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seong-ki <seong-ki@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 17:20:20 by seong-ki          #+#    #+#             */
/*   Updated: 2024/10/17 17:36:34 by seong-ki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int	fd1;
	int	ret;

	fd1 = open("test.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd1 < 0)
		return (1);
	ret = dup2(fd1, STDOUT_FILENO);
	if (ret < 0)
	close(fd1);
	return (0);
}
