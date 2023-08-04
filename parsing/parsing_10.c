/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/03 23:18:43 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_line(char *line, t_env *env)
{
	char	*exp;

	exp = expand_env(line, env, 0);
	free(line);
	line = ft_strdup(exp);
	free(exp);
	return (line);
}

char	*my_ft_strjoin_2(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	while (++j < ft_strlen(s2))
	{
		str[i] = s2[j];
		i++;
	}
	free(s2);
	return (str);
}

int	open_files_helper(t_data *tmp_d, t_tokens *tmp)
{
	if (tmp->type == IN)
	{
		tmp_d->hdoc = 0;
		tmp_d->in = open(tmp->next->str, O_RDONLY);
		if (tmp_d->in == -1)
			return (open_files_error(tmp));
	}
	else if (tmp->type == OUT)
	{
		tmp_d->hdoc = 0;
		tmp_d->out = open(tmp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp_d->out == -1)
			return (open_files_error(tmp));
	}
	else if (tmp->type == APP)
	{
		tmp_d->hdoc = 0;
		tmp_d->out = open(tmp->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp_d->out == -1)
			return (open_files_error(tmp));
	}
	else if (tmp->type == HDOC)
		tmp_d->hdoc = 1;
	return (0);
}

void	error_ambg(t_data *tmp_data, t_tokens **tmp)
{
	write(2, "minishell: ", 11);
	write(2, (*tmp)->next->var, ft_strlen((*tmp)->next->var));
	write(2, ": ambiguous redirect\n", 21);
	g_global.g_exit = 1;
	tmp_data->in = -1;
	go_to_pipe(tmp);
}

void	error_files(t_tokens **tmp)
{
	g_global.g_exit = 1;
	go_to_pipe(tmp);
}
