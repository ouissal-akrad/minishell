/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:48:45 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/10 16:55:19 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	check_valid_csp(t_data *data, char *tmp, size_t cmd)
{
	int	i;

	i = 0;
	if (tmp[0] != '_' && !ft_isalpha(tmp[0]))
	{
		print_error_csp(data->args[cmd]);
		return (0);
	}
	while (tmp[i] && tmp[i] != '=')
		i++;
	return (i);
}

void	modify_g_exit(void)
{
	if (g_global.g_exit == 1)
		g_global.g_exit = 1;
	else if (g_global.g_exit == 0)
		g_global.g_exit = 0;
}

t_csp	initial_csp(void)
{
	t_csp	csp;

	csp.plus = 0;
	csp.prev = NULL;
	csp.rest = NULL;
	return (csp);
}

int	csp_h(t_csp *csp, char *tmp, t_env **env, char *data_arg)
{
	if (check_value(tmp))
		csp->prev = ft_strdup(tmp);
	else
		return (print_error_csp(data_arg), 1);
	if (!check(csp->prev))
		return (print_error_csp(data_arg), free(csp->prev), 1);
	sequal(env, csp->prev, csp->rest, csp->plus);
	return (0);
}

int	csp_helper(char *data_arg, int i, t_csp *csp, char *tmp)
{
	if (ft_strchr(tmp, '+') != NULL)
	{
		if (count_plus(tmp) == 1)
			csp->plus = 1;
		else if (count_plus(tmp) == -1)
		{
			print_error_csp(data_arg);
			return (1);
		}
		csp->prev = tmp;
		csp->prev[i - csp->plus] = '\0';
		csp->rest = tmp + i + 1;
	}
	else
	{
		csp->prev = tmp;
		csp->prev[i] = '\0';
		csp->rest = tmp + i + 1;
	}
	return (0);
}
