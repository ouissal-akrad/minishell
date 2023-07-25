/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:20:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/22 14:23:51 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

int	all_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

void	my_exit(t_env **env,char **cmd)
{
	int	i;

	i = 1;
	if (!cmd[i])
	{
		printf("exit\n");
		g_exit = 0;
		ft_lstfree(env);
		exit(0);
	}
	else if (all_digit(cmd[i]) == 0 || ((all_digit(cmd[i]) == 1) && ft_atoi(cmd[i]) <= 0))
	{
		printf("minishell: exit: ");
		printf("%s: numeric argument required\n", cmd[i]);
		g_exit = 255;
		ft_lstfree(env);
		exit(255);
	}
	else if (cmd[2])
    {
        g_exit = 1;
		return(printf("minishell: exit: too many arguments\n"),free(NULL));
    }
	g_exit = ft_atoi(cmd[i]);
	ft_lstfree(env);
	exit(ft_atoi(cmd[i]) % 256);
}
