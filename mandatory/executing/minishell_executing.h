/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executing.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:35:12 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/14 10:07:45 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTING_H
# define MINISHELL_EXECUTING_H

# include "../minishell.h"
# include <errno.h>
# include <limits.h>

/*-------------------------builtins-------------------------------*/
void	my_cd(t_env **env, char **args);
void	update_env(t_env *env, const char *oldpwd, const char *pwd);
char	*find(t_env **env, char *to_find);

void	my_echo(char **str);
int		newline_checker(char *str);

void	my_env(t_env *env);
void	print_env(t_env *env);
void	delete_node(t_env *head, char *var);
void	ft_lstadd_backk(t_env **lst, t_env *new);
t_env	*ft_lstneww(char *env_name, char *env_content);
t_env	*create_list(char *str[]);

void	my_pwd(void);

void	my_unset(t_env **env, char **args);
#endif