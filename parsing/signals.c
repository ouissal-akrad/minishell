/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 06:54:00 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/02 22:25:35 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigg(int sig)
{
	if (sig == SIGINT && waitpid(0, NULL, WNOHANG) == 0)
	{
		printf("\n");
		g_exit = 130;
		return;
	}
	if (sig == SIGQUIT && waitpid(0, NULL, WNOHANG) == 0)
	{
		printf("Quit: 3\n");
		g_exit = 131;
		return;
	}
	if (sig == SIGINT)
	{
		g_exit = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("" , 0);
		rl_redisplay();
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit = 1;
		backup_stdin = dup(0);
		close(0);
		exitt = 1;
	}
}


void	dont(int sig)
{
	(void)sig;
}

void	sig(void)
{
	signal(SIGINT, dont);
	signal(SIGINT, sigg);
	signal(SIGQUIT, sigg);
}
