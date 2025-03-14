
#include "minishell.h"

int	bi_is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (2);
	else
		return (0);
}

int	bi_do_builtin(t_data *data, char *cmd, t_args *args)
{
	if (!ft_strcmp(cmd, "echo"))
		return (builtin_echo(args));
	if (!ft_strcmp(cmd, "cd"))
		return (builtin_cd(data, args));
	else if (!ft_strcmp(cmd, "pwd"))
		return (builtin_pwd(args));
	else if (!ft_strcmp(cmd, "export"))
		return (bi_export(data, args));
	else if (!ft_strcmp(cmd, "unset"))
		return (builtin_unset(data, args));
	else if (!ft_strcmp(cmd, "env"))
		return (builtin_env(data, args));
	else if (!ft_strcmp(cmd, "exit"))
		return (bi_exit(data, args));
	else
		return (0);
}