/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_executing.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:35:12 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/25 07:08:23 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTING_H
# define MINISHELL_EXECUTING_H

# include "../minishell.h"
# include <errno.h>
# include <limits.h>
#include <string.h>

int		g_exit;
/*-------------------------builtins-------------------------------*/
void	direction(char **l, t_env **new_env);
/*----------------cd---------------------*/
void	my_cd(t_env **env, char **args);
void	update_env(t_env *env, char *oldpwd, char *pwd);
char	*find(t_env *env, char *to_find);
/*----------------echo---------------------*/
void	my_echo(char **str);
int		newline_checker(char *str);
/*----------------env---------------------*/
void	my_env(t_env **env);
void	print_env(t_env *env);
void	delete_node(t_env *head, char *var);
void	ft_lstadd_backk(t_env **lst, t_env *new);
t_env	*ft_lstneww(char *env_name, char *env_content);
t_env	*create_list(char *str[]);
void	ft_lstfree(t_env **head);
void shlvl(t_env *env);
/*----------------pwd---------------------*/
void	my_pwd(void);
/*----------------unset---------------------*/
void	my_unset(t_env **env, char **args);
/*----------------exit---------------------*/
void	my_exit(t_env **env, char **str);
int		all_digit(char *str);
/*----------------export---------------------*/
void	my_export(t_env **env, char **cmd);
void	sort_env(t_env **env);
void	swap_env(t_env *a, t_env *b);
void	print_env_ex(t_env *env);
int		all_str(char *str);
void	ft_csp(t_env *env, char **s, int c);
t_env	*find_env(t_env *env, char *name);
void	sequal(t_env *env, char *prev, char *rest, int plus);
/*----------------execution---------------------*/
char	*join_path(char *path, char *cmd);
char	*find_path(char *cmd, char *envp[]);
void	free_leaks(char **paths);
void	execution(char *av[], char **env, int i);
void	pipex( t_env *env);
void	second(char *av[], char **env, int pfd[2]);
void	first(char *av[], char **env, int pfd[2]);
char	**env_list_to_char_array(t_env *env_list);
#endif