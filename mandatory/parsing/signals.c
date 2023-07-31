/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 06:54:00 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/31 18:43:43 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

// Ctrl + C in <<
// Ctrl + / in >>

// no need to rl_redisplay(); when Ctrl + C in cat



void	sigg(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	// if (sig == SIGQUIT && isatty(STDIN_FILENO))
	// {
	// 	printf("Quit: 3\n");
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// }
}

void	sig(void)
{
	signal(SIGINT, sigg);
	signal(SIGQUIT, sigg);
}
