/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 09:55:46 by bel-idri          #+#    #+#             */
/*   Updated: 2022/10/30 19:24:33 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(const char *str, size_t i)
{
	return (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || \
			str[i] == '\v' || str[i] == '\f' || str[i] == '\r');
}

int	my_atio(const char *str, int i, int sign)
{
	size_t	res;
	size_t	temp;

	res = 0;
	while (ft_isdigit(str[i]))
	{
		temp = res;
		res = (res * 10) + (str[i] - 48);
		if (temp != res / 10 && sign == 1)
			return (-1);
		if (temp != res / 10 && sign == -1)
			return (0);
		i++;
	}
	if (res >= 9223372036854775807ull && sign == 1)
		return (-1);
	if (res > 9223372036854775807ull && sign == -1)
		return (0);
	return ((int)res * sign);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		i;

	sign = 1;
	i = 0;
	while (ft_isspace(str, i))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	return (my_atio(str, i, sign));
}
