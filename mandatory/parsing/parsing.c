/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/29 23:52:11 by bel-idri         ###   ########.fr       */
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
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
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
			if ((str[i] == '>' && str[i + 1] == '>') || \
				(str[i] == '<' && str[i + 1] == '<'))
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

char	*add_spaces(char *str)
{
	char	*new;

	new = ft_calloc(ft_strlen(str) + count_tok(str) + 1, sizeof(char));
	if (!new)
	{
		free(str);
		exit(1);
	}
	add_spaces_handler(str, new);
	return (new);
}

void	add_token(t_tokens **tokens, char *str, t_token type)
{
	t_tokens	*new;
	t_tokens	*tmp;

	new = ft_calloc(1, sizeof(t_tokens));
	if (!new)
	{
		free_tokens(tokens);
		exit(1);
	}
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

void	lexar(char *str, t_tokens **tokens)
{
	int		i;
	int		quote;
	char	**str_t;

	str_t = split_tokens(str);
	i = -1;
	while (str_t[++i])
	{
		quote = OQ;
		is_quote(str_t[i], i, &quote);
		if (!ft_strcmp(str_t[i], "|") && !quote)
			add_token(tokens, ft_strdup("|"), PIPE);
		else if (!ft_strcmp(str_t[i], "<") && !quote)
			add_token(tokens, ft_strdup("<"), IN);
		else if (!ft_strcmp(str_t[i], ">") && !quote)
			add_token(tokens, ft_strdup(">"), OUT);
		else if (!ft_strcmp(str_t[i], ">>") && !quote)
			add_token(tokens, ft_strdup(">>"), APP);
		else if (!ft_strcmp(str_t[i], "<<") && !quote)
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
		if (tmp->type == WORD && !check_quotes(tmp->str) \
			&& check_char(tmp->str, '$'))
			tmp->is_d = 1;
		tmp->var = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
}

int	syntax_error_msg(char *str)
{
	write(2, "minishell: syntax error near unexpected token `", 2);
	write(2, str, ft_strlen(str));
	write(2, "'\n", 2);
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
	int			i;

	tmp = tokens;
	i = 0;
	if (syntax_error_quote(tokens))
		return (1);
	while (tmp)
	{
		i++;
		if (tmp->type == PIPE && !tmp->next)
			return (syntax_error_msg("newline"));
		else if (tmp->type == PIPE && (tmp->next->type == PIPE || i == 1))
			return (syntax_error_msg("|"));
		else if ((tmp->type == IN || tmp->type == OUT || tmp->type == HDOC \
				|| tmp->type == APP) && (!tmp->next || tmp->next->type == PIPE \
				|| tmp->next->type == IN || tmp->next->type == OUT \
				|| tmp->next->type == HDOC || tmp->next->type == APP))
			return (syntax_error_halper(tmp), 1);
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
				if ((tmp->str[i] == '\'' && (quote == SQ || quote == OQ)) \
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

	new = ft_calloc(ft_strlen(str) + 1, 1);
	if (!new)
	{
		free(str);
		exit(1);
	}
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
		if (!ft_strcmp(tmp->var, var))
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

int	expand_env_halper_2(int *i, char *str, t_expvar *exp)
{
	char	*ex_s;

	if ((str[*i + 1] == '\"' && exp->quote != DQ) \
		|| str[*i + 1] == '\'' || str[*i + 1] == '?')
	{
		if (str[*i + 1] == '?')
		{
			ex_s = ft_itoa(9999);
			exp->final = my_ft_strjoin_1(exp->final, ex_s);
			free(ex_s);
		}
		if (str[*i + 1] != '\"' && str[*i + 1] != '\'')
			*i = *i + 1;
		is_quote(str, *i, &exp->quote);
		return (1);
	}
	return (0);
}

int	expand_env_halper(char *str, int *i, t_expvar *exp, t_env *env)
{
	exp->backup[exp->k - 1] = '\0';
	exp->k = 0;
	exp->final = my_ft_strjoin_1(exp->final, exp->backup);
	if (expand_env_halper_2(i, str, exp))
		return (1);
	exp->j = count_j(str, *i);
	if (exp->j == 1)
	{
		exp->final = my_ft_strjoin_1(exp->final, "$");
		return (1);
	}
	exp->var = ft_substr(str, *i + 1, exp->j - 1);
	exp->val = get_val(exp->var, env, exp->quote);
	free(exp->var);
	if (exp->val)
	{
		exp->final = my_ft_strjoin_1(exp->final, exp->val);
		free(exp->val);
	}
	*i = *i + exp->j - 1;
	return (0);
}

void	exit_calloc_2(char *str)
{
	free(str);
	exit(1);
}

int	the_big_check(char *str, int i, int state, t_expvar exp)
{
	if ((state && ((str[i] == '$' && exp.quote != SQ) && ((ft_isalpha \
		(str[i + 1])) || str[i + 1] == '_' || str[i + 1] == '?' || \
		str[i + 1] == '\'' || str[i + 1] == '\"'))) || \
		((!state && (str[i] == '$' && ((ft_isalpha(str[i + 1])) \
		|| str[i + 1] == '_' || str[i + 1] == '?' || str[i + 1] == '\'' \
		|| str[i + 1] == '\"')))))
		return (1);
	return (0);
}

char	*expand_env(char *str, t_env *env, int state)
{
	int			i;
	t_expvar	exp;

	exp.quote = OQ;
	exp.backup = ft_calloc(ft_strlen(str) + 1, 1);
	if (!exp.backup)
		exit_calloc_2(str);
	exp.final = ft_strdup("");
	i = -1;
	exp.k = 0;
	while (str[++i])
	{
		exp.backup[exp.k++] = str[i];
		is_quote(str, i, &exp.quote);
		if (the_big_check(str, i, state, exp))
		{
			if (expand_env_halper(str, &i, &exp, env))
				continue ;
		}
	}
	exp.backup[exp.k] = '\0';
	exp.final = my_ft_strjoin_1(exp.final, exp.backup);
	free(exp.backup);
	return (exp.final);
}

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
		if ((tmp->type == IN || tmp->type == OUT || tmp->type == APP) \
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
	free_data(data);
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

void	ft_lstnewnode(t_data *new, t_tokens **tokens)
{
	int	j;

	j = 0;
	while ((*tokens))
	{
		if ((*tokens)->type == WORD)
			new->args[j++] = ft_strdup((*tokens)->str);
		else if ((*tokens)->type == IN || (*tokens)->type == OUT \
			|| (*tokens)->type == APP \
			|| (*tokens)->type == HDOC)
			(*tokens) = (*tokens)->next;
		else if ((*tokens)->type == PIPE)
			break ;
		(*tokens) = (*tokens)->next;
	}
	new->in = 0;
	new->out = 1;
	new->next = NULL;
}

void	creat_nodes(t_data **data, t_tokens **tokens)
{
	t_tokens	*tmp;
	t_data		*new;

	tmp = *tokens;
	while (tmp)
	{
		new = ft_calloc(1, sizeof(t_data));
		if (!new)
			exit_calloc(data, tokens);
		new->args = ft_calloc(count_n_tokens(tmp) + 1, sizeof(char *));
		if (!new->args)
			exit_calloc(data, tokens);
		ft_lstnewnode(new, &tmp);
		ft_lstadddd_back(data, new);
		if (tmp)
			tmp = tmp->next;
	}
}

void	go_to_pipe(t_tokens **tokens)
{
	while (*tokens)
	{
		if ((*tokens)->type == PIPE)
			break ;
		*tokens = (*tokens)->next;
	}
}

void	open_files_error(t_tokens *tmp)
{
	write(2, "minishell: ", 11);
	write(2, tmp->next->str, ft_strlen(tmp->next->str));
	write(2, ": ", 2);
	perror("");
	go_to_pipe(&tmp);
}

void	open_hdoc_helper(t_data *tmp_data, t_tokens *tmp, \
	t_env *env, char *name)
{
	char		*line;
	char		*exp;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, tmp->next->str))
			break ;
		if (tmp->next->is_d == 3)
		{
			exp = expand_env(line, env, 0);
			free(line);
			line = ft_strdup(exp);
			free(exp);
		}
		write(tmp_data->in, line, ft_strlen(line));
		write(tmp_data->in, "\n", 1);
		free(line);
	}
	close(tmp_data->in);
	tmp_data->in = open(name, O_RDONLY);
	free(name);
	free(line);
}

char	*my_ft_strjoin_2(char *s1, char *s2)
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
	free(s2);
	return (str);
}

void	open_hdoc(t_data **data, t_tokens **tokens, t_env *env)
{
	t_tokens	*tmp;
	t_data		*tmp_data;
	int			n;
	char		*name;

	tmp = *tokens;
	tmp_data = *data;
	n = 0;
	while (tmp)
	{
		if (tmp->type == PIPE)
			tmp_data = tmp_data->next;
		if (tmp->type == HDOC)
		{
			name = my_ft_strjoin_2("/tmp/hdoc", ft_itoa(n++));
			tmp_data->in = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (tmp_data->in == -1)
				open_files_error(tmp);
			open_hdoc_helper(tmp_data, tmp, env, name);
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	open_files_helper(t_data *tmp_data, t_tokens *tmp)
{
	if (tmp->type == IN)
	{
		tmp_data->in = open(tmp->next->str, O_RDONLY);
		if (tmp_data->in == -1)
			open_files_error(tmp);
	}
	else if (tmp->type == OUT)
	{
		tmp_data->out = open(tmp->next->str, \
			O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (tmp_data->out == -1)
			open_files_error(tmp);
	}
	else if (tmp->type == APP)
	{
		tmp_data->out = open(tmp->next->str, \
			O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (tmp_data->out == -1)
			open_files_error(tmp);
	}
	if (tmp)
		tmp = tmp->next;
}

void	open_files(t_data **data, t_tokens **tokens)
{
	t_tokens	*tmp;
	t_data		*tmp_data;

	tmp = *tokens;
	tmp_data = *data;
	while (tmp)
	{
		if (tmp->type == PIPE)
			tmp_data = tmp_data->next;
		if (tmp->type == IN || tmp->type == OUT || tmp->type == APP)
		{
			if (tmp->next->is_d == 2)
			{
				write(2, "minishell: ", 11);
				write(2, tmp->next->var, ft_strlen(tmp->next->var));
				write(2, ": ambiguous redirect\n", 21);
				go_to_pipe(&tmp);
				tmp_data->in = -1;
				continue ;
			}
			open_files_helper(tmp_data, tmp);
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	create_data(t_data **data, t_tokens **tokens, t_env *env)
{
	creat_nodes(data, tokens);
	open_hdoc(data, tokens, env);
	open_files(data, tokens);
}

void	free_data(t_data **data)
{
	t_data	*tmp;
	t_data	*prev;
	int		i;

	tmp = *data;
	while (tmp)
	{
		prev = tmp;
		i = -1;
		while (tmp->args[++i])
			free(tmp->args[i]);
		if (tmp->args)
			free(tmp->args);
		tmp = tmp->next;
		free(prev);
	}
}

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->var);
		free(tmp->val);
		free(tmp);
	}
}

void	close_files(t_data *data)
{
	t_data	*tmp;

	tmp = data;
	while (tmp)
	{
		if (tmp->in != 0)
			close(tmp->in);
		if (tmp->out != 1)
			close(tmp->out);
		tmp = tmp->next;
	}
}
