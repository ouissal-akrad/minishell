/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:09 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/06 07:43:00 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_lstfree(t_env **head)
{
	t_env	*current;
	t_env	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		if (current->var)
			free(current->var);
		if (current->val)
			free(current->val);
		free(current);
		current = next;
	}
}

void	free_leaks(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	print_env(t_env *env, t_data *data)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (env->flag >= 1 && (ft_strncmp("PATH", tmp->var) == 0
				|| ft_strncmp("SHELL", tmp->var) == 0))
		{
			tmp = tmp->next;
			continue ;
		}
		if (tmp->var != NULL && tmp->val != NULL)
		{
			write(data->out, tmp->var, ft_strlen(tmp->var));
			write(data->out, "=", 1);
			write(data->out, tmp->val, ft_strlen(tmp->val));
			write(data->out, "\n", 1);
		}
		tmp = tmp->next;
	}
}

void	shlvl(t_env **env)
{
	int		new_val;
	t_env	*tmp;
	char	*f;

	tmp = *env;
	f = find(*env, "SHLVL");
	if (f == NULL)
		return (ft_lstadd_backk(env, ft_lstneww("SHLVL", "1")));
	free(f);
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "SHLVL") == 0)
		{
			new_val = ft_atoi(tmp->val) + 1;
			if (tmp->val)
				free(tmp->val);
			if (new_val == 1000)
				tmp->val = ft_strdup("");
			else if (ft_strncmp(tmp->var, "") == 0)
				tmp->val = ft_itoa(1);
			else
				tmp->val = ft_itoa(new_val);
		}
		tmp = tmp->next;
	}
}

int	array_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	my_env(t_env **env, t_data *data)
{
	if (data->args[1])
	{
		write(2, "env: too many arguments\n", 24);
		g_exit = 1;
	}
	else
	{
		print_env(*env, data);
		g_exit = 0;
	}
}
