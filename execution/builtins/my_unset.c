/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:33 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/04 00:52:06 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			if((*env)->flag >= 1 && ft_strncmp(cur->var, "_") == 0)
				cur = cur->next;
			else if (ft_strncmp(cur->var, data->args[i]) == 0 )
			{
				if (cur->prev == NULL)
					*env = cur->next;
				delete_node(cur); // need to go back to this
				break ;
			}
			cur = cur->next;
		}
		i++;
	}
	g_global.g_exit = 0;
}
