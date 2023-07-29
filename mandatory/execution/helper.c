/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:57 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/29 19:44:26 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

void	f(void)
{
	system("leaks minishell");
}

void	exec_builtin(t_data *data, t_env **new_env)
{
	char	*cmd;

	cmd = data->args[0];
	if (ft_strcmp(cmd, "pwd") == 0)
		my_pwd();
	else if (ft_strcmp(cmd, "unset") == 0)
		my_unset(new_env, data);
	else if (ft_strcmp(cmd, "echo") == 0)
		my_echo(data);
	else if (ft_strcmp(cmd, "cd") == 0)
		my_cd(new_env, data);
	else if (ft_strcmp(cmd, "env") == 0)
		my_env(new_env);
	else if (ft_strcmp(cmd, "exit") == 0)
		my_exit(new_env, data);
	else if (ft_strcmp(cmd, "export") == 0)
		my_export(new_env, data);
	exit(0);
}

void	direction(t_data *data, t_env **new_env)
{
	char	*cmd;

	if (data->args != NULL && data->args[0] != NULL)
	{
		cmd = data->args[0];
		if (ft_strcmp(cmd, "pwd") == 0 && data->next == NULL)
			my_pwd();
		else if (ft_strcmp(cmd, "unset") == 0 && data->next == NULL)
			my_unset(new_env, data);
		else if (ft_strcmp(cmd, "echo") == 0 && data->next == NULL)
			my_echo(data);
		else if (ft_strcmp(cmd, "cd") == 0 && data->next == NULL)
			my_cd(new_env, data);
		else if (ft_strcmp(cmd, "env") == 0 && data->next == NULL)
			my_env(new_env);
		else if (ft_strcmp(cmd, "exit") == 0 && data->next == NULL)
			my_exit(new_env, data);
		else if (ft_strcmp(cmd, "export") == 0 && data->next == NULL)
			my_export(new_env, data);
		else
			exec_pipe(data, *new_env);
	}
}

int	is_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "pwd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (0);
	else if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (0);
	else if (ft_strcmp(cmd, "env") == 0)
		return (0);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (0);
	else if (ft_strcmp(cmd, "export") == 0)
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
	ft_lstadd_backk(&env, ft_lstneww("PWD", pwd));
	ft_lstadd_backk(&env, ft_lstneww("SHLVL", "1"));
	ft_lstadd_backk(&env, ft_lstneww("_", "/usr/bin/env"));
	ft_lstadd_backk(&env, ft_lstneww("OLDPWD", NULL));
	//hiden
	ft_lstadd_backk(&env, ft_lstneww("PATH",
				"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	ft_lstadd_backk(&env, ft_lstneww("SHELL", "/bin/zsh"));
	return (env);
}
