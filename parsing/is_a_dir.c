/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_12.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/09 15:27:09 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*name_filee(int i)
{
	char	*tmp_name;
	char	*name_file;

	name_file = ft_strdup("/tmp/hdoc_");
	tmp_name = ft_itoa(i);
	name_file = my_ft_strjoin_1(name_file, tmp_name);
	free(tmp_name);
	return (name_file);
}

void	open_files_hdoc_tmp(t_data **data)
{
	t_data	*tmp;
	char	*name_file;
	int		i;

	tmp = *data;
	i = 0;
	while (tmp)
	{
		if (tmp->hdoc)
		{
			name_file = name_filee(i);
			unlink(name_file);
			if (tmp->in != 0 && tmp->in != -1)
				close(tmp->in);
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

void	is_a_dir_helper(t_data *tmp)
{
	DIR	*dir;

	if (ft_strchr(tmp->args[0], '/'))
	{
		if (access(tmp->args[0], F_OK) == 0)
		{
			if (access(tmp->args[0], X_OK) == 0)
			{
				dir = opendir(tmp->args[0]);
				if (dir != NULL)
				{
					closedir(dir);
					tmp->is_dir = 1;
				}
			}
			else
				tmp->is_dir = 2;
		}
		else
			tmp->is_dir = 3;
	}
	else
		tmp->is_dir = 0;
}

void	is_a_directory(t_data **data)
{
	t_data	*tmp;

	tmp = *data;
	while (tmp)
	{
		if (tmp->args != NULL && tmp->args[0] != NULL)
			is_a_dir_helper(tmp);
		else
			tmp->is_dir = 0;
		tmp = tmp->next;
	}
}

int	check_only_w(char *str)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0 || str == NULL)
		return (0);
	if (ft_strlen(str) == 2 && ((str[i] == '\'' && str[i + 1] == '\'')
			|| (str[i] == '\"' && str[i + 1] == '\"')))
		return (0);
	while (str[i])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'') || (str[i] == '\"' && \
			str[i + 1] == '\"'))
		{
			i += 2;
			continue ;
		}
		if (str[i] != '*')
			return (0);
		i++;
	}
	return (1);
}
