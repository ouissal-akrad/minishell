/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:55:46 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/06 08:48:00 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	value;

	i = 0;
	sign = 1;
	value = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32 || str[i] == '0')
		i++;
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
