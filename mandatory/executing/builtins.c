/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:21:52 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/13 01:28:58 by ouakrad          ###   ########.fr       */
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
	i = 1;
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
	// print_env(env);
}

/*
echo "hello"
------------------------
name="ouissal"
echo "My name is $name"
------------------------
echo "This text will be saved in a file." > file.txt
------------------------
echo "$(cat file.txt)"
------------------------
echo "$(pwd)"

*/
/*
cmd =====> args[0 ]= echo
args = -n
file = fd;
*/

int	newline_checker(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	my_echo(char **args)
{
	int	i;
	int	new_line;
	int	flag;

	i = 2;
	flag = 0;
	new_line = 1;
	while (args[i])
	{
		while (newline_checker(args[i]) == 1 && flag == 0)
		{
			i++;
			new_line = 0;
		}
		flag = 1;
		printf("%s", args[i]);
		if (args[++i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
}

char	*find_path(t_env **env, char *to_find)
{
	while (*env)
	{
		if (ft_strcmp((*env)->var, to_find) == 0)
			return ((*env)->val);
		(*env) = (*env)->next;
	}
	return (NULL);
}

void	my_cd(t_env **env, char **args)
{
	char *path = NULL;
	if (args[1] == NULL)
	{
		path = find_path(env, "HOME");
		if (path == NULL)
		{
			printf("cd: HOME not set\n");
			return ;
		}
	}
	else
		path = args[1];
	if (chdir(path) == -1)
	{
		printf("cd: no such file or directory: %s\n", path);
		return ;
	}
	//cd . retriving create 3 folders
	// unset pwd unset OLDPWD
}