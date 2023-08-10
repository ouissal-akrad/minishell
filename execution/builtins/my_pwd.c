/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:53:30 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/10 15:17:31 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_pwd(t_data *data, t_env *env)
{
	char	cwd[1024];
	char 	*pwd;

	if(getcwd(cwd, sizeof(cwd)))
	{
		pwd = find(env, "PWD");
		g_global.g_exit = 0;
		write(data->out, pwd, ft_strlen(cwd));
		write(data->out, "\n", 1);
		free(pwd);
		return;
		
	}
	g_global.g_exit = 0;
	write(data->out, cwd, ft_strlen(cwd));
	write(data->out, "\n", 1);
}
