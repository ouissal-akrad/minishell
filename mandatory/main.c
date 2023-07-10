#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char		*line;
	t_tokens	*tokens;

	t_env		*env_list;
	t_tokens	*tmp;

	t_data *data;
	// t_data *tmp2;

	(void)argc;
	(void)argv;

	env_list = create_list(env); // free env_list
	// char *type[] = {"Word", "Pipe", "In", "Out", "App", "Hdoc"};


	tokens = NULL;
	data = NULL;

	line = readline("minishell$ ");
	while (line)
	{
		lexar(line, &tokens);

		if (syntax_error(tokens))
		{
			free_tokens(&tokens);
			line = readline("minishell$ ");
			continue ;
		}

		// expand_env(&tokens, env_list);
		remove_quotes(tokens);

		tmp = tokens;

		while (tmp)
		{

			printf("str: %s\n", tmp->str);
			printf("type: %d\n", tmp->type);
			tmp = tmp->next;
		}

		// excution

		// fill data datastruct
		// check builtins
		//execute cmd --> pipe or cmd line

		tmp2 = data;

		while (data)
		{
			printf("cmd: %s\n", data->cmd);
			printf("args: ");
			int i = 0;
			while (data->args[i])
			{
				printf("%s ", data->args[i]);
				i++;
			}
			printf("\n");
			printf("file: ");
			printf("out: %d ", data->file.out);
			printf("in: %d ", data->file.in);
			printf("app: %d ", data->file.app);
			printf("\n");

			data = data->next;
		}


		free_tokens(&tokens);
		line = readline("minishell$ ");
	}
	return (0);
}
