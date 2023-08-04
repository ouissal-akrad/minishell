/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:57 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/04 04:28:39 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	exec_builtin(t_data *data, t_env **new_env)
{
	char	*cmd;

	if (data->in != -1 && data->out != -1)
	{
		cmd = data->args[0];
		if (ft_strncmp(cmd, "pwd") == 0)
			my_pwd(data);
		else if (ft_strncmp(cmd, "unset") == 0)
			my_unset(new_env, data);
		else if (ft_strncmp(cmd, "echo") == 0)
			my_echo(data);
		else if (ft_strncmp(cmd, "cd") == 0)
			my_cd(new_env, data);
		else if (ft_strncmp(cmd, "env") == 0)
			my_env(new_env,data);
		else if (ft_strncmp(cmd, "exit") == 0)
			my_exit(new_env, data);
		else if (ft_strncmp(cmd, "export") == 0)
			my_export(new_env, data);
		exit(0);
	}
	// exit(1);
}

void	direction(t_data *data, t_env **new_env)
{
	// // char	*cmd;

	// if (data->args != NULL && data->args[0] != NULL && !is_builtins(data->args[0]))
	// {
	// 		cmd = data->args[0];
	// 	if (ft_strncmp(cmd, "pwd") == 0 && data->next == NULL)
	// 		my_pwd();
	// 	else if (ft_strncmp(cmd, "unset") == 0 && data->next == NULL)
	// 		my_unset(new_env, data);
	// 	else if (ft_strncmp(cmd, "echo") == 0 && data->next == NULL)
	// 		my_echo(data);
	// 	else if (ft_strncmp(cmd, "cd") == 0 && data->next == NULL)
	// 		my_cd(new_env, data);
	// 	else if (ft_strncmp(cmd, "env") == 0 && data->next == NULL)
	// 		my_env(new_env);
	// 	else if (ft_strncmp(cmd, "exit") == 0 && data->next == NULL)
	// 		my_exit(new_env, data);
	// 	else if (ft_strncmp(cmd, "export") == 0 && data->next == NULL)
	// 		my_export(new_env, data);
	// }
	// else

	if (data->next == NULL && data->args != NULL && data->args[0] != NULL && (data->out != -1 && data->in != -1))
	{
		if (ft_strncmp(data->args[0], "exit") == 0)
		{
			my_exit(new_env, data);
			return ;
		}
		if (ft_strncmp(data->args[0], "pwd") == 0)
		{
			my_pwd(data);
			return ;
		}
		else if (ft_strncmp(data->args[0], "unset") == 0)
			{
				my_unset(new_env, data);
				return;
			}
		else if (ft_strncmp(data->args[0], "echo") == 0)
			{
				my_echo(data);
				return;
			}
		else if (ft_strncmp(data->args[0], "cd") == 0)
			{
				my_cd(new_env, data);
				return;
			}
		else if (ft_strncmp(data->args[0], "env") == 0)
			{
				my_env(new_env, data);
				return;
			}
		else if (ft_strncmp(data->args[0], "export") == 0)
			{
				my_export(new_env, data);
				return;
			}
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
