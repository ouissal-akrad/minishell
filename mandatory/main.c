#include "minishell.h"

// void	sig(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 	}
// }

void ff(void)
{
	system("leaks minishell");
}

int	main(int argc, char *argv[], char *env[])
{
	atexit(ff);
	char		*line;
	t_tokens	*tokens;
	t_data		*data;
	t_env		*new_env;

	t_tokens	*tmp_t;
	t_data		*tmp;
	(void)argc;
	(void)argv;
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
	while (1)
	{
		// signal(SIGINT, &sig);
		line = readline("minishell$ ");
		if (!line)
		{
			printf("exit HNAA\n");
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
		if (!tokens)
			continue ;
		split_var_no_quote(&tokens);
		ambiguous_redirect(&tokens);
		remove_quotes(tokens);
		remove_null_tokens(&tokens);
		create_data(&data, &tokens, new_env);

		if (!data)
		{
			free_tokens(&tokens);
			tokens = NULL;
			free(line);
			continue ;
		}

		tmp_t = tokens;
		// while (tmp_t)
		// {
		// 	printf("str = %s\n", tmp_t->str);
		// 	printf("type = %d\n", tmp_t->type);
		// 	printf("is_d = %d\n", tmp_t->is_d);
		// 	printf("var = %s\n", tmp_t->var);
		// 	printf("-------------------\n");
		// 	tmp_t = tmp_t->next;
		// }


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


		// ME
		// direction(data,&new_env);

		free_tokens(&tokens);
		free_data(&data);
		tokens = NULL;
		data = NULL;
	}
	clear_history();
	free_env(&new_env);
	return (0);
}

//  if -1 no exucte
