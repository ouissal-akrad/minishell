#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char		*line;
	t_tokens	*tokens;
	t_data		*data;

	t_env		*env_list;
	t_data	*tmp;


	(void)argc;
	(void)argv;

	env_list = create_list(env); // free env_list
	// char *type[] = {"Word", "Pipe", "In", "Out", "App", "Hdoc"};


	tokens = NULL;
	data = NULL;


	line = readline("minishell$ ");
	while (line)
	{
		add_history(line);
		lexar(line, &tokens);
		add_is_d(&tokens);
		if (syntax_error(tokens))
		{
			free_tokens(&tokens);
			line = readline("minishell$ ");
			continue ;
		}


		// expand_env(&tokens, env_list);



		ambiguous_redirect(&tokens);
		expanding(&tokens, env_list);
		split_var_no_quote(&tokens);
		remove_quotes(tokens);
		remove_null_tokens(&tokens);
		create_data(&data, tokens, env_list);
		// redirections(&tokens, &data);


		//ls > ""
		// write error in 2

		// bash-3.2$ ls > s > ""
		// bash: : No such file or directory
		// bash-3.2$ ls > s
		// bash-3.2$ ls > s > $r
		// bash: $r: ambiguous redirect
		// tmp->next->is_d = 2;
		// bash-3.2$ cat < $p > $e
		// bash: $p: ambiguous redirect





		tmp = data;
		int i = 0;

		while (tmp)
		{
			while (tmp->args[i])
			{
				printf("args: %s\n", tmp->args[i]);
				i++;
			}
			i = 0;
			printf("file in: %d | %s\n", tmp->file.in, tmp->file.in_name);
			printf("file out: %d | %s\n", tmp->file.out, tmp->file.out_name);
			printf("file app: %d | %s\n", tmp->file.app, tmp->file.app_name);
			printf("file hdoc: %d | %s\n", tmp->file.hdoc, tmp->file.hdoc_name);
			printf("-----------------\n");


			tmp = tmp->next;
		}




		// while (tmp)
		// {
		// 	printf("str: %s\n", tmp->str);
		// 	printf("type: %s\n", type[tmp->type]);
		// 	printf("is_d: %d\n", tmp->is_d);
		// 	printf("-----------------\n");
		// 	tmp = tmp->next;
		// }

		// free_tokens(&tokens);
		line = readline("minishell$ ");
	}
	return (0);
}
