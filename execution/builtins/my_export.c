/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:00 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/06 08:30:56 by bel-idri         ###   ########.fr       */
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

void	print_env_ex_helper(t_data *data, t_env *tmp)
{
	int	i;

	i = -1;
	write(data->out, "declare -x ", 11);
	while (tmp->var[++i])
		write(data->out, &tmp->var[i], 1);
	write(data->out, "=\"", 2);
	i = -1;
	while (tmp->val[++i])
	{
		if (tmp->val[i] == '\"')
			write(data->out, "\\", 2);
		write(data->out, &tmp->val[i], 1);
	}
	write(data->out, "\"\n", 2);
}

void	print_env_ex(t_env *env, t_data *data)
{
	t_env	*tmp;

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
			print_env_ex_helper(data, tmp);
		else if (tmp->var != NULL)
		{
			write(data->out, "declare -x ", 11);
			write(data->out, tmp->var, ft_strlen(tmp->var));
			write(data->out, "\n", 1);
		}
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

t_env	*copy_env_list(const t_env *original_head)
{
	t_env	*copy_head;
	t_env	*original_curr;
	t_env	*copy_prev;
	t_env	*copy_curr;

	if (original_head == NULL)
		return (NULL);
	copy_head = create_new_env(original_head);
	if (copy_head == NULL)
		return (NULL);
	original_curr = original_head->next;
	copy_prev = copy_head;
	while (original_curr != NULL)
	{
		copy_curr = create_new_env(original_curr);
		if (copy_curr == NULL)
			return (NULL);
		copy_curr->prev = copy_prev;
		copy_prev->next = copy_curr;
		original_curr = original_curr->next;
		copy_prev = copy_curr;
	}
	return (copy_head);
}

void	my_export(t_env **env, t_data *data)
{
	t_env	*cpy;

	if (!data->args[1])
	{
		cpy = copy_env_list(*env);
		sort_env(&cpy);
		print_env_ex(cpy, data);
		ft_lstfree(&cpy);
	}
	else
		ft_csp(*env, data, '=');
}

void	print_error_csp(char *data_cmd)
{
	write(2, "minishell: export: `", 20);
	write(2, data_cmd, ft_strlen(data_cmd));
	write(2, "': not a valid identifier\n", 26);
	g_exit = 1;
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
			print_error_csp(data->args[cmd++]);
			continue ;
		}
		while (tmp[i] && tmp[i] != c)
			i++;
		if (tmp[i] == c)
		{
			if (ft_strchr(tmp, '+') != NULL)
			{
				if (count_plus(tmp) == 1)
					plus = 1;
				else if (count_plus(tmp) == -1)
				{
					print_error_csp(data->args[cmd++]);
					continue ;
				}
				prev = tmp;
				prev[i - plus] = '\0';
				rest = tmp + i + 1;
			}
			else
			{
				prev = tmp;
				prev[i] = '\0';
				rest = tmp + i + 1;
			}
		}
		if (check_value(tmp))
			prev = ft_strdup(tmp);
		else
		{
			print_error_csp(data->args[cmd++]);
			continue ;
		}
		if (!check(prev))
		{
			print_error_csp(data->args[cmd++]);
			free(prev);
			continue ;
		}
		sequal(env, prev, rest, plus);
		cmd++;
		free(prev);
	}
	if (g_exit == 1)
		g_exit = 1;
	else if (g_exit == 0)
		g_exit = 0;
}

void	sequal_helper(t_env *existing_var, char *rest)
{
	free(existing_var->val);
	if (!rest)
		existing_var->val = NULL;
	else
		existing_var->val = ft_strdup(rest);
}

void	sequal(t_env *env, char *prev, char *rest, int plus)
{
	t_env	*new_var;
	t_env	*existing_var;
	char	*old_val;

	existing_var = find_env(env, prev);
	if (existing_var != NULL)
	{
		if (plus && existing_var->val)
		{
			old_val = ft_strdup(existing_var->val);
			free(existing_var->val);
			existing_var->val = ft_strjoin(old_val, rest);
			free(old_val);
		}
		else
			sequal_helper(existing_var, rest);
	}
	else
	{
		new_var = ft_lstneww(prev, rest);
		if (new_var == NULL)
			return ;
		ft_lstadd_backk(&env, new_var);
	}
}
