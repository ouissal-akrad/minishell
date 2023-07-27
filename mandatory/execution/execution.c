/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:48:12 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/27 11:38:45 by ouakrad          ###   ########.fr       */
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
		free(new_path);
	}
	free_leaks(paths);
	write(2, "command not found!\n", 19);
	exit(0);
}

char	*find_path(char *cmd, char *envp[])
{
	int	i;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) != 0)
			return (write(2, "Command not found!\n", 20), NULL);
		cmd = ft_strdup(cmd);
		if (!cmd)
			return (write(2, "Memorry Error!\n", 15), NULL);
		return (cmd);
	}
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			return (join_path(envp[i] + 5, cmd));
		}
	}
	write(2, "command not found!\n", 19);
	exit(0);
}

char	**env_list_to_char_array(t_env *env_list)
{
	int		count;
	t_env	*curr;
	int		i;
	int		var_len;
	int		val_len;
	char	**env_array;
	char	*var_val_str;

	count = 0;
	curr = env_list;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	env_array = malloc((count + 1) * sizeof(char *));
	i = 0;
	curr = env_list;
	while (curr != NULL)
	{
		var_len = ft_strlen(curr->var);
		val_len = ft_strlen(curr->val);
		var_val_str = malloc(var_len + val_len + 2);
		if (!var_val_str)
			return (NULL);
		//
		strcpy(var_val_str, curr->var);
		strcat(var_val_str, "=");
		strcat(var_val_str, curr->val);
		env_array[i] = var_val_str;
		curr = curr->next;
		i++;
	}
	env_array[i] = NULL;
	return (env_array);
}

void	exec_cmd(t_data *data, char *path, char **env)
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
		if (data->in != -1)
			dup2(data->in, STDIN_FILENO);
		if (data->out != -1)
			dup2(data->out, STDOUT_FILENO);
		execve(path, data->args, env);
		perror(data->args[0]);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			status = WEXITSTATUS(status);
		else
			fprintf(stderr, "Child process terminated abnormally\n");
	}
	free(path);
	free_leaks(env);
}

void exec_pipe(t_data *data, t_env *env_list)
{
    char **env = env_list_to_char_array(env_list);
    if (!env)
        return;
    char *path = find_path(data->args[0], env);
    if (!path)
    {
        free_leaks(env);
        return;
    }
    if (data->next != NULL)
    {
        int pipefd[2];
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            free(path);
            free_leaks(env);
            return;
        }
        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            close(pipefd[0]);
            close(pipefd[1]);
            free(path);
            free_leaks(env);
            return;
        }
        else if (pid == 0)
        {
            if (data->in != -1)
                dup2(data->in, STDIN_FILENO);
            close(pipefd[0]);
           	dup2(pipefd[1], STDOUT_FILENO);
            execve(path, data->args, env);
            perror(data->args[0]);
        }
        else
        {
            close(pipefd[1]);
            free(path);
            free_leaks(env);
            data->next->in = pipefd[0];
            exec_pipe(data->next, env_list);
            int status;
            waitpid(pid, &status, 0);
			g_exit = status;
        }
    }
    else
    {
        exec_cmd(data, path, env);
    }
}