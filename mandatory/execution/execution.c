/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:48:12 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/01 15:24:04 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_execution.h"

char	*join_path(char *path, char *cmd)
{
	char	**paths;
	char	*new_path;
	char	*tmp;
	int		i;

	paths = ft_split(path, ':');
	if (!paths)
		return (write(2, "Memorry Error!\n", 15), NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (free_leaks(paths), NULL);
		new_path = ft_strjoin(tmp, cmd);
		if (!new_path)
			return (free_leaks(paths), free(tmp), NULL);
		free(tmp);
		if (access(new_path, X_OK) == 0)
			return (free_leaks(paths), new_path);
		else if (errno == EACCES)
		{
            fprintf(stderr, "minishell: %s: Permission denied\n", new_path);
            g_exit = 126; 
        }
		free(new_path);
	}
	return (free_leaks(paths), NULL);
}

char	*find_path(char *cmd, char *envp[])
{
	int	i;

	   if (cmd[0] == '\0') 
	{
        g_exit = 127;
        return NULL;
    }
	if ((ft_strchr(cmd, '/')) || !is_builtins(cmd))
		return (cmd);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (join_path(envp[i] + 5, cmd));
	}
	return (cmd);
}

char	**env_list_to_char_array(t_env *env_list)
{
	t_env	*curr;
	int		i;
	int		var_len;
	int		val_len;
	char	**env_array;
	char	*var_val_str;

	env_array = malloc((ft_lstsizee(env_list) + 1) * sizeof(char *));
	i = 0;
	curr = env_list;
	while (curr != NULL)
	{
		var_len = ft_strlen(curr->var);
		val_len = ft_strlen(curr->val);
		var_val_str = malloc(var_len + val_len + 2);
		if (!var_val_str)
			return (NULL);
		ft_strcpy(var_val_str, curr->var);
		ft_strcat(var_val_str, "=");
		ft_strcat(var_val_str, curr->val);
		env_array[i] = var_val_str;
		curr = curr->next;
		i++;
	}
	return (env_array[i] = NULL, env_array);
}

void	exec_cmd(t_data *data, char *path, char **env, t_env **env_list,
		int *pipefd)
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
	{
		signal(SIGINT,sigg);
		signal(SIGQUIT,sigg);

		if (!data->args[0] || data->in < 0 || data->out < 0)
			exit(0);
		if (data->in > 2)
			dup2(data->in, STDIN_FILENO);
		if (data->out > 2)
			dup2(data->out, STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (!is_builtins(path))
			exec_builtin(data, env_list);
		else
		{
			if (execve(path, data->args, env) < 0)
			{
				perror("minishell");
				g_exit = 127;
			}
		}
	}
	else
		waitpid(pid, &status, 0);
}

void	exec_pipe(t_data *data, t_env *env_list)
{
	char	**env;
	char	*path = ft_strdup("");
	int		pipefd[2];
	pid_t	pid;
	int		status;
	
	env = env_list_to_char_array(env_list);
	if (!env)
		return ;
	if (data->args[0])
		path = find_path(data->args[0], env);
	if (!path)
	{
		printf("minishell: %s: command not found\n", data->args[0]);
		g_exit = 127;
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		free(path);
		free_leaks(env);
		return ;
	}
	if (data->next != NULL)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			close(pipefd[0]);
			close(pipefd[1]);
			free(path);
			free_leaks(env);
			return ;
		}
		if (pid == 0)
		{
			signal(SIGINT,sigg);
			signal(SIGQUIT,sigg);
			if (!data->args[0] || data->in < 0 || data->out < 0)
				exit(0);
			if (data->in > 2)
				dup2(data->in, STDIN_FILENO);
			if (data->out > 2)
				dup2(data->out, STDOUT_FILENO);
			else if (data->out == 1)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			if (!is_builtins(path))
				exec_builtin(data, &env_list);
			if (execve(path, data->args, env) < 0)
			{
				perror("minishell");
				g_exit = 127;
			}
		}
		else
		{
			free(path);
			// free_leaks(env);
			close(pipefd[1]);
			if (data->next->in == 0)
				data->next->in = pipefd[0];
			exec_pipe(data->next, env_list);
			waitpid(pid, &status, 0);
			g_exit = status;
		}
	}
	else
	{
		
		exec_cmd(data, path, env, &env_list, pipefd);
	}
	close_files(data);
}
