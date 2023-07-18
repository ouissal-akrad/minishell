/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:00 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/18 18:40:50 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

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
		if (ft_strcmp(env->var, name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	print_env_ex(t_env *env)
{
	t_env	*tmp;
	int i;

	tmp = env;
	while (tmp != NULL)
	{	
		if (tmp->var != NULL && tmp->val != NULL)
		{
			i = -1;
			printf("declare -x ");
			while (tmp->var[++i])
				printf("%c", tmp->var[i]);
			printf ("=\"");
			i = -1;
			while (tmp->val[++i])
			{
				if (tmp->val[i] == '\"')
					printf("\\");
				printf("%c", tmp->val[i]);
			}
			printf("\"\n");
		}
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
			if (ft_strcmp(tmp->var, tmp->next->var) > 0)
			{
				swap_env(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
		tmp = *env;
	}
}

void	my_export(t_env **env, char **cmd)
{
	if (!cmd[1])
	{
		sort_env(env);
		print_env_ex(*env);
	}
	else
		ft_csp(*env, cmd, '=');
}

int	check(char *str)
{
	int	i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return 0;
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

t_env	*ft_csp(t_env *env, char **s, int c)
{
	int		plus;
	size_t	i;
	size_t	cmd;
	char	*oldVal;
	char	*prev;
	char	*rest;
	char	*tmp;
	t_env	*new_var;
	t_env	*existing_var;

	plus = 0;
	cmd = 1;
	while (s[cmd])
	{
		i = 0;
		prev = NULL;
		rest = NULL;
		tmp = s[cmd];
		if (!tmp)
			return (env);
		//one arg
		if (tmp[0] == '=')
		{
			printf("minishell: export: `%s`: not a valid identifier++++\n", s[cmd]);
			return (env);
		}
		//no =
		if (tmp[0] != '=')
		{
			if (ft_strchr(tmp, '=') == NULL)
			{
				if (check(tmp))
				{
					// if(all_str(tmp))
					// Create a new environment variable
					new_var = ft_lstneww(s[cmd], NULL);
					if (new_var == NULL)
						return (env);
					// Add the new variable to the list
					ft_lstadd_backk(&env, new_var);
				}
				else
				{
					printf("minishell: export: `%s`: not a valid identifier----\n",s[cmd]);
					return (env);
				}
			}
			// export with args
			else
			{
				while (tmp[i])
				{
					if (tmp[i] == c)
					{
						if (tmp[i - 1] && tmp[i - 1] == '+')
							plus = 1;
						prev = tmp;
						prev[i - plus] = '\0';
						rest = tmp + i + 1;
						break ;
					}
					i++;
				}
				// printf("prev========>%s\n",prev);
				if (prev)
				{
					// Check if the variable name is valid
					if (!check(prev))
					{
						printf("minishell: export: %s: not a valid identifier******\n", s[cmd]);
						return (env);
					}
					// Check if the variable already exists
					existing_var = find_env(env, prev);
					if (existing_var != NULL)
					{
						// Duplicate the new value and store it in the existing variable and + exists
						if (plus && existing_var->val)
						{
							oldVal = ft_strdup(existing_var->val);
							free(existing_var->val);
							existing_var->val = ft_strjoin(oldVal, rest);
							free(oldVal);
						}
						// assign new value to the old variable if it exists
						else
						{
							free(existing_var->val);
							existing_var->val = ft_strdup(rest);
						}
					}
					else
					{
						// Create a new env variable
						new_var = ft_lstneww(prev, rest);
						if (new_var == NULL)
							return (env);
						// Add the new variable to the list
						ft_lstadd_backk(&env, new_var);
					}
				}
			}
		}
		cmd++;
	}
	//resort env
	sort_env(&env);
	// puts("-------------------");
	// print_env_ex(env);
	// puts("-------------------");
	return (env);
}

// fach nji khassni nsawb export p=bilal export p / p t8anya ma khasch tkun 