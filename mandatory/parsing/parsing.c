/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/26 17:42:30 by bel-idri         ###   ########.fr       */
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

char	*add_spaces(char *str)
{
	char	*new;
	int		quote;
	int		i;
	int		j;

	new = (char *)ft_calloc((int)ft_strlen(str) + count_tok(str) + 1, 1);
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

	new = ft_calloc(1, sizeof(t_tokens));
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

int	check_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
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
			&& check_dollar(tmp->str))
			tmp->is_d = 1;
		tmp->var = ft_strdup(tmp->str);
		tmp = tmp->next;
	}
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
		i = -1;
		j = 0;
		while (tmp->str[++i])
		{
			is_quote(tmp->str, i, &quote);
			if (tmp->str[i] == '\'' && (quote == SQ || quote == OQ))
				continue ;
			else if (tmp->str[i] == '\"' && (quote == DQ || quote == OQ))
				continue ;
			else
				tmp->str[j++] = tmp->str[i];
		}
		tmp->str[j] = '\0';
		tmp = tmp->next;
	}
}

char	*replace_space(char *str)
{
	int		i;
	int		j;
	char	*new;

	new = (char *)ft_calloc(ft_strlen(str) + 1, 1);
	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == ' ')
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

int	expand_env_halper(char *str, int *i, t_expvar *exp, t_env *env)
{
	exp->backup[exp->k - 1] = '\0';
	exp->k = 0;
	exp->final = ft_strjoin(exp->final, exp->backup);
	if ((str[*i + 1] == '\"' && exp->quote != DQ) || \
		str[*i + 1] == '\'' || str[*i + 1] == '?')
	{
		if (str[*i + 1] == '?')
			exp->final = ft_strjoin(exp->final, ft_itoa(9999));
		if (str[*i + 1] != '\"' && str[*i + 0] != '\'')
			*i = *i + 1;
		is_quote(str, *i, &exp->quote);
		return (1);
	}
	exp->j = count_j(str, *i);
	if (exp->j == 1)
	{
		exp->final = ft_strjoin(exp->final, "$");
		return (1);
	}
	exp->var = ft_substr(str, *i + 1, exp->j - 1);
	exp->val = get_val(exp->var, env, exp->quote);
	free(exp->var);
	if (exp->val)
	{
		exp->final = ft_strjoin(exp->final, exp->val);
		free(exp->val);
	}
	*i = *i + exp->j - 1;
	return (0);
}

char	*expand_env(char *str, t_env *env)
{
	int			i;
	t_expvar	exp;

	exp.final = ft_strdup("");
	i = -1;
	exp.quote = OQ;
	exp.backup = ft_calloc(ft_strlen(str) + 1, 1);
	exp.k = 0;
	while (str[++i])
	{
		exp.backup[exp.k++] = str[i];
		is_quote(str, i, &exp.quote);
		if ((str[i] == '$' && exp.quote != SQ) && ((ft_isalpha(str[i + 1])) \
			|| str[i + 1] == '_' || str[i + 1] == '?' || str[i + 1] == '\'' \
			|| str[i + 1] == '\"'))
		{
			if (expand_env_halper(str, &i, &exp, env))
				continue ;
		}
	}
	exp.backup[exp.k] = '\0';
	exp.final = ft_strjoin(exp.final, exp.backup);
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
		if (tmp->type == WORD && check_dollar(tmp->str) && prv->type != HDOC)
		{
			str = expand_env(tmp->str, env);
			free(tmp->str);
			tmp->str = ft_strdup(str);
			free(str);
		}
		prv = tmp;
		tmp = tmp->next;
	}
}

int	check_newline(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\n')
			return (1);
	}
	return (0);
}

void	split_var_no_quote(t_tokens **tokens)
{
	t_tokens	*tmp;
	t_tokens	*next;
	int			i;
	char		**split;

	tmp = *tokens;
	while (tmp)
	{
		if (tmp->type == WORD && check_newline(tmp->str))
		{
			next = tmp->next;
			split = ft_split(tmp->str, '\n');
			if (split[1])
				tmp->is_d = 2;
			tmp->next = NULL;
			free(tmp->str);
			tmp->str = ft_strdup(split[0]);
			i = 0;
			while (split[++i])
			{
				add_token(tokens, ft_strdup(split[i]), WORD);
				tmp = tmp->next;
			}
			free_str(split);
			tmp->next = next;
		}
		tmp = tmp->next;
	}
}

void	remove_null_tokens(t_tokens **tokens)
{
	t_tokens	*tmp;
	t_tokens	*prv;

	tmp = *tokens;
	prv = tmp;
	while (tmp)
	{
		if (tmp->type == WORD && tmp->is_d == 1 && !ft_strlen(tmp->str))
		{
			prv->next = tmp->next;
			free(tmp->str);
			free(tmp);
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
		{
			tmp->next->is_d = 2;
			return ;
		}
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

void	creat_nodes(t_data **data, t_tokens *tokens, t_env *env)
{
	t_tokens	*tmp;
	t_data		*new;
	t_data		*tmp_data;
	int			i;
	int			j;

	tmp = tokens;
	i = 0;
	while (tmp)
	{
		new = (t_data *)malloc(sizeof(t_data));
		if (!new)
			exit(1);
		new->args = ft_calloc(count_n_tokens(tokens) + 1, sizeof(char *));
		j = 0;
		while (tmp)
		{
			if (tmp->type == WORD)
				new->args[j++] = ft_strdup(tmp->str);
			else if (tmp->type == IN || tmp->type == OUT || \
				tmp->type == APP || tmp->type == HDOC)
				tmp = tmp->next;
			else if (tmp->type == PIPE)
				break ;
			tmp = tmp->next;
		}
		new->env = env;
		new->in = 0;
		new->out = 1;
		new->next = NULL;
		tmp_data = *data;
		if (!*data)
			*data = new;
		else
		{
			while (tmp_data->next)
				tmp_data = tmp_data->next;
			tmp_data->next = new;
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void go_to_pipe(t_tokens **tokens)
{

	while (*tokens)
	{
		if ((*tokens)->type == PIPE)
			break ;
		*tokens = (*tokens)->next;
	}
}

void	open_hdoc(t_data **data, t_tokens *tokens, t_env *env)
{
	t_tokens	*tmp;
	t_data		*tmp_data;
	char		*line;
	char		*exp;
	int			i;

	tmp = tokens;
	i = 0;
	tmp_data = *data;
	while (tmp)
	{
		if (tmp->type == PIPE)
			tmp_data = tmp_data->next;
		if (tmp->type == HDOC)
		{
			unlink("/tmp/hdoc");
			tmp_data->in = open("/tmp/hdoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (tmp_data->in == -1)
			{
				write(2, "minishell: ", 11);
				write(2, tmp->next->str, ft_strlen(tmp->next->str));
				write(2, ": ", 2);
				perror("");
				go_to_pipe(&tmp);
			}
			line = readline("> ");
			while (ft_strcmp(line, tmp->next->str))
			{
				if (tmp->next->is_d == 3)
				{
					exp = expand_env(line, env);
					free(line);
					line = ft_strdup(exp);
					free(exp);
				}
				write(tmp_data->in, line, ft_strlen(line));
				write(tmp_data->in, "\n", 1);
				free(line);
				line = readline("> ");
			}
			free(line);
			tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
}


void	open_files(t_data **data, t_tokens *tokens)
{
	t_tokens	*tmp;
	t_data		*tmp_data;

	tmp = tokens;
	tmp_data = *data;
	while (tmp)
	{
		if (tmp->type == PIPE)
			tmp_data = tmp_data->next;
		if (tmp->type == IN || tmp->type == OUT \
			|| tmp->type == APP)
		{
			if (tmp->next->is_d == 2)
			{
				write(2, "minishell: ", 11);
				write(2, tmp->next->var, ft_strlen(tmp->next->var));
				write(2, ": ambiguous redirect\n", 21);
				tmp_data->in = -1;
				go_to_pipe(&tmp);
				continue ;
			}
			else if (tmp->type == IN)
			{
				tmp_data->in = open(tmp->next->str, O_RDONLY);
				if (tmp_data->in == -1)
				{
					write(2, "minishell: ", 11);
					write(2, tmp->next->str, ft_strlen(tmp->next->str));
					write(2, ": ", 2);
					perror("");
					go_to_pipe(&tmp);
				}
			}
			else if (tmp->type == OUT)
			{
				tmp_data->out = open(tmp->next->str, \
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (tmp_data->out == -1)
				{
					write(2, "minishell: ", 11);
					write(2, tmp->next->str, ft_strlen(tmp->next->str));
					write(2, ": ", 2);
					perror("");
					go_to_pipe(&tmp);
				}
			}
			else if (tmp->type == APP)
			{
				tmp_data->out = open(tmp->next->str, O_WRONLY \
					| O_CREAT | O_APPEND, 0644);
				if (tmp_data->out == -1)
				{
					write(2, "minishell: ", 11);
					write(2, tmp->next->str, ft_strlen(tmp->next->str));
					write(2, ": ", 2);
					perror("");
					go_to_pipe(&tmp);
				}
			}
			if (tmp)
				tmp = tmp->next;
		}
		if (tmp)
			tmp = tmp->next;
	}
}

void	create_data(t_data **data, t_tokens *tokens, t_env *env)
{
	creat_nodes(data, tokens, env);
	open_hdoc(data, tokens, env);
	open_files(data, tokens);
}

void	free_data(t_data **data)
{
	t_data	*tmp;
	int		i;

	tmp = *data;
	while (tmp)
	{
		i = -1;
		while (tmp->args[++i])
			free(tmp->args[i]);
		free(tmp->args);
		tmp = tmp->next;
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

