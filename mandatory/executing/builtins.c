/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:52 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/08 20:43:19 by ouakrad          ###   ########.fr       */
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

void	my_unset(t_env **env, char *var)
{
	t_env	*prev;
	t_env	*cur;

	prev = NULL;
	cur = *env;
	while (cur != NULL)
	{
		if (ft_strcmp(cur->var, var) == 0)
		{
			if (prev == NULL)
				*env = cur->next;
			else
				prev->next = cur->next;
			free(cur->var);
			free(cur->val);
			free(cur);
            print_env(env);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}
