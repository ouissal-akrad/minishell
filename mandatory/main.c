#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char		*line;
	t_tokens	*tokens;

	t_env		*env_list;
	t_tokens	*tmp;


	(void)argc;
	(void)argv;

	env_list = create_list(env); // free env_list
	// char *type[] = {"Word", "Pipe", "In", "Out", "App", "Hdoc"};


	tokens = NULL;



	line = readline("minishell$ ");
	while (line)
	{
		add_history(line);
		lexar(line, &tokens);

		if (syntax_error(tokens))
		{
			free_tokens(&tokens);
			line = readline("minishell$ ");
			continue ;
		}


		//expand_env(&tokens, env_list);
		// remove_quotes(tokens);



		expanding(&tokens, env_list);
		remove_quotes(tokens);

		tmp = tokens;


		while (tmp)
		{
			printf("str: %s\n", tmp->str);
			tmp = tmp->next;
		}



		free_tokens(&tokens);
		line = readline("minishell$ ");
	}
	return (0);
}
