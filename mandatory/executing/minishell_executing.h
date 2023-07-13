/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executing.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:35:12 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/13 01:28:20 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTING_H
# define MINISHELL_EXECUTING_H

# include "../minishell.h"
# include <limits.h>
# include <errno.h>

void	my_pwd(void);
void	my_env(t_env **env);
void	my_echo(char **str);
t_env	*create_list(char *str[]);
void	print_env(t_env **env);
void	my_unset(t_env **env, char **args);
void	my_cd(t_env **env,char **args);
#endif
