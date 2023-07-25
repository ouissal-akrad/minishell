/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:35:14 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/25 03:23:04 by bel-idri         ###   ########.fr       */
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
int	redirections(t_tokens **tokens, t_data **data);

void expanding(t_tokens **token, t_env *env);
void split_var_no_quote(t_tokens **token);
void add_is_d(t_tokens **tokens);
void remove_null_tokens(t_tokens **tokens);
void ambiguous_redirect(t_tokens **tokens);
int create_data(t_data **data, t_tokens *tokens, t_env *env);
void free_data(t_data **data);
void free_env(t_env **env);




#endif
