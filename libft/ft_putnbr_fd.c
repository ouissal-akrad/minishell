/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:22:57 by bel-idri          #+#    #+#             */
/*   Updated: 2022/10/28 08:59:30 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

void	ft_putnbr_fd(int n, int fd)
{
	int	d;
	int	m;

	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n *= (-1);
		ft_putnbr_fd(n, fd);
	}
	else if (n >= 10)
	{
		m = n % 10;
		d = n / 10;
		n = d;
		ft_putnbr_fd(n, fd);
		ft_putchar_fd(m + '0', fd);
	}
	else if (n >= 0 && n < 10)
		ft_putchar_fd(n + '0', fd);
}
