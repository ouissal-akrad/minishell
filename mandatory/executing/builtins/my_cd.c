/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:55 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/16 07:55:57 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

char	*find(t_env *env, char *to_find)
{
	while (env)
	{
		if (ft_strcmp(env->var, to_find) == 0)
			return (env->val);
		env = env->next;
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
	// printf("===========>%s\n",args[1]);
	char oldpwd[PATH_MAX];
	char pwd[PATH_MAX];
	char *path;
	// cd without args
	if (args[1] == NULL)
	{
		path = find(*env, "HOME");
		if (path == NULL)
		{
			printf("cd: HOME not set\n");
			g_exit = 1;
			return ;
		}
	}
	// cd -
	else if (args[1] != NULL && ft_strcmp(args[1], "-") == 0)
	{
		path = find(*env, "OLDPWD");
		if (path == NULL)
		{
			printf("cd: OLDPWD not set\n");
			g_exit = 1;
			return ;
		}
	}
	// cd with args
	else
		path = args[1];
	// cd ~
	if(ft_strcmp(path,"~") == 0)
		path = find(*env, "HOME");
	// get OLDPWD
	if (getcwd(oldpwd, PATH_MAX) == NULL)
	{
		perror("getcwd");
		g_exit = 1;
		return ;
	}
	// execute cmd
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		g_exit = 1;
		return ;
	}
	// get PWD
	if (getcwd(pwd, PATH_MAX) == NULL)
	{
		perror("getcwd");
		g_exit = 1;
		return ;
	}
	if(args[1] != NULL && ft_strcmp(args[1],"-") == 0)
		printf("%s\n",pwd);
	// update env
	update_env(*env, oldpwd, pwd);
}