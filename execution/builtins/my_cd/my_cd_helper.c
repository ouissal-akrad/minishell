/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_cd_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 18:05:19 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/10 18:06:21 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	free_cd(t_my_cd my_cd)
{
	free(my_cd.path);
	free(my_cd.origin_oldpwd);
	free(my_cd.origin_pwd);
}

void	update_env_helper(t_env *e, t_my_cd *my_cd)
{
	if (ft_strncmp(e->var, "OLDPWD") == 0)
	{
		free(e->val);
		e->val = ft_strdup(my_cd->oldpwd);
	}
	else if (ft_strncmp(e->var, "PWD") == 0)
	{
		free(e->val);
		e->val = ft_strdup(my_cd->pwd);
	}
}

void	update_env_err_helper(t_env *e, t_my_cd *my_cd)
{
	if (ft_strncmp(e->var, "OLDPWD") == 0)
	{
		free(e->val);
		e->val = ft_strdup(my_cd->origin_oldpwd);
	}
	else if (ft_strncmp(e->var, "PWD") == 0)
	{
		free(e->val);
		e->val = ft_strdup(my_cd->origin_pwd);
	}
}
