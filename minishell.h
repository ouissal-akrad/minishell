/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 00:16:06 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/10 10:21:50 by bel-idri         ###   ########.fr       */
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

/*----------------------------STRUCTS------------------------------*/
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
}					t_quote;

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

typedef struct s_prvrest
{
	char			*prev;
	char			*rest;
	int				plus;
	int				flag;
}					t_prvrest;

typedef struct s_main
{
	char			*line;
	t_tokens		*tokens;
	t_data			*data;
	t_env			*new_env;
}					t_main;

typedef struct s_global
{
	int				backup_stdin;
	int				exitt;
	int				g_exit;
	int				data_s;
	int				g_env;
}					t_global;

typedef struct s_csp
{
	char			*prev;
	char			*rest;
	int				plus;
}					t_csp;

typedef struct s_exec
{
	char			**env;
	char			*path;
}					t_exec;

/*----------------------------GLOBAL------------------------------*/
t_global			g_global;
/*----------------------------MAIN------------------------------*/
void				start(t_main *main, int argc, char *argv[], char *env[]);
char				*read_line(void);
int					read_line_empty(char *line);
int					parsing(t_main *main);
int					check_exit_hdoc(t_main *main);
void				configs(t_main *main);
void				fin_line(t_main *main);
void				fin_program(t_main *main);
/*----------------------------PARSING------------------------------*/
/*----------------------------parsing------------------------------*/
void				add_tok_split(char **split, t_tokens **tmp,
						t_tokens **tokens);
void				split_var_no_quote(t_tokens **tokens);
void				free_remove(t_tokens *tmp);
int					check_remove_null_1(t_tokens *tmp);
int					check_remove_null_2(t_tokens *tmp);
int					expand_env_halper_2(int *i, char *str, t_expvar *exp);
int					expand_env_halper(char *str, int *i, t_expvar *exp,
						t_env *env);
int					the_big_check(char *str, int i, int state, t_expvar exp);
char				*expand_env(char *str, t_env *env, int state);
void				expanding(t_tokens **tokens, t_env *env);
int					syntax_error(t_tokens *tokens);
void				remove_quotes(t_tokens *tokens);
char				*replace_space(char *str);
char				*get_val(char *var, t_env *env, int quote);
int					count_j(char *str, int i);
void				rl_hdoc(void);
int					syntax_error_hdoc(char *str, t_tokens *tokens, int i);
int					syntax_error_halper(t_tokens *tmp, t_tokens *tokens, int i);
int					syntax_error_quote(t_tokens *tokens);
void				lexar(char *str, t_tokens **tokens);
int					check_quotes(char *str);
int					check_char(char *str, char c);
void				add_is_d(t_tokens **tokens);
int					syntax_error_msg(char *str);
char				*add_spaces(char *str);
void				add_token(t_tokens **tokens, char *str, t_token type);
char				**split_tokens(char *str);
void				free_tokens(t_tokens **tokens);
void				free_str(char **str);
void				is_quote(char *str, int i, int *quote);
char				*my_ft_strjoin_1(char *s1, char *s2);
int					is_whitespace(char c);
int					count_tok(char *str);
void				add_spaces_handler(char *str, char *new);
void				remove_null_tokens(t_tokens **tokens);
int					check_no_expanding_valid(char *str);
void				ambiguous_redirect(t_tokens **tokens);
int					count_n_tokens(t_tokens *tokens);
void				ft_lstadddd_back(t_data **data, t_data *new);
void				ft_lstnewnode(t_data *new, t_tokens **tokens);
void				creat_nodes(t_data **data, t_tokens **tokens);
void				go_to_pipe(t_tokens **tokens);
int					open_files_error(t_tokens *tmp);
void				free_2_str(char *str1, char *str2);
void				expanding_wildcard(t_tokens **tokens);
t_tokens			*ft_lstnew_token_w(char *str, char *var);
void				ft_lstadd_in_second_place(t_tokens **lst, t_tokens *new);
void				sort_p(char **tmp);
char				**reserve_names(void);
void				fill_names(char **names);
char				*get_line(char *line, t_env *env);
char				*my_ft_strjoin_2(char *s1, char *s2);
int					open_files_helper(t_data *tmpd, t_tokens *tmp);
void				amgi_msg(t_data *tmp_data, t_tokens **tmp);
void				open_files(t_data **data, t_tokens **tokens);
void				open_hdoc_helper(t_data **tmp_data, t_tokens *tmp,
						t_env *env);
void				open_hdoc(t_data **data, t_tokens **tokens, t_env *env);
void				create_data(t_data **data, t_tokens **tokens, t_env *env);
void				free_env(t_env **env);
void				open_files_hdoc_tmp(t_data **data);
void				is_a_dir_helper(t_data *tmp);
void				is_a_directory(t_data **data);
void				close_files(t_data *data);
int					check_only_w(char *str);
void				open_hdoc_helper(t_data **tmp_data, t_tokens *tmp,
						t_env *env);
void				open_hdoc(t_data **data, t_tokens **tokens, t_env *env);
void				create_data(t_data **data, t_tokens **tokens, t_env *env);
void				free_env(t_env **env);
void				free_data(t_data **data);
int					do_open_in(t_data *tmpd, t_tokens *tmp);
int					do_open_out(t_data *tmpd, t_tokens *tmp);
int					do_open_app(t_data *tmpd, t_tokens *tmp);

/*----------------------------signals------------------------------*/
void				sigg(int sig);
void				sig_handler(int sig);
void				sig(void);
/*----------------------------EXECUTION------------------------------*/
/*----------------------------builtins------------------------------*/
void				direction(t_data *data, t_env **new_env);
int					is_builtins(char *cmd);
/*----------------------------cd------------------------------*/
void				my_cd(t_env **env, t_data *data);
void				update_env(t_env **env, char *oldpwd, char *pwd);
char				*find(t_env *env, char *to_find);
char				*go_home(t_env **env);
char				*go_oldpwd(t_env **env);
void				change_directory(t_env **env, char *path);
void				print_working_directory(void);
void				parent(char *path);
void				error_msg_1(char *path);
void				error_msg_2(char *path);
/*----------------------------echo------------------------------*/
void				my_echo(t_data *data);
int					newline_checker(char *str);
/*----------------------------env------------------------------*/
void				my_env(t_env **env, t_data *data);
void				print_env(t_env *env, t_data *data);
void				delete_node(t_env *head);
void				ft_lstadd_backk(t_env **lst, t_env *new);
t_env				*ft_lstneww(char *env_name, char *env_content);
t_env				*create_list(char *str[]);
void				ft_lstfree(t_env **head);
void				shlvl(t_env **env);
t_env				*no_env(void);
int					array_size(char **str);
/*----------------------------pwd------------------------------*/
void				my_pwd(t_data *data);
/*----------------------------unset------------------------------*/
void				my_unset(t_env **env, t_data *data, int i);
/*----------------------------exit------------------------------*/
void				my_exit(t_env **env, t_data *data);
int					all_digit(char *str);
/*----------------------------export------------------------------*/
void				my_export(t_env **env, t_data *data);
void				print_error_csp(char *data_cmd);
void				ft_csp(t_env **env, t_data *data, int c);
void				sequal_helper(t_env *existing_var, char *rest);
void				sequal(t_env **env, char *prev, char *rest, int plus);
int					all_str(char *str);
t_env				*find_env(t_env *env, char *name);
void				print_env_ex_helper(t_data *data, t_env *tmp);
void				print_env_ex(t_env *env, t_data *data);
int					check_value(char *str);
int					check(char *str);
int					count_plus(char *str);
void				swap_env(t_env *a, t_env *b);
void				sort_env(t_env **env);
t_env				*create_new_env(const t_env *original);
int					check_valid_csp(t_data *data, char *tmp, size_t cmd);
t_csp				initial_csp(void);
int					csp_h(t_csp *csp, char *tmp, t_env *env, char *data_arg);
int					csp_helper(char *data_arg, int i, t_csp *csp, char *tmp);
t_env				*copy_env_list(const t_env *original_head);
void				modify_g_exit(void);
/*----------------------------execution------------------------------*/
void				free_leaks(char **paths);
char				*join_path(char *path, char *cmd);
char				*find_path(char *cmd, char *envp[]);
void				exec_cmd(t_data *data, char *path, char **env,
						t_env **env_list);
void				exec_pipe(t_data *data, t_env *env_list);
char				**env_list_to_char_array(t_env *env_list, int i);
void				exec_builtin(t_data *data, t_env **new_env);
void				do_exec(t_data *data, char *path, char **env,
						t_env **env_list);
void				one_cmd(t_data *tmp, t_exec exec, t_env **env_list);
void				go_child_ocmd(t_data *data, char *path, char **env,
						t_env **env_list);
void				failed(int ex);
int					do_fork(t_data *data, t_env **env_list, t_exec exec,
						int pipefd[]);
void				go_child_mp(t_data *data, t_env **env_list, t_exec exec,
						int pipefd[]);
void				re_call(t_data *tmp, t_exec exec, t_env *env_list,
						int pipefd[]);
/*----------------------------libft------------------------------*/
char				*ft_strcat(char *dest, char *src);
char				*ft_strcpy(char *dest, char *src);
int					ft_lstsizee(t_env *lst);
int					data_size(t_data *lst);
int					ft_strncmp_2(const char *s1, const char *s2, size_t n);
/*-----------------------------Errors--------------------------------*/
void				err_cmd(t_data *data);
void				err_isdir(t_data *data);
void				err_permission(t_data *data);
void				err_nodir(t_data *data);
void				go_child_ocmd(t_data *data, char *path, char **env,
						t_env **env_list);
void				failed(int ex);
void				go_child_mp(t_data *data, t_env **env_list, t_exec exec,
						int pipefd[]);
#endif
