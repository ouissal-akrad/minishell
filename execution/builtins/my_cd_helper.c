/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 06:49:10 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 07:01:29 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find(t_env *env, char *to_find)
{
	t_env	*e;

	e = env;
	while (e)
	{
		if (ft_strncmp(e->var, to_find) == 0)
			return (ft_strdup(e->val));
		e = e->next;
	}
	return (NULL);
}

void	error_msg_1(char *path)
{
	write(2, "minishell: cd: ", 16);
	write(2, path, ft_strlen(path));
	write(2, ": Not a directory\n", 18);
	g_exit = 1;
}

void	error_msg_2(char *path)
{
	write(2, "minishell: cd: ", 16);
	write(2, path, ft_strlen(path));
	write(2, ": No such file or directory\n", 28);
	g_exit = 1;
}

char	*go_home(t_env **env)
{
	char	*path;

	path = find(*env, "HOME");
	if (path == NULL)
	{
		write(2, "cd: HOME not set\n", 17);
		g_exit = 1;
		return (NULL);
	}
	return (path);
}

char	*go_oldpwd(t_env **env)
{
	char	*path;

	path = find(*env, "OLDPWD");
	if (path == NULL)
	{
		write(2, "cd: OLDPWD not set\n", 19);
		g_exit = 1;
		return (NULL);
	}
	return (path);
}
