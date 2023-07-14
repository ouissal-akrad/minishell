/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:09 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/14 10:11:51 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

void	delete_node(t_env *head, char *var)
{
	t_env	*curr;
	t_env	*prev;

	curr = head;
	prev = NULL;
	while (curr != NULL && ft_strcmp(curr->var, var) != 0)
	{
		prev = curr;
		curr = curr->next;
	}
	if (curr != NULL)
	{
		if (prev == NULL)
			head = curr->next;
		else
			prev->next = curr->next;
		free(curr->var);
		free(curr->val);
		free(curr);
	}
}

t_env	*ft_lstneww(char *env_name, char *env_content)
// remove 
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = env_name;
	new->val = env_content;
	new->next = NULL;
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
	tmp->next = new;
}

void	print_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->var != NULL && tmp->val != NULL)
			printf("%s=%s\n", tmp->var, tmp->val);
		tmp = tmp->next;
	}
}

t_env	*create_list(char *str[]) // remove after work in general main
{
	t_env *env;
	char **str1;
	int i;

	i = 0;
	env = NULL;
	while (str[i])
	{
		str1 = ft_split(str[i], '=');
		ft_lstadd_backk(&env, ft_lstneww(str1[0], str1[1]));
		i++;
	}
	// print_env(env);
	return (env);
}

void	my_env(t_env *env)
{
	print_env(env);
}
