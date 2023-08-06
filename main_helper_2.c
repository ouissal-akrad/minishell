/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:14:36 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 11:14:50 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	configs(t_main *main)
{
	open_files_hdoc_tmp(&main->data);
	is_a_directory(&main->data);
}

void	fin_line(t_main *main)
{
	close_files(main->data);
	free_data(&main->data);
	main->data = NULL;
}

void	fin_program(t_main *main)
{
	clear_history();
	free_env(&main->new_env);
}
