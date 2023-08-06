/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:20:11 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 11:14:52 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	t_main	main;

	start(&main, argc, argv, env);
	while (1)
	{
		g_global.exitt = 0;
		main.line = read_line();
		if (read_line_empty(main.line))
			continue ;
		if (parsing(&main))
			continue ;
		if (check_exit_hdoc(&main))
			continue ;
		configs(&main);
		g_global.data_s = data_size(main.data);
		direction(main.data, &main.new_env);
		fin_line(&main);
	}
	fin_program(&main);
	return (0);
}
