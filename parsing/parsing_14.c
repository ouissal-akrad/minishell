/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_14.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/09 17:52:26 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expanding_wildcard(t_tokens **tokens)
{
	t_tokens		*tmp;
	char			**names;
	int				count;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == WORD && check_only_w(tmp->str))
		{
			names = reserve_names();
			if (names == NULL)
				return ;
			fill_names(names);
			count = -1;
			while (names[++count])
			{
				ft_lstadd_in_second_place(&tmp, \
					ft_lstnew_token_w(names[count], tmp->var));
				tmp = tmp->next;
			}
			free_leaks(names);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	free_remove(t_tokens *tmp)
{
	if (tmp->str)
		free(tmp->str);
	if (tmp->var)
		free(tmp->var);
	free(tmp);
}

int	do_open_in(t_data *tmpd, t_tokens *tmp)
{
	tmpd->hdoc = 0;
	if (tmpd->in != 0)
		close(tmpd->in);
	tmpd->in = open(tmp->next->str, O_RDONLY);
	if (tmpd->in == -1)
		return (open_files_error(tmp));
	return (0);
}

int	do_open_out(t_data *tmpd, t_tokens *tmp)
{
	tmpd->hdoc = 0;
	if (tmpd->out != 1)
		close(tmpd->out);
	tmpd->out = open(tmp->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmpd->out == -1)
		return (open_files_error(tmp));
	return (0);
}

int	do_open_app(t_data *tmpd, t_tokens *tmp)
{
	tmpd->hdoc = 0;
	if (tmpd->out != 1)
		close(tmpd->out);
	tmpd->out = open(tmp->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (tmpd->out == -1)
		return (open_files_error(tmp));
	return (0);
}
