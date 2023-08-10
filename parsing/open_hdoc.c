/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_11.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/10 07:38:20 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_hdoc_helper(t_data **tmp_data, t_tokens *tmp, t_env *env)
{
	char	*line;

	while (1)
	{
		g_global.exitt = 1;
		line = readline("> ");
		if (!line)
		{
			rl_hdoc();
			break ;
		}
		if (!ft_strncmp(line, tmp->next->str))
			break ;
		if (tmp->next->is_d == 3)
			line = get_line(line, env);
		if (!(*tmp_data)->buff)
			(*tmp_data)->buff = ft_strdup(line);
		else
			(*tmp_data)->buff = my_ft_strjoin_1((*tmp_data)->buff, line);
		(*tmp_data)->buff = my_ft_strjoin_1((*tmp_data)->buff, "\n");
		free(line);
	}
	if (line)
		free(line);
}

void	open_hdoc(t_data **data, t_tokens **tokens, t_env *env)
{
	t_tokens	*tmp;
	t_data		*tmp_data;

	tmp = *tokens;
	tmp_data = *data;
	while (tmp)
	{
		if (tmp->type == PIPE)
			tmp_data = tmp_data->next;
		if (tmp->type == HDOC && !g_global.exitt)
		{
			free(tmp_data->buff);
			tmp_data->buff = NULL;
			open_hdoc_helper(&tmp_data, tmp, env);
			if (ttyname(0) == NULL)
			{
				dup2(g_global.backup_stdin, 0);
				close(g_global.backup_stdin);
				write(1, "\n", 1);
			}
			else
				g_global.exitt = 0;
		}
		tmp = tmp->next;
	}
}

void	create_data(t_data **data, t_tokens **tokens, t_env *env)
{
	creat_nodes(data, tokens);
	open_hdoc(data, tokens, env);
	open_files(data, tokens);
}

void	free_data(t_data **data)
{
	t_data	*tmp;
	t_data	*prev;
	int		i;

	tmp = *data;
	while (tmp)
	{
		prev = tmp;
		i = -1;
		if (tmp->args != NULL)
		{
			while (tmp->args[++i] != NULL)
				free(tmp->args[i]);
			free(tmp->args);
		}
		if (tmp->buff != NULL)
			free(tmp->buff);
		tmp = tmp->next;
		free(prev);
	}
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		if (tmp->var != NULL)
			free(tmp->var);
		if (tmp->val != NULL)
			free(tmp->val);
		free(tmp);
	}
}
