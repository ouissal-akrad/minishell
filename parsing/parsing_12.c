/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_12.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/03 23:13:23 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->var);
		free(tmp->val);
		free(tmp);
	}
}

void	open_files_hdoc_tmp(t_data **data)
{
	t_data	*tmp;
	char	*name_file;
	char	*tmp_name;
	int		i;

	tmp = *data;
	i = 0;
	while (tmp)
	{
		if (tmp->hdoc)
		{
			name_file = ft_strdup("/tmp/hdoc_");
			tmp_name = ft_itoa(i);
			name_file = my_ft_strjoin_1(name_file, tmp_name);
			free(tmp_name);
			unlink(name_file);
			tmp->in = open(name_file, O_WRONLY | O_CREAT, 0644);
			write(tmp->in, tmp->buff, ft_strlen(tmp->buff));
			close(tmp->in);
			tmp->in = open(name_file, O_RDONLY);
			free(name_file);
			i++;
		}
		tmp = tmp->next;
	}
}

void	is_a_directory(t_data **data)
{
	t_data	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (ft_strchr(tmp->args[0], '/'))
		{
			if (access(tmp->args[0], F_OK) == 0)
			{
				if (access(tmp->args[0], X_OK) == 0)
				{
					if (opendir(tmp->args[0]) != NULL)
						tmp->is_dir = 1;
				}
				else
					tmp->is_dir = 2;
			}
			else
				tmp->is_dir = 3;
		}
		else
			tmp->is_dir = 0;
		tmp = tmp->next;
	}
}
