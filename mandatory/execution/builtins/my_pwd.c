/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 09:53:30 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/30 21:32:13 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_execution.h"

void	my_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("pwd: Error occurred.\n");
	else
	{
		g_exit = 0;
		printf("%s\n", cwd);
	}
}
