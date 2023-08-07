/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 01:40:43 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/07 02:01:23 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	failed(int ex)
{
	g_global.g_exit = ex;
	exit(g_global.g_exit);
}

int	do_fork(t_data *data, t_env **env_list, t_exec exec, int pipefd[])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		free(exec.path);
		free_leaks(exec.env);
		return (pid);
	}
	if (pid == 0)
		go_child_mp(data, env_list, exec, pipefd);
	else if (pid > 0)
		re_call(data, exec, *env_list, pipefd);
	return (pid);
}

void	exec_pipe(t_data *data, t_env *env_list)
{
	t_exec	exec;
	int		pipefd[2];
	pid_t	pid;
	int		status;

	exec.path = NULL;
	exec.env = env_list_to_char_array(env_list, 0);
	if (!exec.env)
		return ;
	if (data->args[0])
		exec.path = find_path(data->args[0], exec.env);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (free(exec.path), free_leaks(exec.env));
	}
	if (data->next != NULL)
	{
		pid = do_fork(data, &env_list, exec, pipefd);
		if (pid == -1)
			return ;
		waitpid(pid, &status, 0);
	}
	else
		one_cmd(data, exec, &env_list, pipefd);
}

void	go_child_mp(t_data *data, t_env **env_list, t_exec exec, int pipefd[])
{
	if (data->in < 0 || data->out < 0)
		failed(1);
	if (!data->args[0])
		failed(0);
	if (data->in > 2)
		dup2(data->in, STDIN_FILENO);
	if (data->out > 2)
		dup2(data->out, STDOUT_FILENO);
	else if (data->out == 1)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	if (data->is_dir == 0)
		do_exec(data, exec.path, exec.env, env_list);
	else if (data->is_dir == 1)
		err_isdir(data);
	else if (data->is_dir == 2)
		err_permission(data);
	else if (data->is_dir == 3)
		err_nodir(data);
}

void	re_call(t_data *tmp, t_exec exec, t_env *env_list, int pipefd[])
{
	if (exec.path != NULL)
		free(exec.path);
	if (exec.env != NULL)
		free_leaks(exec.env);
	close(pipefd[1]);
	if (tmp->next->in == 0)
		tmp->next->in = pipefd[0];
	exec_pipe(tmp->next, env_list);
	close(pipefd[0]);
}
