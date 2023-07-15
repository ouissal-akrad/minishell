/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:00 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/15 18:21:33 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

int	all_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
			i++;
		else
			return (0);
	}
	return (1);
}

void	print_env_ex(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->var != NULL && tmp->val != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->val);
		else
			printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}

void	swap_env(t_env *a, t_env *b)
{
	char	*var_temp;
	char	*val_temp;

	var_temp = a->var;
	val_temp = a->val;
	a->var = b->var;
	a->val = b->val;
	b->var = var_temp;
	b->val = val_temp;
}

void	my_export(t_env **env, char **cmd)
{
	t_env	*tmp;
	int		swapped;

	tmp = *env;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->var, tmp->next->var) > 0)
			{
				swap_env(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
		tmp = *env;
	}
	if (cmd[1])
		ft_csp(*env, cmd[1], '=');
	else
		print_env_ex(*env);
}

t_env	*ft_csp(t_env *env, char *s, int c)
{
	size_t	i;
	char	*prev;
	char	*rest;
	char	*tmp;
	// char	*to_find;
	i = 0;
	prev = NULL;
	rest = NULL;
	tmp = ft_strdup(s);
	if (!tmp)
		return (env);
	if (tmp[0] != '=')
	{
		//no args
		if (ft_strchr(tmp,'=') == NULL)
		{
			if(ft_isalpha(tmp[0]) || tmp[0] == '_')
				ft_lstadd_backk(&env, ft_lstneww(s, NULL));
			else 
			{
				printf("minishell: export: `%s`: not a valid identifier\n", s);
				free(tmp);
				return (env);
			}
		}
		//with args
		else
		{
			while (tmp[i])
			{
				if (tmp[i] == c)
				{
					prev = tmp;
					prev[i] = '\0';
					rest = tmp + i + 1;
					break ;
				}
				i++;
			}
			if (tmp[i] == c)
			{
				prev = tmp;
				prev[i] = '\0';
				rest = tmp + i + 1;
			}
			if (prev)
			{
				if (prev[0] == '_' || ft_isalpha(prev[0]))
				{
					i = 1;
					while (prev[i])
					{
						if (!ft_isalnum(prev[i]) && prev[i] != '_')
						{
							printf("minishell: export: %s: not a valid identifier\n", s);
							free(tmp);
							return (env);
						}
						i++;
					}
				}
				else
				{
					printf("minishell: export: %s: not a valid identifier\n", s);
					free(tmp);
					return (env);
				}
				ft_lstadd_backk(&env, ft_lstneww(prev, rest));
			}
		}
		free(tmp);
		printf("----\n");
		print_env_ex(env);
		printf("----\n");
		}
	return (env);
}

// chi variable deja kayna, ila drtiliha export kat ecrasa value dialha w kadar blastha
// multiple variables f commande whda
// export a="adnane" a+="harib" , concatenehum hh
// 