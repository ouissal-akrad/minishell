#include "minishell_bonus.h"

int main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;

	char *line;
	// t_data data;

	while ((line = readline("minishell$ ")))
	{
		// data = ft_parsing(line);





		free(line);
	}
	return (0);
}
