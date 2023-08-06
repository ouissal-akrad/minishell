/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 11:20:28 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/06 10:38:08 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	all_digit(char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	if (len == 0)
		return (0);
	if (len == 1 && (str[0] == '-' || str[0] == '+'))
		return (0);
	i = 1;
	while (str[i])
	{
		if ((str[0] == '-' || str[0] == '+' || ft_isdigit(str[0]))
			&& (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (0);
	}
	return (1);
}

char	*skip_zero(char *str)
{
	char	*result;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (str[i] == '0')
		i++;
	if (i == ft_strlen(str))
	{
		result[0] = '0';
		free(str);
		return (result);
	}
	while (str[i])
	{
		result[j] = str[i];
		i++;
		j++;
	}
	free(str);
	return (result);
}

static int	ft_check(char *str)
{
	if ((ft_strlen(str) >= 19) && (ft_strncmp_2(str, "9223372036854775807",
				19) > 0))
		return (-1);
	if (ft_strlen(str) >= 20 && ft_strncmp_2(str, "-9223372036854775808",
			20) > 0)
		return (0);
	return (1);
}

int	my_exit_helper(char *data_arg, t_data *data, t_env **env)
{
	if (((ft_check(data_arg) == 0 || ft_check(data_arg) == -1)
			|| all_digit(data_arg) == 0))
	{
		if (g_global.data_s == 1)
			printf("exit\n");
		write(2, "minishell: exit: ", 17);
		write(2, data_arg, ft_strlen(data_arg));
		write(2, ": numeric argument required\n", 28);
		g_global.g_exit = 255;
		ft_lstfree(env);
		free_data(&data);
		exit(255);
	}
	else if (data->args[2])
	{
		g_global.g_exit = 1;
		if (g_global.data_s == 1)
			printf("exit\n");
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	return (0);
}

void	my_exit(t_env **env, t_data *data)
{
	int	i;
	int	e;

	i = 1;
	if (!data->args[i])
	{
		if (g_global.data_s == 1)
			printf("exit\n");
		g_global.g_exit = 0;
		ft_lstfree(env);
		free_data(&data);
		exit(0);
	}
	else
		data->args[i] = skip_zero(data->args[i]);
	if (my_exit_helper(data->args[i], data, env))
		return ;
	g_global.g_exit = ft_atoi(data->args[i]);
	if (g_global.data_s == 1)
		printf("exit\n");
	e = ft_atoi(data->args[i]);
	ft_lstfree(env);
	free_data(&data);
	exit(e % 256);
}
