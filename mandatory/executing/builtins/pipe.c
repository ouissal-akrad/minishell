/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 09:48:12 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/22 11:17:58 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

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

void	execution(char *av[], char **env, int i)
{
	char	*path;
	char	**w_args;
	char	*cmd;

	if (av[i])
	{
		w_args = ft_split(av[i], ' ');
		if (!w_args || !w_args[0])
			return ;
		cmd = w_args[0];
		// path = find_path(cmd, env);
        // printf("===========>%s\n",cmd);
        // printf("=======>path : %s\n",path);
		execve(path, w_args, env);
		free_leaks(w_args);
	}
	return ;
}

char	**env_list_to_char_array(t_env *env_list)
{
	int		count;
	t_env	*curr;
	int		i;
	int		var_len;
	int		val_len;

	count = 0;
	curr = env_list;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	char **env_array = malloc((count + 1) * sizeof(char *));
	i = 0;
	curr = env_list;
	while (curr != NULL)
	{
		var_len = ft_strlen(curr->var);
		val_len = ft_strlen(curr->val);
		char *var_val_str = malloc(var_len + val_len + 2);
		if (!var_val_str)
			return (NULL);
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

// t_data *fill()
// {
//     t_data *data;

//     data->args = (char **) malloc(3 * sizeof(char *));
//     data->args[0] = "ls";
//     data->args[1] = "-l";å
//     data->args[2] = NULL;
//     data->file.in = "input.txt";
//     data->file.out = "output.txt";
//     data->next = NULL;
//     return(data);
// }

void	pipex(t_env *env)
{
    // char *av[] = {"infile", "grep l", "wc -l", "outfile"};
	int		pfd[2];
	// int		id;
	// int		pid;
	char	**env_array;
    
	env_array = env_list_to_char_array(env);
	if (pipe(pfd) == -1)
		return (perror("pipe: "));
    
	close(pfd[0]);
	close(pfd[1]);
	wait(NULL);
	wait(NULL);
}
