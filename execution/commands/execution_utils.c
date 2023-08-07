/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 01:38:47 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/07 02:01:04 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	return (free_leaks(paths), NULL);
}

char	*find_path(char *cmd, char *envp[])
{
	int	i;

	if (cmd[0] == '\0')
	{
		g_global.g_exit = 127;
		return (NULL);
	}
	if ((ft_strchr(cmd, '/')) || !is_builtins(cmd))
		return (ft_strdup(cmd));
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp_2(envp[i], "PATH=", 5) == 0)
			return (join_path(envp[i] + 5, cmd));
	}
	return (ft_strdup(cmd));
}

char	**env_list_to_char_array(t_env *env_list, int i)
{
	t_env	*curr;
	int		var_len;
	int		val_len;
	char	**env_array;
	char	*var_val_str;

	env_array = malloc((ft_lstsizee(env_list) + 1) * sizeof(char *));
	if (!env_array)
		return (NULL);
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
