/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_15.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:26:39 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/10 10:24:42 by bel-idri         ###   ########.fr       */
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

int	syntax_error_quote(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			quote;
	int			i;

	tmp = tokens;
	quote = OQ;
	while (tmp)
	{
		i = -1;
		if (tmp->type == WORD)
		{
			while (tmp->str[++i])
				is_quote(tmp->str, i, &quote);
			if (quote == SQ)
				return (syntax_error_msg("\'"));
			else if (quote == DQ)
				return (syntax_error_msg("\""));
		}
		tmp = tmp->next;
	}
	return (0);
}
