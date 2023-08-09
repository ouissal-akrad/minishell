/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/09 14:52:28 by bel-idri         ###   ########.fr       */
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

int	open_files_helper(t_data *tmpd, t_tokens *tmp)
{
	if (tmp->type == IN)
		return (do_open_in(tmpd, tmp));
	else if (tmp->type == OUT)
		do_open_out(tmpd, tmp);
	else if (tmp->type == APP)
		do_open_app(tmpd, tmp);
	else if (tmp->type == HDOC)
		tmpd->hdoc = 1;
	return (0);
}

void	amgi_msg(t_data *tmp_data, t_tokens **tmp)
{
	write(2, "minishell: ", 11);
	write(2, (*tmp)->next->var, ft_strlen((*tmp)->next->var));
	write(2, ": ambiguous redirect\n", 21);
	go_to_pipe(tmp);
	tmp_data->in = -1;
}

void	open_files(t_data **data, t_tokens **tokens)
{
	t_tokens	*t;
	t_data		*t_data;

	t = *tokens;
	t_data = *data;
	while (t)
	{
		if (t->type == PIPE)
			t_data = t_data->next;
		if ((t->type == IN || t->type == OUT || t->type == APP
				|| t->type == HDOC) && !g_global.exitt)
		{
			if ((t->next->is_d == 2 || t->next->is_d == 5) && t->type != HDOC)
			{
				amgi_msg(t_data, &t);
				continue ;
			}
			if (open_files_helper(t_data, t))
			{
				go_to_pipe(&t);
				continue ;
			}
		}
		t = t->next;
	}
}
