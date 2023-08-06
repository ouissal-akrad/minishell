/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:09 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/06 02:59:54 by bel-idri         ###   ########.fr       */
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
	new->flag = g_env;
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
			write(data->out,"\n", 1);
		}
		tmp = tmp->next;
	}
}

void shlvl(t_env **env)
{
	int new_val;
	t_env *tmp = *env;
	char *f;

	f = find(*env, "SHLVL");
	if (f == NULL)
	{
		ft_lstadd_backk(env, ft_lstneww("SHLVL", "1"));
		return ;
	}
	free(f);

	while(tmp)
	{
		if (ft_strncmp(tmp->var, "SHLVL") == 0)
		{
			new_val = ft_atoi(tmp->val) + 1;
			if (tmp->val)
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

int array_size(char **str)
{
	int i = 0;
	while(str[i])
		i++;
	return i;
}
t_env	*create_list(char *str[])
{
	t_env	*env;
	int		i;
	char	*variable;
	char	*equal_sign;
	int size = array_size(str);
	char	wdir[PATH_MAX];

	getcwd(wdir, PATH_MAX);
	env = NULL;
	g_env = 0;
	i = 0;
	while (str[i])
	{
		variable = str[i];
		equal_sign = ft_strchr(variable, '=');
		if (equal_sign != NULL && ft_strncmp_2(variable, "OLDPWD=", 7) != 0 \
			&& ft_strncmp_2(variable, "PWD=", 4) != 0)
		{
			*equal_sign = '\0';
			ft_lstadd_backk(&env, ft_lstneww(variable, equal_sign + 1));
		}
		if(i == size / 2)
		{
			ft_lstadd_backk(&env, ft_lstneww("OLDPWD", NULL));
			ft_lstadd_backk(&env, ft_lstneww("PWD", wdir));
		}
		i++;
	}
	shlvl(&env);
	return (env);
}
void	my_env(t_env **env,t_data *data)
{
	if(data->args[1])
	{
		write(2,"env: too many arguments\n",24);
		g_exit = 1;
	}
	else
	{
		print_env(*env,data);
		g_exit = 0;
	}
}
