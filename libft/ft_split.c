/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 08:42:44 by bel-idri          #+#    #+#             */
/*   Updated: 2022/10/30 14:31:40 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(char const *s, char c)
{
	int	index;
	int	counter;

	index = 0;
	counter = 0;
	if (ft_strlen(s) == 0)
		return (0);
	while (s[index] == c)
		index++;
	while (s[index])
	{
		if (s[index] == c)
		{
			counter++;
			while (s[index] == c)
				index++;
		}
		else
			index++;
	}
	if (s[index - 1] != c)
		counter++;
	return (counter);
}

static void	ft_free(char **str)
{
	int	index;

	index = 0;
	while (str[index])
		free(str[index++]);
	free(str);
}

static char	**ft_my_split(char const *s, char c, int start, int end)
{
	char	**str;
	int		index;

	index = 0;
	str = (char **)malloc((ft_count_words(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	while (index < ft_count_words(s, c) && s[start])
	{
		start = end;
		while (s[start] && s[start] == c)
			start++;
		end = start;
		while (s[end] && s[end] != c)
			end++;
		str[index] = ft_substr(s, start, end - start);
		if (!str[index])
		{
			ft_free(str);
			return (NULL);
		}
		index++;
	}
	str[index] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		start;
	int		end;

	end = 0;
	start = 0;
	if (!s)
		return (NULL);
	str = ft_my_split(s, c, start, end);
	if (!str)
		return (NULL);
	return (str);
}
