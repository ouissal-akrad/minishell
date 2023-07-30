/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 06:54:00 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/30 10:29:41 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

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
}

void	sig(void)
{
	signal(SIGINT, sigg);
	signal(SIGQUIT, sigg);
}
