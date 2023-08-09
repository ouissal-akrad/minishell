/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_10.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/09 13:29:56 by ouakrad          ###   ########.fr       */
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

int    open_files_helper(t_data *tmpd, t_tokens *tmp)
{
    if (tmp->type == IN)
    {
        tmpd->hdoc = 0;
        if (tmpd->in != 0)
            close(tmpd->in);
        tmpd->in = open(tmp->next->str, O_RDONLY);
        if (tmpd->in == -1)
            return (open_files_error(tmp));
    }
    else if (tmp->type == OUT)
    {
        if (tmpd->out != 1)
            close(tmpd->out);
        tmpd->out = open(tmp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (tmpd->out == -1)
            return (open_files_error(tmp));
    }
    else if (tmp->type == APP)
    {
        tmpd->hdoc = 0;
        if (tmpd->out != 1)
            close(tmpd->out);
        tmpd->out = open(tmp->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (tmpd->out == -1)
            return (open_files_error(tmp));
    }
    else if (tmp->type == HDOC)
        tmpd->hdoc = 1;
    return (0);
}

void    amgi_msg(t_data *tmp_data, t_tokens **tmp)
{
    write(2, "minishell: ", 11);
    write(2, (*tmp)->next->var, ft_strlen((*tmp)->next->var));
    write(2, ": ambiguous redirect\n", 21);
    go_to_pipe(tmp);
    tmp_data->in = -1;
}

void    open_files(t_data **data, t_tokens **tokens)
{
    t_tokens    *t;
    t_data        *t_data;

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