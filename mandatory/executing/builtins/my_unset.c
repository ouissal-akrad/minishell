/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:33 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/18 16:05:16 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

void	my_unset(t_env **env, char **args)
{
	t_env	*cur;
	int		i;

	cur = *env;
	i = 1;
	while (args[i] != NULL)
	{
		cur = *env;
		while (cur != NULL)
		{
			if (ft_strcmp(cur->var, args[i]) == 0)
			{
				if (cur->prev == NULL)
					*env = cur->next;
				// if(cur != NULL)
				delete_node(*env, cur->var);
				break ;
			}
			cur = cur->next;
		}
		i++;
	}
	// print_env(*env);
}