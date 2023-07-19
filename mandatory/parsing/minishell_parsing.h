/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:35:14 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/19 07:56:26 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "../minishell.h"

void	is_quote(char *str, int i, int *quote);
int	count_tokens(char *str);
char	*add_spaces(char *str);
void	add_token(t_tokens **tokens, char *str, t_token type);
char	**split_tokens(char *str);
void	free_tokens(t_tokens **tokens);
void	free_str(char **str);
void	lexar(char *str, t_tokens **tokens);
int	syntax_error_msg(char *str);
int	syntax_error_halper(t_tokens *tmp);
int	syntax_error_quote(t_tokens *tokens);
int	syntax_error(t_tokens *tokens);
void	remove_quotes(t_tokens *tokens);
int	redirections(t_tokens *red);

void expanding(t_tokens **token, t_env *env);


#endif
