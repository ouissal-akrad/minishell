/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:55 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/05 01:27:24 by bel-idri         ###   ########.fr       */
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

void	update_env(t_env **env, char *oldpwd, char *pwd)
{
	t_env	*e;

	if (find(*env, "OLDPWD") == NULL || find(*env, "PWD") == NULL)
	{
		if (find(*env, "OLDPWD") == NULL)
			ft_lstadd_backk(env, ft_lstneww("OLDPWD", oldpwd));
		if (find(*env, "PWD") == NULL)
			ft_lstadd_backk(env, ft_lstneww("PWD", pwd));
		return ;
	}
	e = *env;
	while (e)
	{
		if (ft_strncmp(e->var, "OLDPWD") == 0)
		{
			free(e->val);
			e->val = ft_strdup(oldpwd);
		}
		else if (ft_strncmp(e->var, "PWD") == 0)
		{
			free(e->val);
			e->val = ft_strdup(pwd);
		}
		e = e->next;
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
		if (path[0] == '\0')
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
	if (access(path, F_OK) == 0)
	{
		if (opendir(path) == NULL)
		{
			write(2, "minishell: cd: ", 16);
			write(2, path, ft_strlen(path));
			write(2, ": Not a directory\n", 18);
			g_exit = 1;
			return ;
		}
	}
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 16);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);

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
	update_env(env, oldpwd, pwd);
	g_exit = 0;
}

char	*go_home(t_env **env)
{
	char	*path;

	path = find(*env, "HOME");
	if (path == NULL)
	{
		write(2, "cd: HOME not set\n", 17);
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
		write(2, "cd: OLDPWD not set\n", 19);
		g_exit = 1;
		return (NULL);
	}
	return (path);
}

void	parent(char *path)
{
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 16);
		write(2, path, ft_strlen(path));
		write(2, ": No such file or directory\n", 28);
		g_exit = 1;
		return ;
	}

	write(2, "cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory.\n", 109);
	return;
}
