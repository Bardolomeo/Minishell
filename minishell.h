/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:06 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/09 17:30:19 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <pthread.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED "\001\x1b[1;31m\002"
# define WHITE "\001\x1b[1;0m\002"

extern int				g_signal;

typedef char			*t_str;
typedef __sighandler_t	t_sig;

typedef struct s_uns_ind
{
	int					i;
	int					j;
}						t_uns_ind;

typedef struct s_exp_vars
{
	int					i;
	int					bra_flag;
	int					quotes[2];
	char				*tmp2;
	int					f_break ;
}						t_exp_vars;

typedef struct s_simcmd
{
	char				**cmd_wargs;
	char				*path;
}						t_simcmd;

typedef struct s_cmd
{
	t_simcmd			cmd;
	char				io[3][255];
	pid_t				pid;
}						t_cmd;

typedef struct s_shell
{
	char				*input;
	char				**args;
	t_list				*tokens;
	t_cmd				*cmd_table;
	char				***my_env;
}						t_shell;

typedef struct s_gpv_vars
{
	char				**env;
	char				**paths;
	char				*path;
	int					j;
	int					k;
}						t_gpv_vars;

typedef struct s_exec_vars
{
	int					cmd_count;
	int					status;
	int					*fd;
	int					i;
}						t_exec_vars;

// Builtins
void					ft_cd(t_shell *shell, int i);
void					ft_pwd(t_shell *shell, int i);
void					ft_echo(t_shell *shell, int i);
void					ft_env(t_shell *shell, int i);
void					ft_export(t_shell *shell, int i, char *pflag);
void					ft_unset(t_shell *shell, int i);
int						export_error(void);
void					export_no_args(t_shell *shell);
void					add_empty_env(char *env, char ***my_env);
void					add_env(t_shell *shell, char *key, char *value);

// Garbage collector
void					*ft_malloc(size_t size);
void					clear_garbage(void);
t_list					**garbage_collector(void);
void					ft_free_array(char **array);
void					clear_garbage_no_unlink(void);

// singletons
int						*n_doc(void);
char					***ft_myenv(void);
int						*fd_stand_out(void);
int						*fd_stand_in(void);
int						*exit_status(void);

// utils
char					*ft_getenv(char *str, int flag);
void					ft_error(int exit_code, char *str);
char					*ft_readline(const char *str, int heredoc);
int						is_reserved_export(char ch);

// lexer and expander
void					ft_lexer(t_shell *shell);
int						question_mark_handler(char *str, int *index,
							char **tmp2, int brack_flag);
void					handle_quotes(t_shell *shell, int i, int *quotes);
int						redirect_no_expand(t_shell *shell, int i);
int						expand_wo_brackets(char *str, int *i, char **tmp2,
							int *bra_flag);
int						find_end_bracket(char *str, int *i, int *j, int *index);
int						handle_brackets(char *str, int *index, int *bra_flag,
							char **tmp2);
int						long_ass_condition(t_shell *shell, int *quotes, int i);
void					init_expander(t_exp_vars *vars);
void					get_env_loop(char *str, int bra_flag, int *len);
int						fill_input(char *str, int *i, char **tmp2,
							int bra_flag);

// parser
int						ft_parser(t_shell *shell);
int						create_heredoc(char *limiter, int *n_doc);
void					heredoc_signal_exit(int fd);
int						heredoc_input_setter(t_shell *shell, char *limiter,
							int j, int k);
int						red_doc_loop_no_quotes(t_shell *shell, int *tmp,
							char *quotes);
int						redirect_heredoc_loop(t_shell *shell, int *tmp, int *k,
							char *limiter);
int						redirect_heredoc(t_shell *shell, int j, int *i);
int						create_heredoc_parent(int pid, int *status, int fd);
void					create_heredoc_child(char *limiter, int fd);
int						create_heredoc(char *limiter, int *n_doc);
int						redirect_output(t_shell *shell, int *i, int j);
int						redirect_input(t_shell *shell, int j, int *i);
int						redirect_append(t_shell *shell, int j, int *i);
void					namefile_no_quotes(t_shell *shell, int *tmp, int j,
							int n_io);
void					namefile_quotes(t_shell *shell, int *i, int j,
							int n_io);
void					initialize_cmd_table(t_shell *shell, int cmd_count);

// executor
void					ft_executor(t_shell *shell);
int						count_cmds(t_shell *shell);
void					check_exit(t_shell *shell);
int						check_single_command(int cmd_count, int **fd,
							t_shell *shell);
void					execute_child(t_shell *shell, int i, int *fd,
							int cmd_count);
void					execute_parent(int cmd_count, int i, int *fd);
void					connect_pipe(int *fd, int cmd_count);
int						set_dup2(t_shell *shell, int i, int *fd, int cmd_count);
int						check_builtins(t_shell *shell, int i, char *pflag);
int						reset_io(t_shell *shell);
void					init_first_pipe(int *fd, int i);
void					init_mid_pipe(int *fd, int i);
void					init_last_pipe(int *fd, int i);

// signals
void					set_signals(const char *flag);
void					sighandle_command(int signal);

// altsplit
char					find_quotetype(const char *s, int *i, char quote,
							int *in_arr);
int						find_unquoted(const char *s, char c, size_t start);
int						find_quoted(const char *s, char quote, size_t start,
							char c);
void					special_check(char *to_check, char quote);
void					ft_altcount_arr_loop(char const *s, char c,
							size_t *count);
size_t					ft_altcount_arr(char const *s, char c);
void					skip_quotes(const char *s, size_t *start, char *quote);
size_t					ft_altstrlen(const char *s, size_t start, char c,
							char quote);
char					**ft_altsplit(char *s, char c);

#endif
