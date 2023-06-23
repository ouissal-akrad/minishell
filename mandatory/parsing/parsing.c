/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/06/23 06:09:15 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

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

int	count_tokens(char *str)
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
			if ((str[i] == '>' && str[i + 1] == '>') || \
				(str[i] == '<' && str[i + 1] == '<'))
				i++;
			count++;
		}
	}
	return (count * 2);
}

char	*add_spaces(char *str)
{
	char	*new;
	int		quote;
	int		i;
	int		j;

	new = (char *)ft_calloc((int)ft_strlen(str) + count_tokens(str) + 1, 1);
	quote = OQ;
	i = -1;
	j = 0;
	while (str[++i])
	{
		is_quote(str, i, &quote);
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>') && !quote)
		{
			new[j++] = ' ';
			new[j++] = str[i];
			if ((str[i] == '>' && str[i + 1] == '>' && !quote) \
				|| (str[i] == '<' && str[i + 1] == '<' && !quote))
				new[j++] = str[++i];
			new[j++] = ' ';
		}
		else
			new[j++] = str[i];
	}
	return (new);
}

void	add_token(t_tokens **tokens, char *str, t_token type)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = (t_tokens *)malloc(sizeof(t_tokens));
	if (!new)
		exit(1);
	new->str = str;
	new->type = type;
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
	free(str);
	i = -1;
	quote = OQ;
	while (str_spaces[++i])
	{
		is_quote(str_spaces, i, &quote);
		if (str_spaces[i] == ' ' && !quote)
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
		free(tmp->str);
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

void	lexar(char *str, t_tokens **tokens)
{
	int		i;
	int		quote;
	char	**str_t;

	str_t = split_tokens(str);
	i = -1;
	quote = OQ;
	while (str_t[++i])
	{
		is_quote(str_t[i], i, &quote);
		if (!ft_strncmp(str_t[i], "|", ft_strlen(str_t[i])) && !quote)
			add_token(tokens, ft_strdup("|"), PIPE);
		else if (!ft_strncmp(str_t[i], "<", ft_strlen(str_t[i])) && !quote)
			add_token(tokens, ft_strdup("<"), IN);
		else if (!ft_strncmp(str_t[i], ">", ft_strlen(str_t[i])) && !quote)
			add_token(tokens, ft_strdup(">"), OUT);
		else if (!ft_strncmp(str_t[i], ">>", 2) && !quote)
			add_token(tokens, ft_strdup(">>"), APP);
		else if (!ft_strncmp(str_t[i], "<<", 2) && !quote)
			add_token(tokens, ft_strdup("<<"), HDOC);
		else
			add_token(tokens, ft_strdup(str_t[i]), WORD);
	}
	free_str(str_t);
}

int	syntax_error_msg(char *str)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	return (1);
}

int	syntax_error_halper(t_tokens *tmp)
{
	if (!tmp->next)
		return (syntax_error_msg("newline"));
	else if (tmp->next->type == PIPE)
		return (syntax_error_msg("|"));
	else if (tmp->next->type == IN)
		return (syntax_error_msg("<"));
	else if (tmp->next->type == OUT)
		return (syntax_error_msg(">"));
	else if (tmp->next->type == APP)
		return (syntax_error_msg(">>"));
	else if (tmp->next->type == HDOC)
		return (syntax_error_msg("<<"));
	return (0);
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

int	syntax_error(t_tokens *tokens)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;
	int			i;

	tmp = tokens;
	tmp2 = tokens;
	i = 0;
	if (syntax_error_quote(tmp2))
		return (1);
	while (tmp)
	{
		i++;
		if (tmp->type == PIPE && !tmp->next)
			return (syntax_error_msg("newline"));
		else if (tmp->type == PIPE && (tmp->next->type == PIPE || i == 1))
			return (syntax_error_msg("|"));
		else if ((tmp->type == IN || tmp->type == OUT || \
			tmp->type == HDOC || tmp->type == APP) && \
			(!tmp->next || tmp->next->type == PIPE || \
			tmp->next->type == IN || tmp->next->type == OUT \
			|| tmp->next->type == HDOC || tmp->next->type == APP))
			return (syntax_error_halper(tmp), 1);
		tmp = tmp->next;
	}
	return (0);
}

void remove_quotes_halper(t_tokens *tmp, int quote, int i, int *j)
{
	if (tmp->str[i] == '\'')
	{
		if (quote == SQ || quote == OQ)
			return;
	}
	if (tmp->str[i] == '\"')
	{
		if (quote == DQ || quote == OQ)
			return;
	}
	else
		tmp->str[(*j)++] = tmp->str[i];
}

void	remove_quotes(t_tokens **tokens)
{
	t_tokens	*tmp;
	int			quote;
	int			i;
	int			j;

	tmp = *tokens;
	quote = OQ;
	while (tmp)
	{
		i = -1;
		j = 0;
		if (tmp->type == WORD)
		{
			while (tmp->str[++i])
			{
				is_quote(tmp->str, i, &quote);
				remove_quotes_halper(tmp, quote, i, &j);
			}
			tmp->str[j] = '\0';
			printf("str : %s, j : %d\n", tmp->str, j);
		}
		tmp = tmp->next;
	}
}

// void	expand(t_tokens **tokens)
// {
// 	t_tokens	*tmp;
// 	int			i;

// 	remove_quotes(tokens);
// 	tmp = *tokens;
// 	while (tmp)
// 	{
// 		i = -1;
// 		if (tmp->type == WORD)
// 		{
// 			while (tmp->str[++i])
// 			{
// 				if (tmp->str[i] == '$')
// 					expand_env(&tmp->str, i);
// 				else if (tmp->str[i] == '~')
// 					expand_tilde(&tmp->str, i);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }

int	main(int argc, char *argv[], char *env[])
{
	char		*line;
	t_tokens	*tokens;

	(void)argc;
	(void)argv;
	(void)env;
	tokens = NULL;
	line = readline("minishell$ ");
	while (line)
	{
		lexar(line, &tokens);
		if (syntax_error(tokens))
		{
			free_tokens(&tokens);
			line = readline("minishell$ ");
			continue ;
		}
		// expand(&tokens);
		remove_quotes(&tokens);
		free_tokens(&tokens);
		line = readline("minishell$ ");
	}
	return (0);
}
// cat > file
// ls > file
// >>>
// <>
// $?
