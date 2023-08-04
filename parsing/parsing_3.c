/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 23:09:15 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/03 23:18:43 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lexar(char *str, t_tokens **tokens)
{
	int		i;
	char	**str_t;

	str_t = split_tokens(str);
	i = -1;
	while (str_t[++i])
	{
		if (!ft_strncmp(str_t[i], "|"))
			add_token(tokens, ft_strdup("|"), PIPE);
		else if (!ft_strncmp(str_t[i], "<"))
			add_token(tokens, ft_strdup("<"), IN);
		else if (!ft_strncmp(str_t[i], ">"))
			add_token(tokens, ft_strdup(">"), OUT);
		else if (!ft_strncmp(str_t[i], ">>"))
			add_token(tokens, ft_strdup(">>"), APP);
		else if (!ft_strncmp(str_t[i], "<<"))
			add_token(tokens, ft_strdup("<<"), HDOC);
		else
			add_token(tokens, ft_strdup(str_t[i]), WORD);
	}
	free_str(str_t);
}

int	check_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
	}
	return (0);
}

int	check_char(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

void	add_is_d(t_tokens **tokens)
{
	t_tokens	*tmp;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == WORD && !check_quotes(tmp->str) && check_char(tmp->str,
				'$'))
			tmp->is_d = 1;
		tmp->var = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
}

int	syntax_error_msg(char *str)
{
	g_global.g_exit = 258;
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
	return (1);
}
