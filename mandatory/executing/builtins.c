/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:52 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/11 19:57:14 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executing.h"

void	my_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		printf("pwd: Error occurred.\n");
	else
		printf("%s\n", cwd);
}

void	my_env(t_env **env)
{
	print_env(env);
}

void	my_unset(t_env **env, char **args)
{
	t_env	*prev;
	t_env	*cur;
	int		i;

	prev = NULL;
	cur = *env;
	i = 2;
	while (args[i] != NULL)
	{
		cur = *env;
		prev = NULL;
		while (cur != NULL)
		{
			if (ft_strcmp(cur->var, args[i]) == 0)
			{
				if (prev == NULL)
					*env = cur->next;
				else
					prev->next = cur->next;
				free(cur->var);
				free(cur->val);
				free(cur);
				break ;
			}
			prev = cur;
			cur = cur->next;
		}
		i++;
	}
	print_env(env);
}

void	my_echo(char **str)
{
	int	i;
	int	check;

	i = 3;
	check = 0;
	int fd = 1;
	int new_line = 1;
	printf("=====>%s\n",str[i]);
	if (str[i] && !ft_strcmp(str[i], "-n"))
	{
		new_line = 0;
		i++;
	}
	if (str[i] && str[i + 1] && !ft_strcmp(str[i + 1], ">"))
	{
		fd = open(str[i + 2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		str[i + 1] = NULL;
		str[i + 2] = NULL;
	}
	while (str[i] && ft_strncmp(str[i], "-", 1) == 0)
		i++;
	while (str[i] && ft_strcmp(str[i], ""))
	{
		dprintf(fd, "%s ", str[i]);
		i++;
	}
	if (new_line)
		dprintf(fd, "\n");
	close(fd);
	return ;
}
