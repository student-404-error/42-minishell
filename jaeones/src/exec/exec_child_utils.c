/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaoh <jaoh@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 16:10:26 by jaoh              #+#    #+#             */
/*   Updated: 2025/02/18 16:14:46 by jaoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
1. ex_get_path(cmd, data->envp)
cmd(예: ls)의 실행 파일 경로를 찾음 (예: /bin/ls).
2. ex_get_envs(data->envp)
환경 변수를 char ** 형태로 변환.
3. ex_get_cmds(cmd, args)
cmd + args를 배열 형태로 변환 (예: {"ls", "-l", NULL}).
4. execve(path, cmds, envs) 실행
실행 파일을 현재 프로세스와 교체.
*** execve()는 실패할 경우만 다음 코드가 실행됨.
*/
int	ex_do_exec(t_data *data, char *cmd, t_args *args)
{
	char	*path;
	char	**cmds;
	char	**envs;

	if (!cmd || *cmd == '\0')
		return (0);
	path = ex_get_path(cmd, data->envp); // 실행 파일의 경로 찾기
	if (!path)
		return (ex_err_exec(cmd, errno), -1);
	envs = ex_get_envs(data->envp);
	cmds = ex_get_cmds(cmd, args); // 명령어 + args 배열 만들기
	if (!envs || !cmds)
		return (free(path), free(envs), free(cmds), -1);
	if (execve(path, cmds, envs) == -1) // execve 실행
		ex_err_exec(path, errno);
	ft_free_all(cmds);
	free(path);
	free(envs);
	return (-2);
}
/*
env path를 검색하여 실행 파일 경로를 찾음
절대경로(/bin/ls)면 그대로 반환함
 */
char	*ex_get_path(char *file, t_env *env)
{
	char	**paths;
	char	*exec;
	t_env	*path_env;

	if (file && file[0] == '\0')
		return (NULL);
	if (!env || ex_is_abs_path(file) == 1) // 절대경로(`/bin/ls`)면 그대로 사용
		return (ft_strdup(file));
	path_env = ms_getenv("PATH", env); // env에서 PATH 가져오기
	if (!path_env)
		return (ft_strdup(file));
	paths = ft_split(path_env->value, ':');
	if (!paths)
		return (ft_strdup(file));
	exec = ex_get_exec(paths, file); // 실행 파일 찾기
	ft_free_all(paths);
	return (exec);
}
/*
PATH에 있는 디렉토리에서 파일이 실행 가능한지 검사함
access(path, X_OK | F_OK)로 실행 권한 확인함
*/
char	*ex_get_exec(char **paths, char *file)
{
	char	*exec;
	char	*path;
	int		i;

	if (!paths || !file)
		return (NULL);
	i = -1;
	while (paths[++i]) // PATH 환경 변수에 있는 모든 디렉토리 검사
	{
		path = ft_strjoin(paths[i], "/"); // 디렉토리 경로 + "/" 붙이기
		if (!path)
			return (NULL);
		if (!(exec = ft_strjoin(path, file))) // 전체 경로 만들기 (예: /bin/ls)
			return (free(path), NULL);
		free(path);
		if (!access(exec, X_OK | F_OK)) // 실행 가능한지 확인
			return (exec);
		free(exec);
	}
	return (NULL);
}

char	**ex_get_cmds(char *cmd, t_args *args)
{
	char	**cmds;
	int		i;

	if (!cmd || *cmd == '\0')
		return (NULL);
	if (!(cmds = malloc((arg_lstsize(args) + 2) * sizeof(char *)))) // 명령어 + args 저장할 배열 할당
		return (NULL);
	if (!(cmds[0] = ft_strdup(cmd)))
		return (free(cmds), NULL);
	i = 1;
	while (args)
	{
		if (!(cmds[i++] = ft_strdup(args->value))) 
			return (ft_free_all(cmds), NULL);
		args = args->next;
	}
	cmds[i] = NULL;
	return (cmds);
}

char	**ex_get_envs(t_env *env)
{
	char	**envs;
	int		i;

	if (!(envs = malloc((env_lstsize(env) + 1) * sizeof(char *)))) // env 개수 구하기
		return (NULL);
	i = 0;
	while (env)
	{
		if (!(envs[i++] = ft_strdup(env->raw))) // env 원본 문자열 ("PATH=/bin:/usr/bin")
			return (ft_free_all(envs), NULL);
		env = env->next;
	}
	envs[i] = NULL;
	return (envs);
}
