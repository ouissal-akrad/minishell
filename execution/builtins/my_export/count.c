/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:48:06 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/10 17:06:02 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if ((ft_isalnum(str[i]) || str[i] == '_'))
			i++;
		else
			return (0);
		if (str[i] == '=' || str[i] == '+')
			break ;
	}
	return (1);
}

int	count_plus(char *str)
{
	int	plus_count;
	int	i;

	plus_count = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_isalpha(str[i]))
		{
			if (str[i] == '+')
			{
				plus_count++;
				if (plus_count > 1 && str[i + 1] == '=')
					return (-1);
			}
			else if (str[i] == '=' && plus_count == 1)
				return (1);
		}
		i++;
	}
	return (0);
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

void	sort_env(t_env **env)
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
			if (ft_strncmp(tmp->var, tmp->next->var) > 0)
			{
				swap_env(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
		tmp = *env;
	}
}

t_env	*create_new_env(const t_env *original)
{
	t_env	*new_env;

	new_env = (t_env *)malloc(sizeof(t_env));
	if (new_env == NULL)
		return (NULL);
	new_env->var = ft_strdup(original->var);
	if (original->val == NULL)
		new_env->val = NULL;
	else
		new_env->val = ft_strdup(original->val);
	new_env->flag = original->flag;
	new_env->prev = NULL;
	new_env->next = NULL;
	return (new_env);
}
