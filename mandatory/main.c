#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char		*line;
	t_tokens	*tokens;
	t_data		*data;
	t_env		*env_list;

	t_data		*tmp;


	(void)argc;
	(void)argv;

	env_list = create_list(env);


	tokens = NULL;
	data = NULL;


	line = readline("minishell$ ");
	while (line)
	{
		if (ft_strlen(line) == 0)
		{
			line = readline("minishell$ ");
			continue ;
		}

		add_history(line);
		lexar(line, &tokens);
		add_is_d(&tokens);
		if (syntax_error(tokens))
		{
			free_tokens(&tokens);
			tokens = NULL;
			line = readline("minishell$ ");
			continue ;
		}

		ambiguous_redirect(&tokens);
		expanding(&tokens, env_list);
		split_var_no_quote(&tokens);
		remove_quotes(tokens);
		remove_null_tokens(&tokens);

		if (create_data(&data, tokens, env_list))
		{
			free_tokens(&tokens);
			free_data(&data);
			tokens = NULL;
			data = NULL;
			line = readline("minishell$ ");
			close_files(data);
			continue ;
		}


		tmp = data;
		int i = 0;

		while (tmp)
		{
			i = 0;
			while (tmp->args[i])
			{
				printf("args[%d] = %s\n", i, tmp->args[i]);
				i++;
			}
			printf("in = %d\n", tmp->in);
			printf("out = %d\n", tmp->out);
			printf("-------------------\n");
			tmp = tmp->next;
		}



		close_files(data);
		free_tokens(&tokens);
		tokens = NULL;
		free_data(&data);
		data = NULL;
		line = readline("minishell$ ");
	}

	free_env(&env_list);
	return (0);
}


// s > "" : double free
