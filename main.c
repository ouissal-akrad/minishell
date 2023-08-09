/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:20:11 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/09 13:40:01 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main(int argc, char *argv[], char *env[])
{
	t_main	main;
	
	start(&main, argc, argv, env);
		// t_data *tmp;
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
		// int i;
		// tmp = main.data;
        // while (tmp)
        // {
        //     i = -1;
        //     while (tmp->args[++i])
        //         printf("args[%d]: %s\n", i, tmp->args[i]);
        //     printf("in: %d\n", tmp->in);
        //     printf("out: %d\n", tmp->out);
        //     printf("hdoc: %d\n", tmp->hdoc);
        //     printf("buff: %s\n", tmp->buff);
        //     tmp = tmp->next;
        // }
		direction(main.data, &main.new_env);
		fin_line(&main);
	}
	fin_program(&main);
	return (0);
}
