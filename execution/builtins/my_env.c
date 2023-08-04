/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:09 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/03 23:28:08 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_env(t_env *env, char *oldpwd, char *pwd)
{
	while (env)
	{
		if (ft_strncmp(env->var, "OLDPWD") == 0)
		{
			free(env->val);
			env->val = ft_strdup(oldpwd);
		}
		else if (ft_strncmp(env->var, "PWD") == 0)
		{
			free(env->val);
			env->val = ft_strdup(pwd);
		}
		env = env->next;
	}
}

char	*find(t_env *env, char *to_find)
{
	while (env)
	{
		if (ft_strncmp(env->var, to_find) == 0)
			return (env->val);
		env = env->next;
	}
	return (NULL);
}

/////////////////////////////////////////

void	ft_lstfree(t_env **head)
{
	t_env	*current;
	t_env	*next;

	current = *head;
	while (current != NULL)
	{
		next = current->next;
		free(current->var);
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

void delete_node(t_env *curr)
{
    if (curr->prev != NULL)
        curr->prev->next = curr->next;
    if (curr->next != NULL)
        curr->next->prev = curr->prev;
    free(curr->var);
    free(curr->val);
    free(curr);
}

t_env	*ft_lstneww(char *env_name, char *env_content)
// remove
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = ft_strdup(env_name);
	new->val = NULL;
	if (env_content != NULL)
		new->val = ft_strdup(env_content);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_backk(t_env **lst, t_env *new)
// remove
{
	t_env *tmp;

	tmp = *lst;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	new->prev = tmp;
	tmp->next = new;
}

void	print_env(t_env *env ,t_data *data)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if(env->flag >= 1 && (ft_strncmp("PATH",tmp->var) == 0 || ft_strncmp("SHELL",tmp->var) == 0))
		{
			tmp = tmp->next;
			continue;
		}
		if (tmp->var != NULL && tmp->val != NULL)
		{
			write(data->out,tmp->var, ft_strlen(tmp->var));
			write(data->out,"=", 1);
			write(data->out,tmp->val, ft_strlen(tmp->val));
		}
		tmp = tmp->next;
	}
}

void shlvl(t_env *env)
{
	int new_val;
	t_env *tmp = env;
	while(tmp)
	{
		if (ft_strncmp(tmp->var, "SHLVL") == 0)
		{
			new_val = ft_atoi(tmp->val) + 1;
			free(tmp->val);
			if(new_val == 1000)
				tmp->val = ft_strdup("");
			else if(ft_strncmp(tmp->var, "") == 0)
				tmp->val = ft_itoa(1);
			else
				tmp->val = ft_itoa(new_val);
		}
		tmp = tmp->next;
	}
}

t_env	*create_list(char *str[])
{
	t_env	*env;
	int		i;
	char	*variable;
	char	*equal_sign;

	env = NULL;
	i = 0;
	while (str[i])
	{
		variable = str[i];
		equal_sign = ft_strchr(variable, '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			ft_lstadd_backk(&env, ft_lstneww(variable, equal_sign + 1));
		}
		i++;
	}
	shlvl(env);
	return (env);
}
void	my_env(t_env **env,t_data *data)
{
	print_env(*env,data);
	g_global.g_exit = 0;
}
