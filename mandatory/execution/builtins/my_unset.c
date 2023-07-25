/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:33 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/25 14:56:47 by ouakrad          ###   ########.fr       */
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
			if (ft_strcmp(cur->var, data->args[i]) == 0 && ft_strcmp(cur->var, "_") != 0)
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
