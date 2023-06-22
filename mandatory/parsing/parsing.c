/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/06/22 18:03:52 by bel-idri         ###   ########.fr       */
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
	int quote;

	i = -1;
	count = 0;
	quote = OQ;
	while (str[++i])
	{
		is_quote(str, i, &quote);
		if ((str[i] == '|' || str[i] == '<' || str[i] == '>' ) && !quote)
		{
			if (str[i] == '>' && str[i + 1] == '>')
				i++;
			count++;
		}
	}
	return (count * 2);
}

char	*add_spaces(char *str)
{
	char	*new;
	int	quote;
	int		i;
	int		j;

	new = (char *)ft_calloc((int)ft_strlen(str) + count_tokens(str) + 1, sizeof(char));
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
			if (str[i] == '>' && str[i + 1] == '>')
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

char **split_tokens(char *str)
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
	return(tokens);
}

// void free_tokens(t_tokens **tokens)
// {
// 	t_tokens	*tmp;

// 	while (*tokens)
// 	{
// 		tmp = *tokens;
// 		*tokens = (*tokens)->next;
// 		free(tmp->str);
// 		free(tmp);
// 	}
// }

void free_str(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}

void lexar(char *str, t_tokens **tokens)
{
	int			i;
	int			quote;
	char 		**str_t;

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
		else
			add_token(tokens, ft_strdup(str_t[i]), WORD);
	}
	free_str(str_t);
}

int main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;

	char *line;
	t_tokens *tokens;

	tokens = NULL;

	while ((line = readline("minishell$ ")))
	{
		lexar(line, &tokens);

		while (tokens)
		{
			printf("%s -> %d\n", tokens->str, tokens->type);
			tokens = tokens->next;
		}




		// free_tokens(&tokens);
	}
	return (0);
}
