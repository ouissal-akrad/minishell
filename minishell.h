/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:16:06 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/04 02:10:45 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

/*---------------STRUCTS----------------*/
typedef struct s_env
{
	char			*var;
	char			*val;
	int				flag;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	char			**args;
	int				in;
	int				out;
	int				hdoc;
	char			*buff;
	int				is_dir;
	struct s_data	*next;
}					t_data;

typedef enum e_quote
{
	OQ,
	SQ,
	DQ
}			t_quote;

typedef enum e_token
{
	WORD,
	PIPE,
	IN,
	OUT,
	APP,
	HDOC
}					t_token;

typedef struct s_tokens
{
	char			*str;
	t_token			type;
	int				is_d;
	char			*var;
	struct s_tokens	*next;
}					t_tokens;

typedef struct s_expvar
{
	int				j;
	int				k;
	int				quote;
	char			*var;
	char			*val;
	char			*final;
	char			*backup;
}					t_expvar;

typedef struct s_global
{
	int				g_exit;
	int				backup_stdin;
	int				exitt;
	int				data_s;
}					t_global;

t_global			g_global;

/*---------------PARSING-----------------*/
void				is_quote(char *str, int i, int *quote);
char				*my_ft_strjoin_1(char *s1, char *s2);
int					is_whitespace(char c);
int					count_tok(char *str);
void				add_spaces_handler(char *str, char *new);
char				*add_spaces(char *str);
void				add_token(t_tokens **tokens, char *str, t_token type);
char				**split_tokens(char *str);
void				free_tokens(t_tokens **tokens);
void				free_str(char **str);
void				lexar(char *str, t_tokens **tokens);
int					check_quotes(char *str);
int					check_char(char *str, char c);
void				add_is_d(t_tokens **tokens);
int					syntax_error_msg(char *str);
void				rl_hdoc(void);
void				syntax_error_hdoc_helper(char *str);
int					syntax_error_hdoc(char *str, t_tokens *tokens, int i);
int					syntax_error_halper(t_tokens *tmp, t_tokens *tokens, int i);
int					syntax_error_quote(t_tokens *tokens);
int					syntax_error(t_tokens *tokens);
void				remove_quotes(t_tokens *tokens);
char				*replace_space(char *str);
char				*get_val(char *var, t_env *env, int quote);
int					count_j(char *str, int i);
int					expand_env_halper_2(int *i, char *str, t_expvar *exp);
int					expand_env_halper(char *str, int *i, t_expvar *exp,
						t_env *env);
void				exit_calloc_2(char *str);
int					the_big_check(char *str, int i, int state, t_expvar exp);
char				*expand_env(char *str, t_env *env, int state);
void				expanding(t_tokens **tokens, t_env *env);
void				add_tok_split(char **split, t_tokens **tmp,
						t_tokens **tokens);
void				split_var_no_quote(t_tokens **tokens);
void				free_remove(t_tokens *tmp);
void				remove_null_tokens(t_tokens **tokens);
int					check_no_expanding_valid(char *str);
void				ambiguous_redirect(t_tokens **tokens);
int					count_n_tokens(t_tokens *tokens);
void				exit_calloc(t_data **data, t_tokens **tokens);
void				ft_lstadddd_back(t_data **data, t_data *new);
void				ft_lstnewnode(t_data *new, t_tokens **tokens);
void				creat_nodes(t_data **data, t_tokens **tokens);
void				go_to_pipe(t_tokens **tokens);
int					open_files_error(t_tokens *tmp);
void				free_2_str(char *str1, char *str2);
char				*get_line(char *line, t_env *env);
char				*my_ft_strjoin_2(char *s1, char *s2);
int					open_files_helper(t_data *tmp_d, t_tokens *tmp);
void				error_ambg(t_data *tmp_data, t_tokens **tmp);
void				error_files(t_tokens **tmp);
void				open_hdoc_helper(t_data **tmp_data, t_tokens *tmp,
						t_env *env);
void				open_hdoc(t_data **data, t_tokens **tokens, t_env *env);
void				create_data(t_data **data, t_tokens **tokens, t_env *env);
void				free_data(t_data *data);
void				free_env(t_env **env);
void				open_files_hdoc_tmp(t_data **data);
void				is_a_directory(t_data **data);
void				sigg(int sig);
void				sig_handler(int sig);
void				sig(void);

/*---------------EXECUTION-----------------*/
/*-------------------------builtins-------------------------------*/
void				direction(t_data *data, t_env **new_env);
int					is_builtins(char *cmd);
/*----------------cd---------------------*/
void				my_cd(t_env **env, t_data *data);
void				update_env(t_env *env, char *oldpwd, char *pwd);
char				*find(t_env *env, char *to_find);
char				*go_home(t_env **env);
char				*go_oldpwd(t_env **env);
void				change_directory(t_env **env, char *path);
void				print_working_directory(void);
void				parent(char *path);
/*----------------echo---------------------*/
void				my_echo(t_data *data);
int					newline_checker(char *str);
/*----------------env---------------------*/
void				my_env(t_env **env, t_data *data);
void				print_env(t_env *env, t_data *data);
void				delete_node(t_env *head);
void				ft_lstadd_backk(t_env **lst, t_env *new);
t_env				*ft_lstneww(char *env_name, char *env_content);
t_env				*create_list(char *str[]);
void				ft_lstfree(t_env **head);
void				shlvl(t_env *env);
t_env				*no_env(void);
/*----------------pwd---------------------*/
void				my_pwd(t_data *data);
/*----------------unset---------------------*/
void				my_unset(t_env **env, t_data *data);
/*----------------exit---------------------*/
void				my_exit(t_env **env, t_data *data);
int					all_digit(char *str);
/*----------------export---------------------*/
void				my_export(t_env **env, t_data *data);
void				ft_csp(t_env *env, t_data *data, int c);
void				sort_env(t_env **env);
void				swap_env(t_env *a, t_env *b);
void				print_env_ex(t_env *env, t_data *data);
int					all_str(char *str);
void				my_export(t_env **env, t_data *data);
t_env				*find_env(t_env *env, char *name);
void				sequal(t_env *env, char *prev, char *rest, int plus);
/*----------------execution---------------------*/
void				free_leaks(char **paths);
char				*join_path(char *path, char *cmd);
char				*find_path(char *cmd, char *envp[]);
void				exec_cmd(t_data *data, char *path, char **env,
						t_env **env_list, int *pipefd);
void				exec_pipe(t_data *data, t_env *env_list);
char				**env_list_to_char_array(t_env *env_list);
void				exec_builtin(t_data *data, t_env **new_env);
/*----------------LIBFT---------------------*/
char				*ft_strcat(char *dest, char *src);
char				*ft_strcpy(char *dest, char *src);
int					ft_lstsizee(t_env *lst);
int					data_size(t_data *lst);
int					ft_strncmp_2(const char *s1, const char *s2, size_t n);
void	all_free(t_data *data, t_env *env);

#endif
