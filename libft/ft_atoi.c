/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:55:46 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/14 13:36:41 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check(const char *str)
{
	if ((ft_strlen(str) >= 19)
		&& (ft_strncmp(str, "9223372036854775807", 19) >= 0))
		return (-1);
	if (ft_strlen(str) >= 20
		&& ft_strncmp(str, "-9223372036854775808", 20) >= 0)
		return (0);
	return (1);
}	

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	value;
	int			check;

	i = 0;
	sign = 1;
	value = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
	check = ft_check(str);
	if (check != 1)
		return (check);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		value = value * 10 + str[i++] - '0';
	return (value * sign);
}