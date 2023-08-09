/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 06:54:00 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/09 13:16:41 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigg(int sig)
{
	if (sig == SIGINT && waitpid(0, NULL, WNOHANG) == 0)
	{
		printf("\n");
		return ;
	}
	else if (sig == SIGQUIT && waitpid(0, NULL, WNOHANG) == 0)
	{
		printf("\n");
		return ;
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

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_global.backup_stdin = dup(0);
		close(0);
		g_global.exitt = 1;
	}
}

void	sig(void)
{
	signal(SIGINT, sigg);
	signal(SIGQUIT, sigg);
}