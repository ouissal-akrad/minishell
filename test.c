#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char	*strchrt(char *s, int c)
{
	size_t	i;
	char	*prev;
	char	*rest;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			prev = strdup(s);
			prev[i] = '\0';
			rest = strdup(s + i + 1);
			return ((char *)&s[i + 1]);
		}
		i++;
	}
	if (s[i] == c)
	{
		prev = strdup(s);
		prev[i] = '\0';
		rest = strdup(s + i + 1);
		return ((char *)&s[i + 1]);
	}
	return (NULL);
}

int	main(void)
{
	printf("%s\n", strchrt("ouissalakd=1337", '='));
}