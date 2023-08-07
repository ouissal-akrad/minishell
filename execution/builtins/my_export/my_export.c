/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:46:00 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/07 02:00:46 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	my_export(t_env **env, t_data *data)
{
	t_env	*cpy;

	if (!data->args[1])
	{
		cpy = copy_env_list(*env);
		sort_env(&cpy);
		print_env_ex(cpy, data);
		ft_lstfree(&cpy);
	}
	else
		ft_csp(*env, data, '=');
}

void	print_error_csp(char *data_cmd)
{
	write(2, "minishell: export: `", 20);
	write(2, data_cmd, ft_strlen(data_cmd));
	write(2, "': not a valid identifier\n", 26);
	g_global.g_exit = 1;
}

void	ft_csp(t_env *env, t_data *data, int c)
{
	size_t	i;
	size_t	cmd;
	char	*tmp;
	t_csp	csp;

	cmd = 0;
	while (data->args[++cmd])
	{
		csp = initial_csp();
		tmp = data->args[cmd];
		i = check_valid_csp(data, tmp, cmd);
		if (i == 0)
			continue ;
		if (tmp[i] == c)
		{
			if (csp_helper(data->args[cmd], i, &csp, tmp))
				continue ;
		}
		if (csp_h(&csp, tmp, env, data->args[cmd]))
			continue ;
	}
	modify_g_exit();
}

void	sequal_helper(t_env *existing_var, char *rest)
{
	free(existing_var->val);
	if (!rest)
		existing_var->val = NULL;
	else
		existing_var->val = ft_strdup(rest);
}

void	sequal(t_env *env, char *prev, char *rest, int plus)
{
	t_env	*new_var;
	t_env	*existing_var;
	char	*old_val;

	existing_var = find_env(env, prev);
	if (existing_var != NULL)
	{
		if (plus && existing_var->val)
		{
			old_val = ft_strdup(existing_var->val);
			free(existing_var->val);
			existing_var->val = ft_strjoin(old_val, rest);
			free(old_val);
		}
		else
			sequal_helper(existing_var, rest);
	}
	else
	{
		new_var = ft_lstneww(prev, rest);
		if (new_var == NULL)
			return ;
		ft_lstadd_backk(&env, new_var);
	}
	free(prev);
}
