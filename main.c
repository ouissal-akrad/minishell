#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;

	char *line;
	// t_data data;

	while ((line = readline("minishell$ ")))
	{
		// data = ft_parsing(argv, env);





		free(line);
	}
	return (0);
}
