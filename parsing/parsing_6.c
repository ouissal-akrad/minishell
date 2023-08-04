/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_6.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/03 23:18:43 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	expand_env_halper_2(int *i, char *str, t_expvar *exp)
{
	char	*ex_s;

	if ((str[*i + 1] == '\"' && exp->quote != DQ) || \
		str[*i + 1] == '\'' || str[*i + 1] == '?')
	{
		if (str[*i + 1] == '?')
		{
			ex_s = ft_itoa(g_global.g_exit);
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
	if ((state && ((str[i] == '$' && exp.quote != SQ) && \
		((ft_isalpha(str[i + 1])) || str[i + 1] == '_' || \
		str[i + 1] == '?' || str[i + 1] == '\'' || \
		str[i + 1] == '\"'))) || ((!state && (str[i] == '$' \
		&& ((ft_isalpha(str[i + 1])) || str[i + 1] == '_' \
		|| str[i + 1] == '?' || str[i + 1] == '\'' \
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
