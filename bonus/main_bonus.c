#include "minishell_bonus.h"

int main(int argc, char *argv[], char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;

	char *line;
	line = readline("minishell$ ");

	while (line)
	{
		// code
		free(line);
		line = readline("minishell$ ");
	}
	return (0);
}
