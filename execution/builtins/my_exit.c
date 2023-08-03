/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:20:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/03 18:29:39 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_digit(char *str)
{
	int	i;
	int len = ft_strlen(str);
	if(len == 1 && (str[0] == '-' || str[0] == '+'))
		return 0;
	i = 1;
	while (str[i])
	{
		if ((str[0] == '-' || str[0] == '+' || ft_isdigit(str[0])) && (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}

char *skip_zero(char *str)
{
	while(*str)
	{
		if(*str != '0')
			return((char *)str);
		str++;
	}
	return(NULL);
}

static int	ft_check(char *str)
{
	if ((ft_strlen(str) >= 19)
			&& (ft_strncmp_2(str, "9223372036854775807", 19) > 0))
			return (-1);
	if (ft_strlen(str) >= 20
			&& ft_strncmp_2(str, "-9223372036854775808", 20) > 0)
			return (0);
	return (1);
}

void	my_exit(t_env **env,t_data *data)
{
	int	i;

	i = 1;
	if (!data->args[i])
	{
		if(data_s == 1)
			printf("exit\n");
		g_exit = 0;
		ft_lstfree(env);
		exit(0);
	}
	else
		data->args[i] = skip_zero(data->args[i]);
	if ((ft_check(data->args[i]) == 0 || ft_check(data->args[i]) == -1) || all_digit(data->args[i]) == 0)
	{
		if (data_s == 1)
			printf("exit\n");
		write(2, "minishell: exit: ", 17);
		write(2, data->args[i], ft_strlen(data->args[i]));
		write(2, ": numeric argument required\n", 28);
		g_exit = 255;
		// ft_lstfree(env);
		exit(255);
	}
	else if (data->args[2])
    {
        g_exit = 1;
		if (data_s == 1)
			printf("exit\n");
		write(2, "minishell: exit: too many arguments\n", 36);
		return;
    }
	g_exit = ft_atoi(data->args[i]);
	ft_lstfree(env);
	if(data_s == 1)
		printf("exit\n");
	exit(ft_atoi(data->args[i]) % 256);
}
