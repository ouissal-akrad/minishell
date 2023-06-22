/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:35:14 by bel-idri          #+#    #+#             */
/*   Updated: 2023/06/22 16:18:55 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "../minishell.h"

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
	APP // >>
} 				t_token;

typedef struct s_tokens
{
	char			*str;
	t_token	type;
	struct s_tokens	*next;
}					t_tokens;


#endif
