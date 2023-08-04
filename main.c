/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 03:20:11 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/04 02:17:08 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *env[])
{
	char		*line;
	t_tokens	*tokens;
	t_data		*data;
	t_env		*new_env;

	(void)argv;
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
		g_global.exitt = 0;
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
		if (g_global.exitt == 1)
		{
			// unlink_file(tokens, data);
			if (data)
				free_data(data);
			data = NULL;
			// close files
			continue ;
		}
		open_files_hdoc_tmp(&data);
		// unlink_file

		is_a_directory(&data);



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
		// 	printf("is_dir = %d\n",tmp->is_dir);
		// 	printf("-----------------\n");

		// 	tmp = tmp->next;
		// }

		g_global.data_s = data_size(data);
		direction(data,&new_env);

		free_data(data);
		// close files
		data = NULL;
	}
	clear_history();
	free_env(&new_env);
	return (0);
}
