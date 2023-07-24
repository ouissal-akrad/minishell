/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 15:13:05 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/24 16:38:39 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"

/*
ls > a.out | echo -n ls << u
str: ls
type: 0

str: >
type: 3

str: a.out
type: 0

str: |
type: 1

str: echo
type: 0

str: -n
type: 0

str: ls
type: 0

str: <<
type: 5

str: u
type: 0

minishell$ > hshs
*/

int	redirection(t_tokens *red)
{
	int	fd;

	fd = 0;
	if (red->type == OUT || red->type == APP)
	{
		if (red->type == OUT)
			fd = open(red->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fd = open(red->next->str, O_WRONLY | O_CREAT | O_APPEND , 0644);
		if (fd < 0)
			exit(1);
	}
	if (red->type == IN)
	{
		fd = open(red->next->str, O_RDONLY);
		if (fd < 0)
			exit(1);
	}
	return (fd);
}
