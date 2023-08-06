/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 10:18:47 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	is_quote(char *str, int i, int *quote)
{
	if (str[i] == '\'' && !*quote)
		*quote = SQ;
	else if (str[i] == '\'' && *quote == SQ)
		*quote = OQ;
	else if (str[i] == '\"' && !*quote)
		*quote = DQ;
	else if (str[i] == '\"' && *quote == DQ)
		*quote = OQ;
}

char	*my_ft_strjoin_1(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < ft_strlen(s1))
		str[i] = s1[i];
	while (++j < ft_strlen(s2))
	{
		str[i] = s2[j];
		i++;
	}
	free(s1);
	return (str);
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || \
		c == '\f' || c == '\r');
}

int	count_tok(char *str)
{
	int	i;
	int	count;
	int	quote;

	i = -1;
	count = 0;
	quote = OQ;
	while (str[++i])
	{
		is_quote(str, i, &quote);
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && !quote)
		{
			if ((str[i] == '>' && str[i + 1] == '>') || (str[i] == '<' \
				&& str[i + 1] == '<'))
				i++;
			count++;
		}
	}
	return (count * 2);
}

void	add_spaces_handler(char *str, char *new)
{
	int	quote;
	int	i;
	int	j;

	i = -1;
	j = 0;
	quote = OQ;
	while (str[++i])
	{
		is_quote(str, i, &quote);
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && !quote)
		{
			new[j++] = ' ';
			new[j++] = str[i];
			if ((str[i] == '>' && str[i + 1] == '>' && !quote) || \
				(str[i] == '<' && str[i + 1] == '<' && !quote))
				new[j++] = str[++i];
			new[j++] = ' ';
		}
		else
			new[j++] = str[i];
	}
}
