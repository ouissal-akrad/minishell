/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:57 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/13 01:28:56 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_executing.h"

t_env	*ft_lstneww(char *env_name, char *env_content)
	// remove after work in general main
{
	t_env *new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->var = env_name;
	new->val = env_content;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_backk(t_env **lst, t_env *new)
	// remove after work in general main
{
	t_env *tmp;

	tmp = *lst;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	print_env(t_env **env)
{
	while (*env != NULL)
	{
		printf("%s=%s\n", (*env)->var, (*env)->val);
		(*env) = (*env)->next;
	}
}

t_env	*create_list(char *str[]) // remove after work in general main
{
	t_env *env;
	char **str1;
	int i;

	i = 0;
	env = NULL;
	while (str[i])
	{
		str1 = ft_split(str[i], '=');
		ft_lstadd_backk(&env, ft_lstneww(str1[0], str1[1]));
		i++;
	}
	// print_env(env);
	return (env);
}

int	main(int ac, char **av, char *env[])
{
	char	*line;
	char	**l;
	t_env	*new_env;

	(void)ac;
	(void)av;
	line = readline("minishell$ ");
	while (line)
	{
		new_env = create_list(env);
		add_history(line);
		l = ft_split(line, ' ');
		if (ft_strcmp(l[0], "env") == 0)
			my_env(&new_env);
		else if (ft_strcmp(l[0], "pwd") == 0)
			my_pwd();
		else if (ft_strcmp(l[0], "unset") == 0)
			my_unset(&new_env, l);
		else if (ft_strcmp(l[0], "echo") == 0)
			my_echo(l);
		else if (ft_strcmp(l[0], "cd") == 0)
			my_cd(&new_env, l);
		// else if (ft_strcmp(av[1], "export") == 0)
		// 	my_export();
		// else if (ft_strcmp(av[1], "exit") == 0)
		// 	ft_exit();
		free(line);
		line = readline("minishell$ ");
	}
}
