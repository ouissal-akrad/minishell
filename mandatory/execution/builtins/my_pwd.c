/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:53:30 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/31 16:14:21 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	my_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		printf("[%s]\n", cwd);
		printf("pwd: Error occurred.\n");
	}
	else
	{
		g_exit = 0;
		printf("%s\n", cwd);
	}
}
