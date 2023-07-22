/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:57 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/22 14:47:25 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executing.h"

void f()
{
	system("leaks minishell");
}

void direction(char **l,t_env **new_env)
{
		if (ft_strcmp(l[0], "pwd") == 0)
			my_pwd();
		else if (ft_strcmp(l[0], "unset") == 0)
			my_unset(new_env, l);
		else if (ft_strcmp(l[0], "echo") == 0)
			my_echo(l);
		else if (ft_strcmp(l[0], "cd") == 0)
			my_cd(new_env, l);
		else if (ft_strcmp(l[0], "env") == 0)
			my_env(new_env);
		else if (ft_strcmp(l[0], "exit") == 0)
			my_exit(new_env,l);
		else if (ft_strcmp(l[0], "export") == 0)
			my_export(new_env,l);
		// else
		// 	pipex(new_env);
}
t_env *no_env()
{
	t_env *env;
	char pwd[PATH_MAX];

	if(getcwd(pwd,PATH_MAX) == NULL)
		return NULL;
	ft_lstadd_backk(&env, ft_lstneww("PWD",pwd));
	ft_lstadd_backk(&env, ft_lstneww("SHLVL", "1"));
	ft_lstadd_backk(&env, ft_lstneww("_", "/usr/bin/env"));
	ft_lstadd_backk(&env, ft_lstneww("OLDPWD", NULL));
	//hiden
	ft_lstadd_backk(&env, ft_lstneww("PATH", "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."));
	ft_lstadd_backk(&env, ft_lstneww("SHELL", "/bin/zsh"));
	env->flag = 1;
	return (env);
}
int	main(int ac, char **av, char *env[])
{
	char	*line;
	char	**l;
	t_env	*new_env;

	(void)ac;
	(void)av;
	if(!*env)
		new_env = no_env();
	else
		new_env = create_list(env);
	line = readline("minishell$ ");
	// atexit(f);
	while (line)
	{
		add_history(line);
		l = ft_split(line, ' ');
		direction(l,&new_env);
		free(line);
		free_leaks(l);
		line = readline("minishell$ ");
	}
	clear_history();
	ft_lstfree(&new_env);
}