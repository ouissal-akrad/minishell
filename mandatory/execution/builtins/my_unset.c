/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:33 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/25 15:48:06 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	my_unset(t_env **env, t_data *data)
{
	t_env	*cur;
	int		i;

	i = 1;
	while (data->args[i] != NULL)
	{
		cur = *env;
		while (cur != NULL)
		{
			if((*env)->flag >= 1 && ft_strcmp(cur->var, "_") == 0)
				cur = cur->next;
			else if (ft_strcmp(cur->var, data->args[i]) == 0 )
			{
				if (cur->prev == NULL)
					*env = cur->next;
				delete_node(cur);
				break ;
			}
			cur = cur->next;
		}
		i++;
	}
}
