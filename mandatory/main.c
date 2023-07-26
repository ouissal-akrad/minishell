#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char		*line;
	t_tokens	*tokens;
	t_data		*data;
	t_env		*new_env;

	t_tokens	*tmp_t;
	t_data		*tmp;


	(void)argc;
	(void)argv;

	if(!*env)
		new_env = no_env();
	else
		new_env = create_list(env);


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

		expanding(&tokens, new_env);
		split_var_no_quote(&tokens);

		ambiguous_redirect(&tokens);
		remove_quotes(tokens);
		remove_null_tokens(&tokens);
		create_data(&data, tokens, new_env);


		tmp_t = tokens;

		while (tmp_t)
		{
			printf("str = %s\n", tmp_t->str);
			printf("type = %d\n", tmp_t->type);
			printf("is_d = %d\n", tmp_t->is_d);
			printf("var = %s\n", tmp_t->var);
			printf("-------------------\n");
			tmp_t = tmp_t->next;
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


		//direction(l,&new_env);
		// hna


		close_files(data);
		tokens = NULL;
		free_data(&data);
		data = NULL;
		line = readline("minishell$ ");
	}
	clear_history();
	free_env(&new_env);
	return (0);
}


// s > "" : double free

// bash-3.2$ export y="a b"
// bash-3.2$ ls > $y
// bash: $y: ambiguous redirect

// minishell$ ls > $USER
// minishell: $USER: ambiguous redirect


//  if -1 no exucte
//bash-3.2$ ls -la > f r
//ls: r: No such file or directory
// bash-3.2$ ls -la > "" r
// bash: : No such file or directory
