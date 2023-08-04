/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:33 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/04 23:41:37 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_unset(t_env **env, t_data *data)
{
	t_env	*cur;
	int		i;

	i = 1;
	g_exit = 0;
	while (data->args[i] != NULL)
	{
		cur = *env;
		while (cur != NULL)
		{
			if((*env)->flag >= 1 && ft_strncmp(cur->var, "_") == 0)
				cur = cur->next;
			if (ft_strncmp(cur->var, data->args[i]) == 0)
			{
				if (cur->prev == NULL)
					*env = cur->next;
				delete_node(cur);
				break ;
			}
			else if (check_value(data->args[i]) == 0)
			{

				write(2, "minishell: export: `", 20);
					write(2, data->args[i], ft_strlen(data->args[i]));
					write(2, "': not a valid identifier\n", 26);
					g_exit = 1;
					break ;
			}
			cur = cur->next;
		}
		i++;
	}
}
