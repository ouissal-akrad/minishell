/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 01:11:29 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/07 02:00:36 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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
