/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:53:30 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/03 23:18:43 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	my_pwd(t_data *data)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	g_global.g_exit = 0;
	write(data->out,cwd, ft_strlen(cwd));
	write(data->out,"\n", 1);
}
