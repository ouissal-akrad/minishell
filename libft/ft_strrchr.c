/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:05:45 by bel-idri          #+#    #+#             */
/*   Updated: 2022/10/30 11:46:00 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	x;

	x = ft_strlen(s) + 1;
	while (x--)
	{
		if ((char)s[x] == (char)c)
			return ((char *)s + x);
	}
	return (NULL);
}
