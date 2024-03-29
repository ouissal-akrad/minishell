/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 06:54:00 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/10 10:22:27 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigg(int sig)
{
	if (sig == SIGINT && waitpid(0, NULL, WNOHANG) == 0)
		printf("\n");
	else if (sig == SIGQUIT && waitpid(0, NULL, WNOHANG) == 0)
		printf("\n");
	else if (sig == SIGINT && g_global.exitt)
	{
		g_global.backup_stdin = dup(0);
		close(0);
	}
	else if (sig == SIGINT)
	{
		g_global.g_exit = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig(void)
{
	signal(SIGINT, sigg);
	signal(SIGQUIT, sigg);
}
