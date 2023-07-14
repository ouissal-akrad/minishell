/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:55 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/14 10:10:51 by ouakrad          ###   ########.fr       */
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

void	update_env(t_env *env, const char *oldpwd, const char *pwd)
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
	char *path = NULL;
	char pwd[PATH_MAX];
	char oldpwd[PATH_MAX];
	if (getcwd(oldpwd, PATH_MAX) == NULL)
	{
		perror("getcwd");
		return ;
	}
	if (args[1] == NULL)
	{
		path = find(env, "HOME");
		if (path == NULL)
		{
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return ;
	}
	//update env
    update_env(*env,oldpwd,pwd);
	// t_env *tmp = *env;
	// while (tmp)
	// {
	// 	if (ft_strcmp(tmp->var, "OLDPWD") == 0)
	// 	{
	// 		free(tmp->val);
	// 		tmp->val = ft_strdup(oldpwd);
	// 	}
	// 	if (ft_strcmp(tmp->var, "PWD") == 0)
	// 	{
	// 		if (getcwd(pwd, PATH_MAX) == NULL)
	// 		{
	// 			perror("getcwd");
	// 			return ;
	// 		}
	// 		free(tmp->val);
	// 		tmp->val = ft_strdup(pwd);
	// 	}
	// 	tmp = tmp->next;
	// }
	//cd . retriving create 3 folders
	// unset pwd unset OLDPWD
}