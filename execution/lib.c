/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/30 18:47:33 by ouakrad           #+#    #+#             */
/*   Updated: 2023/08/04 01:16:10 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if(!src)
		return (dest);
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_lstsizee(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

int    data_size(t_data *lst)
{
    int        i;
    t_data    *tmp;

    tmp = lst;
    i = 0;
    while (tmp)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}

int	ft_strncmp_2(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	if (!s1[i] || !s2[i])
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	all_free(t_data *data, t_env *env)
{
	int	i;
	t_env	*tmp;
	t_data	*tmp2;

	i = -1;
	if (data)
	{
		tmp2 = data->next;
		if (data->args)
		{
			while (data->args[++i])
				free(data->args[i]);
			free(data->args);
		}
		if (data->buff)
			free(data->buff);
		free(data);
		data = tmp2;

	}
	i = -1;
	if (env)
	{
		tmp = env->next;
		if (env->val)
		{
			if (env->val)
				free(env->val);
		}
		if (env->var)
		{
			if (env->var)
				free(env->var);
		}
		free(env);
		env = tmp;
	}
}
