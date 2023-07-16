/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:00 by ouakrad           #+#    #+#             */
/*   Updated: 2023/07/16 12:52:52 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_executing.h"

int	all_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A'
				&& str[i] <= 'Z'))
			i++;
		else
			return (0);
	}
	return (1);
}

t_env *find_env(t_env *env, char *name) 
{
    while (env != NULL)
	{
        if (ft_strcmp(env->var, name) == 0)
            return env;
        env = env->next;
    }
    return NULL;
}

void	print_env_ex(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (tmp->var != NULL && tmp->val != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->var, tmp->val);
		else
			printf("declare -x %s\n", tmp->var);
		tmp = tmp->next;
	}
}
void	swap_env(t_env *a, t_env *b)
{
	char	*var_temp;
	char	*val_temp;

	var_temp = a->var;
	val_temp = a->val;
	a->var = b->var;
	a->val = b->val;
	b->var = var_temp;
	b->val = val_temp;
}

void sort_env(t_env **env)
{
	t_env	*tmp;
	int		swapped;

	tmp = *env;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		while (tmp && tmp->next)
		{
			if (ft_strcmp(tmp->var, tmp->next->var) > 0)
			{
				swap_env(tmp, tmp->next);
				swapped = 1;
			}
			tmp = tmp->next;
		}
		tmp = *env;
	}
	print_env_ex(*env);
}

void	my_export(t_env **env, char **cmd)
{
	if (!cmd[1])
        sort_env(env);
	else
		ft_csp(*env, cmd, '=');
}
t_env *ft_csp(t_env *env, char **s, int c)
{
    size_t i;
    size_t cmd = 1;
    char *prev;
    char *rest;
    char *tmp;
    t_env *new_var;
    t_env *existing_var;


    while (s[cmd])
    {
        i = 0;
        prev = NULL;
        rest = NULL;
        tmp = ft_strdup(s[cmd]);
        if (!tmp)
            return env;
        //one arg
        if (tmp[0] == '=')
        {
            printf("minishell: export: `%s`: not a valid identifier\n", s[cmd]);
            free(tmp);
            return (env);
        }
        if (tmp[0] != '=')
        {
            if (ft_strchr(tmp, '=') == NULL)
            {
                if (ft_isalpha(tmp[0]) || tmp[0] == '_')
                {
                    // Create a new environment variable
                    new_var = ft_lstneww(s[cmd], NULL);
                    if (new_var == NULL)
                    {
                        free(tmp);
                        return (env);
                    }
                    // Add the new variable to the list
                    ft_lstadd_backk(&env, new_var);
                }
                else
                {
                    printf("minishell: export: `%s`: not a valid identifier\n", s[cmd]);
                    free(tmp);
                    return (env);
                }
            }
            // export with args
            else
            {
                while (tmp[i])
                {
                    if (tmp[i] == c)
                    {
                        prev = tmp;
                        prev[i] = '\0';
                        rest = tmp + i + 1;
                        break ;
                    }
                    i++;
                }
                if (prev)
                {
                    // Check if the variable name is valid
                    if (prev[0] == '_' || ft_isalpha(prev[0]))
                    {
                        i = 1;
                        while (prev[i])
                        {
                            if (!ft_isalnum(prev[i]) && prev[i] != '_')
                            {
                                printf("minishell: export:%s: not a valid identifier\n", s[cmd]);
                                free(tmp);
                                break;
                            }
                            i++;
                        }
                    }
                    else
                    {
                        printf("minishell: export: %s: not a valid identifier\n", s[cmd]);
                        free(tmp);
                        return (env);
                    }
                    // Check if the variable already exists
                    existing_var = find_env(env, prev);
                    if (existing_var != NULL)
                    {
                        free(existing_var->val);
                        // Duplicate the new value and store it in the existing variable
                        existing_var->val = ft_strdup(rest);
                        if (existing_var->val == NULL)
                        {
                            free(tmp);
                            return (env);
                        }
                    }
                    else
                    {
                        // Create a new environment variable
                        new_var = ft_lstneww(prev, rest);
                        if (new_var == NULL)
                        {
                            free(tmp);
                            return (env);
                        }
                        // Add the new variable to the list
                        ft_lstadd_backk(&env, new_var);
                    }
                }
            }
            free(tmp);
        }
        s++;
    }
    //resort env
    sort_env(&env);
    puts("-------------------");
    print_env_ex(env);
    puts("-------------------");
    return (env);
}