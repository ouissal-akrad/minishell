/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_13.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:44:04 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 10:23:51 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_tokens	*ft_lstnew_token_w(char *str, char *var)
{
	t_tokens	*new;

	new = ft_calloc(1, sizeof(t_tokens));
	if (new == NULL)
		return (NULL);
	new->str = ft_strdup(str);
	new->type = WORD;
	new->is_d = 5;
	new->var = ft_strdup(var);
	new->next = NULL;
	return (new);
}

void	ft_lstadd_in_second_place(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tmp;
	t_tokens	*tmp2;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	tmp2 = tmp->next;
	tmp->next = new;
	new->next = tmp2;
}

void	sort_p(char **tmp)
{
	int		i;
	int		j;
	char	*tmp2;

	i = 0;
	while (tmp[i])
	{
		j = i + 1;
		while (tmp[j])
		{
			if (ft_strncmp(tmp[i], tmp[j]) > 0)
			{
				tmp2 = tmp[i];
				tmp[i] = tmp[j];
				tmp[j] = tmp2;
			}
			j++;
		}
		i++;
	}
}

char	**reserve_names(void)
{
	int				count;
	char			**names;
	DIR				*dir;
	struct dirent	*en;

	count = 0;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	while (1)
	{
		en = readdir(dir);
		if (en == NULL)
			break ;
		if (ft_strncmp(en->d_name, ".") == 0 || \
			ft_strncmp(en->d_name, "..") == 0 || en->d_name[0] == '.')
			continue ;
		count++;
	}
	closedir(dir);
	names = ft_calloc(count + 3, sizeof(char *));
	if (names == NULL)
		return (NULL);
	return (names);
}

void	fill_names(char **names)
{
	int				count;
	DIR				*dir;
	struct dirent	*en;

	count = 0;
	dir = opendir(".");
	if (dir == NULL)
		return (perror("opendir"));
	while (1)
	{
		en = readdir(dir);
		if (en == NULL)
			break ;
		if (ft_strncmp(en->d_name, ".") == 0 || \
			ft_strncmp(en->d_name, "..") == 0 || en->d_name[0] == '.')
			continue ;
		names[count++] = ft_strdup(en->d_name);
	}
	closedir(dir);
	sort_p(names);
}
