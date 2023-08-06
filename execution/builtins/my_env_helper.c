/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_env_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 07:40:51 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 10:39:27 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_lstneww(char *env_name, char *env_content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = ft_strdup(env_name);
	new->val = NULL;
	if (env_content != NULL)
		new->val = ft_strdup(env_content);
	new->flag = g_global.g_env;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_backk(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

void	create_list_helper(t_env **env)
{
	char	wdir[PATH_MAX];

	getcwd(wdir, PATH_MAX);
	ft_lstadd_backk(env, ft_lstneww("OLDPWD", NULL));
	ft_lstadd_backk(env, ft_lstneww("PWD", wdir));
}

t_env	*create_list(char *str[])
{
	t_env	*env;
	int		i;
	char	*variable;
	char	*equal_sign;
	int		size;

	size = array_size(str);
	env = NULL;
	g_global.g_env = 0;
	i = -1;
	while (str[++i])
	{
		variable = str[i];
		equal_sign = ft_strchr(variable, '=');
		if (equal_sign != NULL && ft_strncmp_2(variable, "OLDPWD=", 7) != 0
			&& ft_strncmp_2(variable, "PWD=", 4) != 0)
		{
			*equal_sign = '\0';
			ft_lstadd_backk(&env, ft_lstneww(variable, equal_sign + 1));
		}
		if (i == size / 2)
			create_list_helper(&env);
	}
	shlvl(&env);
	return (env);
}

void	delete_node(t_env *curr)
{
	if (curr->prev != NULL)
		curr->prev->next = curr->next;
	if (curr->next != NULL)
		curr->next->prev = curr->prev;
	free(curr->var);
	free(curr->val);
	free(curr);
}
