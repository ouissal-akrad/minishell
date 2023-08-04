/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_11.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:08:50 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/04 02:20:13 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_files(t_data **data, t_tokens **tokens)
{
	t_tokens	*tmp;
	t_data		*tmp_data;

	tmp = *tokens;
	tmp_data = *data;
	while (tmp)
	{
		if (tmp->type == PIPE)
			tmp_data = tmp_data->next;
		if ((tmp->type == IN || tmp->type == OUT || tmp->type == APP
				|| tmp->type == HDOC) && !g_global.exitt)
		{
			if (tmp->next->is_d == 2 && tmp->type != HDOC)
			{
				error_ambg(tmp_data, &tmp);
				continue ;
			}
			if (open_files_helper(tmp_data, tmp))
			{
				error_files(&tmp);
				continue ;
			}
		}
		tmp = tmp->next;
	}
}

void	open_hdoc_helper(t_data **tmp_data, t_tokens *tmp, t_env *env)
{
	char	*line;

	while (1)
	{
		signal(SIGINT, sig_handler);
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

void	free_data(t_data *data)
{
	t_data	*tmp;
	t_data	*next;
	int		i;

	tmp = data;
	while (tmp != NULL)
	{
		next = tmp->next;
		i = 0;
		if (tmp->args != NULL)
		{
			while (tmp->args[i] != NULL)
				free(tmp->args[i++]);
			free(tmp->args);
		}
		if (tmp->buff != NULL)
			free(tmp->buff);
		free(tmp);
		tmp = next;
	}
}
