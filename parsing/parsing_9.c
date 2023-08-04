/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_9.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/03 23:12:24 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstnewnode(t_data *new, t_tokens **tokens)
{
	int	j;

	j = 0;
	while ((*tokens))
	{
		if ((*tokens)->type == WORD)
			new->args[j++] = ft_strdup((*tokens)->str);
		else if ((*tokens)->type == IN || (*tokens)->type == OUT
			|| (*tokens)->type == APP || (*tokens)->type == HDOC)
			(*tokens) = (*tokens)->next;
		else if ((*tokens)->type == PIPE)
			break ;
		(*tokens) = (*tokens)->next;
	}
	new->in = 0;
	new->out = 1;
	new->hdoc = 0;
	new->buff = ft_strdup("");
	new->is_dir = 0;
	new->next = NULL;
}

void	creat_nodes(t_data **data, t_tokens **tokens)
{
	t_tokens	*tmp;
	t_data		*new;

	tmp = *tokens;
	while (tmp)
	{
		new = ft_calloc(1, sizeof(t_data));
		if (!new)
			exit_calloc(data, tokens);
		new->args = ft_calloc(count_n_tokens(tmp) + 1, sizeof(char *));
		if (!new->args)
			exit_calloc(data, tokens);
		ft_lstnewnode(new, &tmp);
		ft_lstadddd_back(data, new);
		if (tmp)
			tmp = tmp->next;
	}
}

void	go_to_pipe(t_tokens **tokens)
{
	while (*tokens)
	{
		if ((*tokens)->type == PIPE)
			break ;
		*tokens = (*tokens)->next;
	}
}

int	open_files_error(t_tokens *tmp)
{
	write(2, "minishell: ", 11);
	write(2, tmp->next->str, ft_strlen(tmp->next->str));
	write(2, ": ", 2);
	perror("");
	return (1);
}

void	free_2_str(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}
