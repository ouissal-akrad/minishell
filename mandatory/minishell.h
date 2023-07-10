/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:16:06 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/10 21:31:14 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>

typedef struct s_env
{
	char	*var;
	char	*val;
	struct s_env	*next;
}			t_env;

typedef struct s_file
{
	// int	type;
	int out; 
	int in;
	int app;
	// char *file_name;
}			t_file;

typedef struct s_data
{
	char	*cmd; // only cmd
	char	**args; // args[0] = cmd
	t_env	env;
	t_file	file;
	struct s_data	*next;
}			t_data;

# endif
