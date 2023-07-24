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


		//ls > ""
		// write error in 2

		// bash-3.2$ ls > s > ""
		// bash: : No such file or directory
		// bash-3.2$ ls > s
		// bash-3.2$ ls > s > $r
		// bash: $r: ambiguous redirect
		// tmp->next->is_d = 2;

		tmp = data;
		// int i = -1;
		// while (tmp)
		// {
		// 	while(tmp->args[++i])
		// 		printf("args[%d]=%s\n",i,tmp->args[i]);
		// 	printf("----------------------\n");
		// 	printf("in:%d\n", tmp->file.in);
		// 	printf("in:%d\n", tmp->file.out);
		// 	printf("in:%d\n", tmp->file.app);
		// 	tmp = tmp->next;
		// 	i = -1;
		// }



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
