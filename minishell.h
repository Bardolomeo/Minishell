/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:06 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/08 13:58:47 by gsapio           ###   ########.fr       */
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

// Builtins
void					ft_cd(t_shell *shell, int i);
void					ft_pwd(t_shell *shell, int i);
void					ft_echo(t_shell *shell, int i);
void					ft_env(t_shell *shell, int i);
void					ft_export(t_shell *shell, int i, char *pflag);
void					ft_unset(t_shell *shell, int i);

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
