/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:55:18 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/25 07:44:52 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

int	newline_checker(char *str)
{
	int	i;

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
		while (data->args[i] && newline_checker(data->args[i]) == 1 && flag == 0)
		{
			i++;
			new_line = 0;
		}
		flag = 1;
		if(data->args[i])
			printf("%s", data->args[i]);
		if (data->args[++i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
}