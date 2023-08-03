/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:55 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/03 01:54:22 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find(t_env *env, char *to_find)
{
	while (env)
	{
		if (ft_strncmp(env->var, to_find) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

void	update_env(t_env *env, char *oldpwd, char *pwd)
{
	while (env)
	{
		if (ft_strncmp(env->var, "OLDPWD") == 0)
		{
			free(env->val);
			env->val = ft_strdup(oldpwd);
		}
		else if (ft_strncmp(env->var, "PWD") == 0)
		{
			free(env->val);
			env->val = ft_strdup(pwd);
		}
		env = env->next;
	}
}

void	my_cd(t_env **env, t_data *data)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	*path;

	if (data->args[1] == NULL)
	{
		path = go_home(env);
		if (path == NULL)
			return ;
	}
	else if (data->args[1] != NULL && ft_strncmp(data->args[1], "-") == 0)
	{
		path = go_oldpwd(env);
		if (path == NULL)
			return ;
	}
	else
		path = data->args[1];
	if (getcwd(oldpwd, PATH_MAX) == NULL)
		parent(path);
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		g_exit = 1;
		return ;
	}
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		perror("getcwd");
		g_exit = 1;
		return ;
	}
	if (data->args[1] != NULL && ft_strncmp(data->args[1], "-") == 0)
		printf("%s\n", pwd);
	update_env(*env, oldpwd, pwd);
	g_exit = 0;
}

char	*go_home(t_env **env)
{
	char	*path;

	path = find(*env, "HOME");
	if (path == NULL)
	{
		printf("cd: HOME not set\n");
		g_exit = 1;
		return (NULL);
	}
	return (path);
}
char	*go_oldpwd(t_env **env)
{
	char	*path;

	path = find(*env, "OLDPWD");
	if (path == NULL)
	{
		printf("cd: OLDPWD not set\n");
		g_exit = 1;
		return (NULL);
	}
	return (path);
}

void	parent(char *path)
{
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		g_exit = 1;
		return ;
	}
	printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory.\n");
	return ;
}
