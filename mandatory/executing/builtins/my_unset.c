/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:33 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/14 10:12:01 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"


void	my_unset(t_env **env, char **args)
{
	t_env	*prev;
	t_env	*cur;
	int		i;

	prev = NULL;
	cur = *env;
	i = 1;
	while (args[i] != NULL)
	{
		cur = *env;
		prev = NULL;
		while (cur != NULL)
		{
			if (ft_strcmp(cur->var, args[i]) == 0)
			{
				if (prev == NULL)
					*env = cur->next;
				else
					prev->next = cur->next;
				delete_node(*env, cur->var);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	// print_env(*env);
}