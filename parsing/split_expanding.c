/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expanding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/10 17:01:13 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	if_split_null(t_tokens *tmp, char **split)
{
	tmp->is_d = 2;
	free(tmp->str);
	free_str(split);
	tmp->str = ft_strdup("");
}

void	if_split(t_tokens *tmp, char **split)
{
	if (split[1])
		tmp->is_d = 2;
	tmp->next = NULL;
	free(tmp->str);
	tmp->str = ft_strdup(split[0]);
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
			if (!split[0])
			{
				if_split_null(tmp, split);
				continue ;
			}
			if_split(tmp, split);
			add_tok_split(split, &tmp, tokens);
			free_str(split);
			tmp->next = next;
		}
		tmp = tmp->next;
	}
}

int	check_remove_null_1(t_tokens *tmp)
{
	if (tmp && tmp->type == WORD && (tmp->is_d == 1 && !ft_strlen(tmp->str)))
		return (1);
	return (0);
}

int	check_remove_null_2(t_tokens *tmp)
{
	if (tmp->type == WORD && (tmp->is_d == 1 && !ft_strlen(tmp->str)))
		return (1);
	return (0);
}
