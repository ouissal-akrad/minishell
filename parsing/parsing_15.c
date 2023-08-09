/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_15.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:26:39 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/09 15:27:28 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_files(t_data *data)
{
	t_data	*tmp;

	tmp = data;
	while (tmp)
	{
		if (tmp->in != 0 && tmp->in != -1)
			close(tmp->in);
		if (tmp->out != 1 && tmp->out != -1)
			close(tmp->out);
		tmp = tmp->next;
	}
}

void	add_tok_split(char **split, t_tokens **tmp, t_tokens **tokens)
{
	int	i;

	i = 0;
	while (split[++i])
	{
		add_token(tokens, ft_strdup(split[i]), WORD);
		*tmp = (*tmp)->next;
	}
}
