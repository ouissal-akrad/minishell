/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 10:19:28 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_spaces(char *str)
{
	char	*new;

	new = ft_calloc(ft_strlen(str) + count_tok(str) + 1, sizeof(char));
	if (!new)
		return (NULL);
	add_spaces_handler(str, new);
	return (new);
}

void	add_token(t_tokens **tokens, char *str, t_token type)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = ft_calloc(1, sizeof(t_tokens));
	if (!new)
		return ;
	new->str = str;
	new->type = type;
	new->is_d = 0;
	new->var = NULL;
	new->next = NULL;
	if (!*tokens)
		*tokens = new;
	else
	{
		tmp = *tokens;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

char	**split_tokens(char *str)
{
	char	**tokens;
	int		i;
	int		quote;
	char	*str_spaces;

	str_spaces = add_spaces(str);
	i = -1;
	quote = OQ;
	while (str_spaces[++i])
	{
		is_quote(str_spaces, i, &quote);
		if (!quote && is_whitespace(str_spaces[i]))
			str_spaces[i] = '\n';
	}
	tokens = ft_split(str_spaces, '\n');
	free(str_spaces);
	return (tokens);
}

void	free_tokens(t_tokens **tokens)
{
	t_tokens	*tmp;

	while (*tokens)
	{
		tmp = *tokens;
		*tokens = (*tokens)->next;
		if (tmp->str)
			free(tmp->str);
		if (tmp->var)
			free(tmp->var);
		free(tmp);
	}
}

void	free_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
