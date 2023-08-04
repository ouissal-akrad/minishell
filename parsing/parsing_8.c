/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_8.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/04 02:11:37 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_no_expanding_valid(char *str)
{
	int	i;

	i = -1;
	if (ft_strlen(str) == 1 && str[0] == '$')
		return (0);
	else if (str[0] == '$' && str[1] != '_' && !ft_isalpha(str[1]))
		return (0);
	return (1);
}

void	ambiguous_redirect(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if ((tmp->type == IN || tmp->type == OUT || tmp->type == APP)
			&& tmp->next->is_d == 1 && !ft_strlen(tmp->next->str))
			tmp->next->is_d = 2;
		else if (tmp->type == HDOC && !check_quotes(tmp->next->str))
			tmp->next->is_d = 3;
		tmp = tmp->next;
	}
}

int	count_n_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			c;

	c = 0;
	tmp = tokens;
	while (tmp)
	{
		c++;
		tmp = tmp->next;
	}
	return (c);
}

void	exit_calloc(t_data **data, t_tokens **tokens)
{
	free_data(*data);
	free_tokens(tokens);
	exit(1);
}

void	ft_lstadddd_back(t_data **data, t_data *new)
{
	t_data	*tmp;

	if (!*data)
	{
		*data = new;
		return ;
	}
	tmp = *data;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
