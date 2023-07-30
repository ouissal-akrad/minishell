/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 06:54:00 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/30 21:24:12 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

// cat ==> cntrl+\ g_exit = 131;
// cat ==> cntrl+c g_exit = 130;
void	new_line_no_display(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	new_line(void)
{
	new_line_no_display();
	rl_redisplay();
}

// \ cat
void	sigg(int sig)
{
	if (sig == SIGINT)
		new_line();
	if (sig == SIGQUIT && isatty(STDIN_FILENO))
	{
		printf("Quit: 3\n");
		rl_on_new_line();
		rl_redisplay();
	}
}

void	sig(void)
{
	signal(SIGINT, sigg);
	signal(SIGQUIT, sigg);
}
