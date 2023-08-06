/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 10:24:30 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	split_var_no_quote(t_tokens **tokens)
{
	t_tokens	*tmp;
	t_tokens	*next;
	char		**split;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == WORD && check_char(tmp->str, '\n'))
		{
			next = tmp->next;
			split = ft_split(tmp->str, '\n');
			if (split[1])
				tmp->is_d = 2;
			tmp->next = NULL;
			free(tmp->str);
			tmp->str = ft_strdup(split[0]);
			add_tok_split(split, &tmp, tokens);
			free_str(split);
			tmp->next = next;
		}
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

int	check_remove_null_1(t_tokens *tmp)
{
	if ((tmp && tmp->type == WORD) && ((tmp->is_d == 1 && \
		!ft_strlen(tmp->str)) || check_only_w(tmp->str)))
		return (1);
	return (0);
}

int	check_remove_null_2(t_tokens *tmp)
{
	if (tmp->type == WORD && ((tmp->is_d == 1 && !ft_strlen(tmp->str)) \
		|| check_only_w(tmp->str)))
		return (1);
	return (0);
}
