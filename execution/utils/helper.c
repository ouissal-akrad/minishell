/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:57 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/10 17:05:25 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_builtin(t_data *data, t_env **new_env)
{
	char	*cmd;

	if (data->in != -1 && data->out != -1)
	{
		cmd = data->args[0];
		if (ft_strncmp(cmd, "pwd") == 0)
			my_pwd(data, *new_env);
		else if (ft_strncmp(cmd, "unset") == 0)
			my_unset(new_env, data, 0);
		else if (ft_strncmp(cmd, "echo") == 0)
			my_echo(data, 1);
		else if (ft_strncmp(cmd, "cd") == 0)
			my_cd(new_env, data);
		else if (ft_strncmp(cmd, "env") == 0)
			my_env(new_env, data);
		else if (ft_strncmp(cmd, "exit") == 0)
			my_exit(new_env, data);
		else if (ft_strncmp(cmd, "export") == 0)
			my_export(new_env, data);
		exit(g_global.g_exit);
	}
}

void	direction(t_data *data, t_env **new_env)
{
	if (data->next == NULL && data->args != NULL && data->args[0] != NULL
		&& (data->out != -1 && data->in != -1) && !is_builtins(data->args[0]))
	{
		if (ft_strncmp(data->args[0], "exit") == 0)
			my_exit(new_env, data);
		else if (ft_strncmp(data->args[0], "pwd") == 0)
			my_pwd(data, *new_env);
		else if (ft_strncmp(data->args[0], "unset") == 0)
			my_unset(new_env, data, 0);
		else if (ft_strncmp(data->args[0], "echo") == 0)
			my_echo(data, 1);
		else if (ft_strncmp(data->args[0], "cd") == 0)
			my_cd(new_env, data);
		else if (ft_strncmp(data->args[0], "env") == 0)
			my_env(new_env, data);
		else if (ft_strncmp(data->args[0], "export") == 0)
			my_export(new_env, data);
		return ;
	}
	exec_pipe(data, *new_env);
}

int	is_builtins(char *cmd)
{
	if (ft_strncmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strncmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strncmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strncmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strncmp(cmd, "env") == 0)
		return (0);
	else if (ft_strncmp(cmd, "exit") == 0)
		return (0);
	else if (ft_strncmp(cmd, "export") == 0)
		return (0);
	else
		return (1);
}

t_env	*no_env(void)
{
	t_env	*env;
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX) == NULL)
		return (NULL);
	g_global.g_env = 1;
	ft_lstadd_backk(&env, ft_lstneww("PWD", pwd));
	ft_lstadd_backk(&env, ft_lstneww("SHLVL", "1"));
	ft_lstadd_backk(&env, ft_lstneww("_", "/usr/bin/env"));
	ft_lstadd_backk(&env, ft_lstneww("OLDPWD", NULL));
	ft_lstadd_backk(&env, ft_lstneww("PATH",
			"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	return (env);
}
