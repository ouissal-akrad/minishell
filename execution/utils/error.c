/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 23:37:49 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/07 02:01:30 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	err_cmd(t_data *data)
{
	write(2, "minishell: ", 11);
	write(2, data->args[0], ft_strlen(data->args[0]));
	write(2, ": command not found\n", 20);
	g_global.g_exit = 127;
	exit(g_global.g_exit);
}

void	err_isdir(t_data *data)
{
	write(2, "minishell: ", 11);
	write(2, data->args[0], ft_strlen(data->args[0]));
	write(2, ": is a directory\n", 17);
	g_global.g_exit = 126;
	exit(g_global.g_exit);
}

void	err_permission(t_data *data)
{
	write(2, "minishell: ", 11);
	write(2, data->args[0], ft_strlen(data->args[0]));
	write(2, ": Permission denied\n", 20);
	g_global.g_exit = 126;
	exit(g_global.g_exit);
}

void	err_nodir(t_data *data)
{
	write(2, "minishell: ", 11);
	write(2, data->args[0], ft_strlen(data->args[0]));
	write(2, ": No such file or directory\n", 28);
	g_global.g_exit = 127;
	exit(g_global.g_exit);
}
