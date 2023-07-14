/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:57 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/14 10:00:15 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executing.h"

int	main(int ac, char **av, char *env[])
{
	char	*line;
	char	**l;
	t_env	*new_env;

	(void)ac;
	(void)av;
	line = readline("minishell$ ");
	new_env = create_list(env);
	while (line)
	{
		add_history(line);
		l = ft_split(line, ' ');
		if (ft_strcmp(l[0], "pwd") == 0)
			my_pwd();
		else if (ft_strcmp(l[0], "unset") == 0)
			my_unset(&new_env, l);
		else if (ft_strcmp(l[0], "echo") == 0)
			my_echo(l);
		else if (ft_strcmp(l[0], "cd") == 0)
			my_cd(&new_env, l);
		else if (ft_strcmp(l[0], "env") == 0)
			my_env(new_env);
		// else if (ft_strcmp(av[1], "export") == 0)
		// 	my_export();
		// else if (ft_strcmp(av[1], "exit") == 0)
		// 	ft_exit();
		free(line);
		line = readline("minishell$ ");
	}
}
