/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executing.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:35:12 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/14 14:41:44 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTING_H
# define MINISHELL_EXECUTING_H

# include "../minishell.h"
# include <errno.h>
# include <limits.h>


/*------------int		g_exit;
-------------builtins-------------------------------*/

/*----------------cd---------------------*/
void	my_cd(t_env **env, char **args);
void	update_env(t_env *env, char *oldpwd, char *pwd);
char	*find(t_env **env, char *to_find);
/*----------------echo---------------------*/
void	my_echo(char **str);
int		newline_checker(char *str);
/*----------------env---------------------*/
void	my_env(t_env *env);
void	print_env(t_env *env);
void	delete_node(t_env *head, char *var);
void	ft_lstadd_backk(t_env **lst, t_env *new);
t_env	*ft_lstneww(char *env_name, char *env_content);
t_env	*create_list(char *str[]);
/*----------------pwd---------------------*/
void	my_pwd(void);
/*----------------unset---------------------*/
void	my_unset(t_env **env, char **args);
/*----------------exit---------------------*/
void	my_exit(char **str);
int		all_digit(char *str);
#endif