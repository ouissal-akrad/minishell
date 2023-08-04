/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_7.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/03 23:11:59 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expanding(t_tokens **tokens, t_env *env)
{
	t_tokens	*tmp;
	t_tokens	*prv;
	char		*str;

	tmp = *tokens;
	prv = tmp;
	while (tmp)
	{
		if (tmp->type == WORD && check_char(tmp->str, '$') && prv->type != HDOC)
		{
			str = expand_env(tmp->str, env, 1);
			free(tmp->str);
			tmp->str = ft_strdup(str);
			free(str);
		}
		prv = tmp;
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

void	remove_null_tokens(t_tokens **tokens)
{
	t_tokens	*tmp;
	t_tokens	*prv;

	tmp = *tokens;
	prv = tmp;
	while (tmp && tmp->type == WORD && tmp->is_d == 1 && !ft_strlen(tmp->str))
	{
		*tokens = tmp->next;
		free_remove(tmp);
		tmp = *tokens;
	}
	while (tmp)
	{
		if (tmp->type == WORD && tmp->is_d == 1 && !ft_strlen(tmp->str))
		{
			prv->next = tmp->next;
			free_remove(tmp);
			tmp = prv->next;
		}
		else
		{
			prv = tmp;
			tmp = tmp->next;
		}
	}
}
