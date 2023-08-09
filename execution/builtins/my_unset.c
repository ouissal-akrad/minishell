/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:54:33 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/09 17:12:44 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_msg_unset(char *data_arg)
{
	write(2, "minishell: export: `", 20);
	write(2, data_arg, ft_strlen(data_arg));
	write(2, "': not a valid identifier\n", 26);
	g_global.g_exit = 1;
}

void	my_unset(t_env **env, t_data *data, int i)
{
	t_env	*cur;

	g_global.g_exit = 0;
	while (data->args[++i] != NULL)
	{
		cur = *env;
		while (cur != NULL)
		{
			if (ft_strncmp(cur->var, data->args[i]) == 0)
			{
				if (cur->prev == NULL)
					*env = cur->next;
				delete_node(cur);
				break ;
			}
			else if (check_value(data->args[i]) == 0)
			{
				error_msg_unset(data->args[i]);
				break ;
			}
			cur = cur->next;
		}
	}
}
