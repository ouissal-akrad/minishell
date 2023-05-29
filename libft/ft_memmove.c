/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 17:04:02 by bel-idri          #+#    #+#             */
/*   Updated: 2022/10/30 10:00:48 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*a;
	char	*b;

	if (!dst && !src)
		return (NULL);
	i = -1;
	a = (char *)dst;
	b = (char *)src;
	if (a > b)
	{
		while (len)
		{
			a[len - 1] = b[len - 1];
			len--;
		}
	}
	else
	{
		while (++i < len)
			a[i] = b[i];
	}
	return (dst);
}
