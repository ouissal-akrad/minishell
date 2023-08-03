/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:00 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/03 02:40:58 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	all_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
				&& str[i] <= 'Z'))
			i++;
		else
			return (0);
	}
	return (1);
}

t_env	*find_env(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strncmp(env->var, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	print_env_ex(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	while (tmp != NULL)
	{
		if (env->flag >= 1 && (ft_strncmp("PATH", tmp->var) == 0
				|| ft_strncmp("SHELL", tmp->var) == 0 || ft_strncmp("_",
					tmp->var) == 0))
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->var != NULL && tmp->val != NULL)
		{
			i = -1;
			printf("declare -x ");
			while (tmp->var[++i])
				printf("%c", tmp->var[i]);
			printf("=\"");
			i = -1;
			while (tmp->val[++i])
			{
				if (tmp->val[i] == '\"')
					printf("\\");
				printf("%c", tmp->val[i]);
			}
			printf("\"\n");
		}
		else if (tmp->var != NULL)
			printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}

int	check_value(char *str)
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
	}
	return (1);
}

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

void	my_export(t_env **env, t_data *data)
{
	if (!data->args[1])
	{
		sort_env(env);
		print_env_ex(*env);
	}
	else
		ft_csp(*env, data, '=');
}

void	ft_csp(t_env *env, t_data *data, int c)
{
	int		plus;
	size_t	i;
	size_t	cmd;
	char	*tmp;
	char	*prev;
	char	*rest;

	cmd = 1;
	while (data->args[cmd])
	{
		plus = 0;
		i = 0;
		prev = NULL;
		rest = NULL;
		tmp = data->args[cmd];
		if (tmp[0] != '_' && !ft_isalpha(tmp[0]))
		{
			fprintf(stderr, "minishell: export: `%s': not a valid identifier\n",
					data->args[cmd]);
			cmd++;
			g_exit = 1;
			continue ;
		}
		while (tmp[i] && tmp[i] != c)
			i++;
		//with equal
		if (tmp[i] == c)
		{
			//with plus
			if (ft_strchr(tmp, '+') != NULL)
			{
				if (count_plus(tmp) == 1)
					plus = 1;
				else if (count_plus(tmp) == -1)
				{
					fprintf(stderr, "minishell: export: `%s': not a valid identifier\n",
							data->args[cmd]);
										g_exit = 1;

					cmd++;
					continue ;
				}
				prev = tmp;
				prev[i - plus] = '\0';
				rest = tmp + i + 1;
			}
			//without plus
			else
			{
				prev = tmp;
				prev[i] = '\0';
				rest = tmp + i + 1;
			}
		}
		//without = ,rest == NULL
		if (check_value(tmp))
			prev = ft_strdup(tmp);
		else
		{
			fprintf(stderr, "minishell: export: `%s': not a valid identifier\n",
					data->args[cmd]);
			cmd++;
			g_exit = 1;
			continue ;
		}
		if (!check(prev))
		{
			fprintf(stderr, "minishell: export: `%s': not a valid identifier\n",
					data->args[cmd]);
			cmd++;
						g_exit = 1;

			continue ;
		}
		// check
		sequal(env, prev, rest, plus);
		cmd++;
	}
	//resort env
	sort_env(&env);
	if (g_exit == 1)
		g_exit = 1;
	else if (g_exit == 0)
		g_exit = 0;
	// print_env_ex(env);
	// puts("-----------------------------");
	// print_env(env);
}

void	sequal(t_env *env, char *prev, char *rest, int plus)
{
	t_env	*new_var;
	t_env	*existing_var;
	char	*old_val;

	existing_var = find_env(env, prev);
	if (existing_var != NULL)
	{
		// Duplicate the new value and store it in the existing variable and + exists
		if (plus && existing_var->val)
		{
			old_val = ft_strdup(existing_var->val);
			free(existing_var->val);
			existing_var->val = ft_strjoin(old_val, rest);
			free(old_val);
		}
		// assign new value to the old variable if it exists
		else
		{
			free(existing_var->val);
			if (!rest)
				existing_var->val = NULL;
			else
				existing_var->val = ft_strdup(rest);
		}
	}
	else
	{
		// Create a new env variable
		new_var = ft_lstneww(prev, rest);
		if (new_var == NULL)
			return ;
		ft_lstadd_backk(&env, new_var);
	}
}
