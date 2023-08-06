/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:18 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/06 06:50:54 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	newline_checker(char *str)
{
	int	i;

	if (!str || str[0] == '\0')
		return (0);
	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0' && str[i - 1] == 'n')
		return (1);
	return (0);
}

void	my_echo(t_data *data)
{
	int	i;
	int	new_line;
	int	flag;

	i = 1;
	flag = 0;
	new_line = 1;
	while (data->args[i])
	{
		while (data->args[i] && newline_checker(data->args[i]) == 1
			&& flag == 0)
		{
			i++;
			new_line = 0;
		}
		flag = 1;
		if (data->args[i])
			write(data->out, data->args[i], ft_strlen(data->args[i]));
		if (data->args[++i])
			write(data->out, " ", 1);
	}
	if (new_line)
		write(data->out, "\n", 1);
	g_exit = 0;
}
