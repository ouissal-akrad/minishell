/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   one_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 01:39:02 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/07 20:05:21 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	go_child_ocmd(t_data *data, char *path, char **env, t_env **env_list)
{
	if (data->in < 0 || data->out < 0)
		failed(1);
	if (!data->args[0])
		failed(0);
	if (data->in > 2)
		dup2(data->in, STDIN_FILENO);
	if (data->out > 2)
		dup2(data->out, STDOUT_FILENO);
	if (data->is_dir == 0)
		do_exec(data, path, env, env_list);
	else if (data->is_dir == 1)
		err_isdir(data);
	else if (data->is_dir == 2)
		err_permission(data);
	else if (data->is_dir == 3)
		err_nodir(data);
}

void	exec_cmd(t_data *data, char *path, char **env, t_env **env_list)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		free(path);
		free_leaks(env);
		return ;
	}
	else if (pid == 0)
		go_child_ocmd(data, path, env, env_list);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_global.g_exit = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_global.g_exit = 128 + WTERMSIG(status);
	}
}

void	do_exec(t_data *data, char *path, char **env, t_env **env_list)
{
	if (!path)
		err_cmd(data);
	else if (path[ft_strlen(path) - 2] == '.'
		&& path[ft_strlen(path) - 1] == '.')
		err_cmd(data);
	if (!is_builtins(path))
		exec_builtin(data, env_list);
	else if (execve(path, data->args, env) < 0)
	{
		write(2, "minishell: ", 11);
		write(2, data->args[0], ft_strlen(data->args[0]));
		write(2, ": ", 2);
		perror("");
		g_global.g_exit = 127;
		exit(g_global.g_exit);
	}
}

void	one_cmd(t_data *tmp, t_exec exec, t_env **env_list)
{
	exec_cmd(tmp, exec.path, exec.env, env_list);
	if (exec.path != NULL)
		free(exec.path);
	if (exec.env != NULL)
		free_leaks(exec.env);
}
