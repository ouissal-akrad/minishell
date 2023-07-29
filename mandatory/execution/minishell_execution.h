/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_execution.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouakrad <ouakrad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 13:35:12 by bel-idri          #+#    #+#             */
/*   Updated: 2023/07/29 19:44:17 by ouakrad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXECUTION_H
# define MINISHELL_EXECUTION_H

# include "../minishell.h"
# include <errno.h>
# include <limits.h>
# include <string.h>

int		g_exit;
/*-------------------------builtins-------------------------------*/
void direction(t_data *data,t_env **new_env);
int is_builtins(char *cmd);
/*----------------cd---------------------*/
void	my_cd(t_env **env, t_data *data);
void	update_env(t_env *env, char *oldpwd, char *pwd);
char	*find(t_env *env, char *to_find);
/*----------------echo---------------------*/
void	my_echo(t_data *data);
int		newline_checker(char *str);
/*----------------env---------------------*/
void	my_env(t_env **env);
void	print_env(t_env *env);
void	delete_node(t_env *head);
void	ft_lstadd_backk(t_env **lst, t_env *new);
t_env	*ft_lstneww(char *env_name, char *env_content);
t_env	*create_list(char *str[]);
void	ft_lstfree(t_env **head);
void	shlvl(t_env *env);
t_env	*no_env(void);
/*----------------pwd---------------------*/
void	my_pwd(void);
/*----------------unset---------------------*/
void	my_unset(t_env **env, t_data *data);
/*----------------exit---------------------*/
void	my_exit(t_env **env,t_data *data);
int		all_digit(char *str);
/*----------------export---------------------*/
void	my_export(t_env **env, t_data *data);
void	ft_csp(t_env *env, t_data *data, int c);
void	sort_env(t_env **env);
void	swap_env(t_env *a, t_env *b);
void	print_env_ex(t_env *env);
int		all_str(char *str);
void	my_export(t_env **env, t_data *data);
t_env	*find_env(t_env *env, char *name);
void	sequal(t_env *env, char *prev, char *rest, int plus);
/*----------------execution---------------------*/
void	free_leaks(char **paths);
char	*join_path(char *path, char *cmd);
char	*find_path(char *cmd, char *envp[]);
void	exec_cmd(t_data *data,char *path,char **env, t_env **env_list, int *pipefd);
void exec_pipe(t_data *data, t_env *env_list);
char	**env_list_to_char_array(t_env *env_list);
void	exec_builtin(t_data *data, t_env **new_env);

#endif
