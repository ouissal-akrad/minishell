/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:48:12 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/05 03:18:33 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void    ft_wait(int pid)
// {
//     if (!lines)
//         waitpid(pid, &g_exit, 0);
//     // close(old);
//     // close(fd);
// }

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
			return (NULL);
		new_path = ft_strjoin(tmp, cmd);
		if (!new_path)
			return (NULL);

		if (access(new_path, X_OK) == 0)
			return ( new_path);
	}
	return (NULL);
}

char	*find_path(char *cmd, char *envp[])
{
	int	i;

	if (cmd[0] == '\0')
	{
		g_exit = 127;
		return (NULL);
	}
	if ((ft_strchr(cmd, '/')) || !is_builtins(cmd))
		return (cmd);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp_2(envp[i], "PATH=", 5) == 0)
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
		// free(path);
		// free_leaks(env);
		return ;
	}
	else if (pid == 0)
	{
		signal(SIGINT, sigg);
		signal(SIGQUIT, sigg);
		if (data->in < 0 || data->out < 0)
		{
			g_exit = 1;
			exit(g_exit);
		}
		if (!data->args[0])
		{
			g_exit = 0;
			exit(g_exit);
		}
		if (data->in > 2)
			dup2(data->in, STDIN_FILENO);
		if (data->out > 2)
			dup2(data->out, STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		if (data->is_dir == 0)
		{
			if (!path)
				{
					write(2, "minishell: ", 11);
					write(2, data->args[0], ft_strlen(data->args[0]));
					write(2, ": command not found\n", 20);
					g_exit = 127;
					exit(g_exit);
				}
			 else if(path[ft_strlen(path) - 2] == '.' && path[ft_strlen(path) - 1] == '.')
				{
					write(2, "minishell: ", 11);
					write(2, data->args[0], ft_strlen(data->args[0]));
					write(2, ": command not found\n", 20);
					g_exit = 127;
					exit(g_exit);
				}

			if (!is_builtins(path))
				exec_builtin(data, env_list);
			else if (execve(path, data->args, env) < 0)
			{
				write(2, "minishell: ", 11);
				write(2, data->args[0], ft_strlen(data->args[0]));
				write(2, ": ", 2);
				perror("");
				g_exit = 127;
				exit(g_exit);
			}
			else if(path[ft_strlen(path) - 2] == '.' && path[ft_strlen(path) - 3] == '.')
				{
					write(2, "minishell: ", 11);
					write(2, data->args[0], ft_strlen(data->args[0]));
					write(2, ": command not found\n", 20);
					g_exit = 127;
					exit(g_exit);
				}
		}
		else if (data->is_dir == 1)
		{
			write(2, "minishell: ", 11);
			write(2, data->args[0], ft_strlen(data->args[0]));
			write(2, ": is a directory\n", 17);
			g_exit = 126;
			exit(g_exit);
		}
		else if (data->is_dir == 2)
		{
			write(2, "minishell: ", 11);
			write(2, data->args[0], ft_strlen(data->args[0]));
			write(2, ": Permission denied\n", 20);
			g_exit = 126;
			exit(g_exit);
		}
		else if (data->is_dir == 3)
		{
			write(2, "minishell: ", 11);
			write(2, data->args[0], ft_strlen(data->args[0]));
			write(2, ": No such file or directory\n", 28);
			g_exit = 127;
			exit(g_exit);
		}
	}
	else
	{
		// waitpid(pid, &status, 0);
		// g_exit = status / 256;
		// // free(path);
		// // free_leaks(env);
			waitpid(pid, &status, 0);
			g_exit = status / 256;
		// exit(g_exit); // the is exit is returnrd
	}
}

void	exec_pipe(t_data *data, t_env *env_list)
{
	char	**env;
	char	*path;
	int		pipefd[2];
	pid_t	pid;
	int		status;
	t_data	*tmp;
			// int child_exit_status;

	tmp = data;
	path = ft_strdup("");
	env = env_list_to_char_array(env_list);
	if (!env)
		return ;
	if (tmp->args[0])
		path = find_path(tmp->args[0], env);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		// free(path);
		// free_leaks(env);
		return ;
	}
	if (tmp->next != NULL)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			close(pipefd[0]);
			close(pipefd[1]);
			// free(path);
			// free_leaks(env);
			return ;
		}
		if (pid == 0)
		{
			signal(SIGINT, sigg);
			signal(SIGQUIT, sigg);
			if (tmp->in < 0 || tmp->out < 0)
			{
				g_exit = 1;
				exit(g_exit);
			}
			if (!data->args[0])
			{
				g_exit = 0;
				exit(g_exit);
			}
			if (tmp->in > 2)
				dup2(tmp->in, STDIN_FILENO);
			if (tmp->out > 2)
				dup2(tmp->out, STDOUT_FILENO);
			else if (tmp->out == 1)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]);
			close(pipefd[1]);
			if (tmp->is_dir == 0)
			{
				if (!path )
				{
					write(2, "minishell: ", 11);
					write(2, tmp->args[0], ft_strlen(tmp->args[0]));
					write(2, ": command not found\n", 20);
					g_exit = 127;
					exit(g_exit);
				}
			 	else if(path[ft_strlen(path) - 2] == '.' && path[ft_strlen(path) - 1] == '.')
				{
					write(2, "minishell: ", 11);
					write(2, data->args[0], ft_strlen(data->args[0]));
					write(2, ": command not found\n", 20);
					g_exit = 127;
					exit(g_exit);
				}
				if (!is_builtins(path))
					exec_builtin(data, &env_list);
				else if (execve(path, data->args, env) < 0)
				{
					perror("minishell");
					g_exit = 127;
					exit(g_exit);
				}
			}
			// if (!path && tmp->is_dir == 0)
			// {
			// 	write(2, "minishell: ", 11);
			// 	write(2, tmp->args[0], ft_strlen(tmp->args[0]));
			// 	write(2, ": command not found\n", 20);
			// 	g_exit = 127;
			// 	// return ;
			// }
			else if (tmp->is_dir == 1)
			{
				write(2, "minishell: ", 11);
				write(2, tmp->args[0], ft_strlen(tmp->args[0]));
				write(2, ": Is a directory\n", 17);
				g_exit = 126;
				exit(g_exit);
			}
			else if (tmp->is_dir == 2)
			{
				write(2, "minishell: ", 11);
				write(2, tmp->args[0], ft_strlen(tmp->args[0]));
				write(2, ": Permission denied\n", 20);
				g_exit = 126;
				exit(g_exit);
			}
			else if (tmp->is_dir == 3)
			{
				write(2, "minishell: ", 11);
				write(2, tmp->args[0], ft_strlen(tmp->args[0]));
				write(2, ": No such file or directory\n", 28);
				g_exit = 127;
				exit(g_exit);
			}
		}
		else if (pid > 0)
		{
			// free(path);
			// free_leaks(env);
			close(pipefd[1]);
			if (tmp->next->in == 0)
				tmp->next->in = pipefd[0];
			exec_pipe(tmp->next, env_list);
				waitpid(pid, &status, 0);
			// g_exit = status / 256;
			// waitpid(pid, &status, 0);
			// g_exit = status / 256;
		}
		// else if (pid > 0)
		// {
			// free(path);
			// free_leaks(env);
			// close(pipefd[1]);
			// if (tmp->next->in == 0)
			// 	tmp->next->in = pipefd[0];
			// exec_pipe(tmp->next, env_list);
			// waitpid(pid, &status, 0);
			// g_exit = WIFEXITED(status) ? WEXITSTATUS(status) : 1;
		// }
	}
	else
	{
		exec_cmd(tmp, path, env, &env_list, pipefd);
		////// exit(g_exit);
	}
	close_files(data);
}
