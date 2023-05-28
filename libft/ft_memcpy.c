/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:44:59 by bel-idri          #+#    #+#             */
/*   Updated: 2022/10/30 17:40:25 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*x;

	if (!dst && !src)
		return (NULL);
	x = (char *)src;
	i = 0;
	while (i < n)
	{
		ft_memset(dst + i, x[i], 1);
		i++;
	}
	return (dst);
}
