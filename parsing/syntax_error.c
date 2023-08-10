/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 10:20:37 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			i;

	tmp = tokens;
	i = 0;
	if (syntax_error_quote(tokens))
		return (1);
	while (tmp)
	{
		i++;
		if (tmp->type == PIPE && !tmp->next)
			return (syntax_error_hdoc("newline", tokens, i));
		else if (tmp->type == PIPE && (tmp->next->type == PIPE || i == 1))
			return (syntax_error_hdoc("|", tokens, i));
		else if ((tmp->type == IN || tmp->type == OUT || tmp->type == HDOC
				|| tmp->type == APP) && (!tmp->next || tmp->next->type == PIPE
				|| tmp->next->type == IN || tmp->next->type == OUT
				|| tmp->next->type == HDOC || tmp->next->type == APP))
			return (syntax_error_halper(tmp, tokens, i), 1);
		tmp = tmp->next;
	}
	return (0);
}

void	remove_quotes(t_tokens *tokens)
{
	t_tokens	*tmp;
	int			quote;
	int			i;
	int			j;

	quote = OQ;
	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			i = -1;
			j = 0;
			while (tmp->str[++i])
			{
				is_quote(tmp->str, i, &quote);
				if ((tmp->str[i] == '\'' && (quote == SQ || quote == OQ))
					|| (tmp->str[i] == '\"' && (quote == DQ || quote == OQ)))
					continue ;
				tmp->str[j++] = tmp->str[i];
			}
			tmp->str[j] = '\0';
		}
		tmp = tmp->next;
	}
}

char	*replace_space(char *str)
{
	int		i;
	int		j;
	char	*new;

	if (!str)
		return (NULL);
	new = ft_calloc(ft_strlen(str) + 1, 1);
	if (!new)
		return (NULL);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (is_whitespace(str[i]))
			new[j++] = '\n';
		else
			new[j++] = str[i];
	}
	return (new);
}

char	*get_val(char *var, t_env *env, int quote)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, var))
		{
			if (quote == OQ)
				return (replace_space(tmp->val));
			else
				return (ft_strdup(tmp->val));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	count_j(char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j] && (ft_isalnum(str[i + j]) || str[i + j] == '_'))
		j++;
	return (j);
}
