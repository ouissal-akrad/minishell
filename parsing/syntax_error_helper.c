/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/10 10:24:38 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rl_hdoc(void)
{
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	check_tty(void)
{
	if (ttyname(0) == NULL)
	{
		dup2(g_global.backup_stdin, 0);
		close(g_global.backup_stdin);
		write(1, "\n", 1);
	}
	else
		g_global.exitt = 0;
}

void	syntax_error_hdoc_helper(char *str)
{
	char	*line;

	line = NULL;
	while (1)
	{
		g_global.exitt = 1;
		line = readline("> ");
		if (!line)
		{
			rl_hdoc();
			break ;
		}
		if (!ft_strncmp(line, str))
		{
			free(line);
			break ;
		}
		free(line);
	}
	check_tty();
}

int	syntax_error_hdoc(char *str, t_tokens *tokens, int i)
{
	t_tokens	*tmp;

	tmp = tokens;
	while (i--)
	{
		if ((tmp->type == HDOC && tmp->next && tmp->next->type == WORD)
			&& !g_global.exitt)
			syntax_error_hdoc_helper(tmp->next->str);
		tmp = tmp->next;
	}
	if (g_global.exitt)
		return (1);
	else
		return (syntax_error_msg(str));
}

int	syntax_error_halper(t_tokens *tmp, t_tokens *tokens, int i)
{
	if (!tmp->next)
		return (syntax_error_hdoc("newline", tokens, i));
	else if (tmp->next->type == PIPE)
		return (syntax_error_hdoc("|", tokens, i));
	else if (tmp->next->type == IN)
		return (syntax_error_hdoc("<", tokens, i));
	else if (tmp->next->type == OUT)
		return (syntax_error_hdoc(">", tokens, i));
	else if (tmp->next->type == APP)
		return (syntax_error_hdoc(">>", tokens, i));
	else if (tmp->next->type == HDOC)
		return (syntax_error_hdoc("<<", tokens, i));
	return (0);
}
