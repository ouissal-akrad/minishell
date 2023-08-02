#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char		*line;
	t_tokens	*tokens;
	t_data		*data;
	t_env		*new_env;

	if (argc > 1)
	{
		write(2, "Error: too many arguments\n", 26);
		return (1);
	}

	t_data		*tmp;

	if (!*env)
	{
		new_env = no_env();
		new_env->flag = 1;
	}
	else
	{
		new_env = create_list(env);
		new_env->flag = 0;
	}
	tokens = NULL;
	data = NULL;
	line = NULL;
	while (1)
	{
		exitt = 0;
		sig();
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue ;
		}
		add_history(line);
		lexar(line, &tokens);
		free(line);
		add_is_d(&tokens);
		if (syntax_error(tokens))
		{
			free_tokens(&tokens);
			tokens = NULL;
			continue ;
		}
		expanding(&tokens, new_env);
		split_var_no_quote(&tokens);
		ambiguous_redirect(&tokens);
		remove_quotes(tokens);
		remove_null_tokens(&tokens);
		if (!tokens)
			continue ;
		create_data(&data, &tokens, new_env);
		free_tokens(&tokens);
		tokens = NULL;
		if (!data)
			continue ;
		if (exitt == 1)
		{
			// unlink_file(tokens, data);
			if (data)
				free_data(&data);
			data = NULL;
			// close files
			continue ;
		}
		open_files_hdoc_tmp(&data);
		// unlink_file

		// if (is_a_directory(data, new_env))
		// {
		// 	free_tokens(&tokens);
		// 	free_data(&data);
		// 	tokens = NULL;
		// 	data = NULL;
		// 	// close files
		// 	continue ;
		// }



		tmp = data;
		// int i = 0;
		// while (tmp)
		// {
		// 	printf("-----------------\n");
		// 	while (tmp->args[i])
		// 	{
		// 		printf("args[%d] = %s\n",i,tmp->args[i]);
		// 		i++;
		// 	}
		// 	printf("in = %d\n",tmp->in);
		// 	printf("out = %d\n",tmp->out);
		// 	printf("hdoc = %d\n",tmp->hdoc);
		// 	printf("buff = %s\n",tmp->buff);
		// 	printf("-----------------\n");

		// 	tmp = tmp->next;
		// }
		data_s = data_size(data);
		direction(data,&new_env);

		free_data(&data);
		// close files
		data = NULL;
	}
	clear_history();
	free_env(&new_env);
	return (0);
}

//  if -1 no exucte
