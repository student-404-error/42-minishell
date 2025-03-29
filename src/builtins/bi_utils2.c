/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bi_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 17:44:29 by jaoh              #+#    #+#             */
/*   Updated: 2025/03/29 17:45:06 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bi_update_pwd(t_data *data, char *value)
{
	t_env	*old_pwd;
	t_env	*pwd;
	char	*new_cwd;
	char	*raw;
	char	*raw2;

	new_cwd = getcwd(NULL, 0);
	old_pwd = ms_getenv("OLDPWD", data->envp);
	pwd = ms_getenv("PWD", data->envp);
	if (pwd && new_cwd)
	{
		raw2 = ft_strjoin("PWD=", new_cwd);
		if (!raw2 || bi_add_var(raw2, &data->envp))
			return (free(new_cwd), 1);
		free(raw2);
	}
	if (old_pwd && value)
	{
		raw = ft_strjoin("OLDPWD=", value);
		if (!raw || bi_add_var(raw, &data->envp))
			return (free(new_cwd), 1);
		free(raw);
	}
	free(new_cwd);
	return (0);
}

int	bi_nflag(char *flag)
{
	if (!ft_strncmp(flag, "-n", 2))
		flag += 2;
	else
		return (1);
	while (*flag)
	{
		if (*flag++ != 'n')
			return (1);
	}
	return (0);
}
