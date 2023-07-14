/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:55 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/14 16:40:31 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

char	*find(t_env **env, char *to_find)
{
	while (*env)
	{
		if (ft_strcmp((*env)->var, to_find) == 0)
			return ((*env)->val);
		(*env) = (*env)->next;
	}
	return (NULL);
}

void	update_env(t_env *env, char *oldpwd, char *pwd)
{
	while (env)
	{
		if (ft_strcmp(env->var, "OLDPWD") == 0)
		{
			free(env->val);
			env->val = ft_strdup(oldpwd);
		}
		else if (ft_strcmp(env->var, "PWD") == 0)
		{
			free(env->val);
			env->val = ft_strdup(pwd);
		}
		env = env->next;
	}
}

void	my_cd(t_env **env, char **args)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	*path;

	if (getcwd(oldpwd, PATH_MAX) == NULL)
	{
		perror("getcwd");
		g_exit = 1;
		exit(1);
	}
	path = NULL;
	if (args[1] == NULL)
	{
		path = find(env,"HOME");
		if (path == NULL)
		{
			printf("cd: HOME not set\n");
			g_exit = 1;
			return ;
		}
	}
	else
		path = args[1];
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
	update_env(*env, oldpwd, pwd);
}
