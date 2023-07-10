/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 22:06:09 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/10 22:07:34 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

/// executing

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

/// parsing

typedef enum	e_quote
{
	OQ, // outside quote
	SQ, // single quote
	DQ // double quote
} 				t_quote;

typedef enum e_token
{
	WORD, // any string
	PIPE, // |
	IN, // <
	OUT, // >
	APP, // >>
	HDOC // <<
} 				t_token;

typedef struct s_tokens
{
	char			*str;
	t_token	type;
	struct s_tokens	*next;
}					t_tokens;

#endif
