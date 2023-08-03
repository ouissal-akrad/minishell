/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:41:40 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/03 01:46:43 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	tall_str(const char *s1, const char *s2)
{
	size_t	n;

	if (ft_strlen(s1) > ft_strlen(s2))
		n = ft_strlen(s1);
	else
		n = ft_strlen(s2);
	return (n);
}

int	ft_strncmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	n;

	n = tall_str(s1, s2);
	i = 0;
	if (n == 0)
		return (0);
	if (!s1 || !s2)
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
