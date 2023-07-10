/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:52 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/09 15:07:02 by ouakrad          ###   ########.fr       */
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
	t_env *prev = NULL;
	t_env *cur = *env;

	int i = 2;
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