/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:55 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/10 18:05:15 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	update_env(t_env **env, t_my_cd *my_cd)
{
	t_env	*e;
	t_env	*f_oldpwd;
	t_env	*f_pwd;

	f_oldpwd = find_env(*env, "OLDPWD");
	f_pwd = find_env(*env, "PWD");
	if (f_oldpwd == NULL)
		ft_lstadd_backk(env, ft_lstneww("OLDPWD", my_cd->oldpwd));
	if (f_pwd == NULL)
		ft_lstadd_backk(env, ft_lstneww("PWD", my_cd->pwd));
	e = *env;
	while (e)
	{
		update_env_helper(e, my_cd);
		e = e->next;
	}
	free_cd(*my_cd);
}

int	my_cd_helper(t_data *data, t_my_cd *my_cd)
{
	DIR	*dir;

	if (access(my_cd->path, F_OK) == 0)
	{
		dir = opendir(my_cd->path);
		if (dir == NULL)
			return (error_msg_1(my_cd->path), 0);
		closedir(dir);
	}
	if (chdir(my_cd->path) == -1)
		return (error_msg_2(my_cd->path), 0);
	if (getcwd(my_cd->pwd, PATH_MAX) == NULL)
		return (g_global.g_exit = 1, perror("getcwd"), 0);
	if (data->args[1] != NULL && ft_strncmp(data->args[1], "-") == 0)
		printf("%s\n", my_cd->pwd);
	g_global.g_exit = 0;
	return (1);
}

void	update_env_error(t_env **env, t_my_cd *my_cd)
{
	t_env	*e;
	t_env	*f_oldpwd;
	t_env	*f_pwd;

	f_oldpwd = find_env(*env, "OLDPWD");
	f_pwd = find_env(*env, "PWD");
	if (f_oldpwd == NULL)
		ft_lstadd_backk(env, ft_lstneww("OLDPWD", my_cd->origin_oldpwd));
	if (f_pwd == NULL)
		ft_lstadd_backk(env, ft_lstneww("PWD", my_cd->origin_pwd));
	e = *env;
	while (e)
	{
		update_env_err_helper(e, my_cd);
		e = e->next;
	}
	free_cd(*my_cd);
}

void	my_cd(t_env **env, t_data *data)
{
	t_my_cd	my_cd;

	if (data->args[1] == NULL)
	{
		my_cd.path = go_home(env);
		if (my_cd.path == NULL || my_cd.path[0] == '\0')
			return ;
	}
	else if (data->args[1] != NULL && ft_strncmp(data->args[1], "-") == 0)
	{
		my_cd.path = go_oldpwd(env);
		if (my_cd.path == NULL)
			return ;
	}
	else
		my_cd.path = ft_strdup(data->args[1]);
	my_cd.origin_pwd = find(*env, "PWD");
	my_cd.origin_oldpwd = find(*env, "OLDPWD");
	if (getcwd(my_cd.oldpwd, PATH_MAX) == NULL)
		return (parent(&my_cd), update_env_error(env, &my_cd));
	if (my_cd_helper(data, &my_cd))
		update_env(env, &my_cd);
	else
		update_env_error(env, &my_cd);
}

void	parent(t_my_cd *my_cd)
{
	if (chdir(my_cd->path) == -1)
	{
		write(2, "minishell: cd: ", 16);
		write(2, my_cd->path, ft_strlen(my_cd->path));
		write(2, ": ", 2);
		perror("");
		g_global.g_exit = 1;
		return ;
	}
	write(2, "cd: error retrieving current directory: ", 40);
	write(2, "getcwd: cannot access parent directories: ", 42);
	perror("");
	return ;
}
