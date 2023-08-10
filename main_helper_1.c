/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 11:14:11 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/10 08:13:55 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start(t_main *main, int argc, char *argv[], char *env[])
{
	rl_catch_signals = 0;
	g_global.g_exit = 0;
	g_global.exitt = 0;
	(void)argv;
	if (argc > 1)
	{
		write(2, "Error: too many arguments\n", 26);
		exit(1);
	}
	if (!*env)
		main->new_env = no_env();
	else
		main->new_env = create_list(env);
	main->tokens = NULL;
	main->data = NULL;
	main->line = NULL;
	sig();
}

char	*read_line(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		printf("exit\n");
		exit(g_global.g_exit);
	}
	return (line);
}

int	read_line_empty(char *line)
{
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (1);
	}
	add_history(line);
	return (0);
}

int	parsing(t_main *main)
{
	lexar(main->line, &main->tokens);
	free(main->line);
	add_is_d(&main->tokens);
	if (syntax_error(main->tokens))
	{
		free_tokens(&main->tokens);
		main->tokens = NULL;
		return (1);
	}
	expanding(&main->tokens, main->new_env);
	expanding_wildcard(&main->tokens);
	split_var_no_quote(&main->tokens);
	ambiguous_redirect(&main->tokens);
	remove_quotes(main->tokens);
	remove_null_tokens(&main->tokens);
	if (!main->tokens)
		return (1);
	create_data(&main->data, &main->tokens, main->new_env);
	free_tokens(&main->tokens);
	main->tokens = NULL;
	if (!main->data)
		return (1);
	return (0);
}

int	check_exit_hdoc(t_main *main)
{
	if (g_global.exitt == 1)
	{
		if (main->data)
			free_data(&main->data);
		main->data = NULL;
		close_files(main->data);
		g_global.exitt = 0;
		return (1);
	}
	return (0);
}
