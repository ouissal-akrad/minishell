/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:55 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/10 14:13:34 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	update_env(t_env **env, char *oldpwd, char *pwd)
{
	t_env	*e;
	t_env	*f_oldpwd;
	t_env	*f_pwd;

	f_oldpwd = find_env(*env, "OLDPWD");
	f_pwd = find_env(*env, "PWD");
	if (f_oldpwd == NULL)
		ft_lstadd_backk(env, ft_lstneww("OLDPWD", oldpwd));
	if (f_pwd == NULL)
		ft_lstadd_backk(env, ft_lstneww("PWD", pwd));
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

int	my_cd_helper(t_data *data, char *path, char *pwd)
{
	DIR	*dir;

	if (access(path, F_OK) == 0)
	{
		dir = opendir(path);
		if (dir == NULL)
			return (error_msg_1(path), 0);
		closedir(dir);
	}
	if (chdir(path) == -1)
		return (error_msg_2(path), 0);
	if (getcwd(pwd, PATH_MAX) == NULL)
		return (g_global.g_exit = 1, perror("getcwd"), 0);
	if (data->args[1] != NULL && ft_strncmp(data->args[1], "-") == 0)
		printf("%s\n", pwd);
	g_global.g_exit = 0;
	return (1);
}

void	update_env_error(t_env **env, char *origin_oldpwd, char *origin_pwd)
{
	t_env	*e;
	t_env	*f_oldpwd;
	t_env	*f_pwd;

	f_oldpwd = find_env(*env, "OLDPWD");
	f_pwd = find_env(*env, "PWD");

	if (f_oldpwd == NULL)
		ft_lstadd_backk(env, ft_lstneww("OLDPWD", origin_oldpwd));
	if (f_pwd == NULL)
		ft_lstadd_backk(env, ft_lstneww("PWD", origin_pwd));
	e = *env;
	while (e)
	{
		if (ft_strncmp(e->var, "OLDPWD") == 0)
		{
			free(e->val);
			e->val = ft_strdup(origin_oldpwd);
		}
		else if (ft_strncmp(e->var, "PWD") == 0)
		{
			free(e->val);
			e->val = ft_strdup(origin_pwd);
		}
		e = e->next;
	}
}

void	my_cd(t_env **env, t_data *data)
{
	char	oldpwd[PATH_MAX];
	char	pwd[PATH_MAX];
	char	*origin_pwd;
	char	*origin_oldpwd;
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
		path = ft_strdup(data->args[1]);
	origin_pwd = find(*env, "PWD");
	origin_oldpwd = find(*env, "OLDPWD");
	if (getcwd(oldpwd, PATH_MAX) == NULL)
	{
		parent(path);
		update_env_error(env, origin_oldpwd, origin_pwd);
		return (free(path));
	}
	if (my_cd_helper(data, path, pwd))
		update_env(env, oldpwd, pwd);
	else
		update_env_error(env, origin_oldpwd, origin_pwd);
	free(origin_pwd);
	free(origin_oldpwd);
	free(path);
}

void	parent(char *path)
{
	if (chdir(path) == -1)
	{
		write(2, "minishell: cd: ", 16);
		write(2, path, ft_strlen(path));
		write(2, ": ", 2);
		perror("");
		g_global.g_exit = 1;
		return ;
	}
	write(2, "cd: error retrieving current directory: ", 40);
	write(2, "getcwd: cannot access parent directories: ", 42);
	perror("");
	// write(2, "cd: error retrieving current directory: ", 40);
	// write(2, "getcwd: cannot access parent directories: ", 42);
	// write(2, "No such file or directory\n", 26);
	return ;
}
