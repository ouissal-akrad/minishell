/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_14.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 10:24:05 by bel-idri         ###   ########.fr       */
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
