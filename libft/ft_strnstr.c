/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 16:01:26 by bel-idri          #+#    #+#             */
/*   Updated: 2022/10/30 20:10:22 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_if_match(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	count;

	i = 0;
	count = 0;
	while (i < len)
	{
		j = 0;
		k = i;
		while (needle[j] == haystack[k] && haystack[k] && k < len)
		{
			count++;
			j++;
			k++;
		}
		if (count == ft_strlen(needle))
			return ((char *)&haystack[i]);
		count = 0;
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	lh;

	if (!haystack && len == 0)
		return (NULL);
	lh = ft_strlen(haystack);
	if (ft_strlen(needle) > len)
		return (NULL);
	if (needle[0] == '\0')
		return ((char *)haystack);
	if (lh == 0)
		return (NULL);
	return (ft_if_match(haystack, needle, len));
}
