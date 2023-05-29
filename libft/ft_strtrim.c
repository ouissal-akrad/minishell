/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:45:33 by bel-idri          #+#    #+#             */
/*   Updated: 2022/10/30 19:47:34 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_start(char const *s1, char const *set)
{
	size_t	start;
	size_t	index;
	size_t	count;

	start = 0;
	index = 0;
	while (s1[start])
	{
		while (set[index])
		{
			if (s1[start] == set[index])
				count++;
			index++;
		}
		if (count > 0)
		{
			index = 0;
			count = 0;
			start++;
		}
		else
			break ;
	}
	return (start);
}

static size_t	ft_end(char const *s1, char const *set)
{
	size_t	end;
	size_t	index;
	size_t	count;

	count = 0;
	index = 0;
	end = ft_strlen(s1) - 1;
	while (end >= 0)
	{
		while (set[index])
		{
			if (s1[end] == set[index])
				count++;
			index++;
		}
		if (count > 0)
		{
			index = 0;
			count = 0;
			end--;
		}
		else
			break ;
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*str;

	if (!set)
		return (ft_strdup(s1));
	if (!s1)
		return (NULL);
	if (ft_start(s1, set) == ft_strlen(s1) - 1 || !s1 || s1[0] == '\0')
		return (ft_strdup(""));
	start = ft_start(s1, set);
	end = ft_end(s1, set);
	str = ft_substr(s1, start, end - start + 1);
	return (str);
}
