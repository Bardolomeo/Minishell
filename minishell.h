/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:06 by gsapio            #+#    #+#             */
/*   Updated: 2024/04/30 20:29:31 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*<command line>   ::=  <command> '|' <command line>
                  |   <command>

<command>        ::=  <simple command> '<' <filename>
                  |   <simple command> '>' <filename>
                  |   <simple command> '<<' <filename>
                  |   <simple command> '>>' <filename>
                  |   <simple command>

<simple command> ::=  <cmd path> <token list>

<token list>     ::=  <token> <token list>
                  |   (EMPTY)*/

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <pthread.h>
# include <sys/resource.h>
# include <signal.h>


# define RED "\001\x1b[1;31m\002"
# define WHITE "\001\x1b[1;0m\002"
extern int g_signal;

typedef char *t_str;
typedef __sighandler_t t_sig;

typedef struct s_simcmd
{
    char	**cmd_wargs;
	char    *path;
} t_simcmd;

typedef struct s_cmd
{
	t_simcmd    cmd;
    char		io[3][255];
    pid_t       pid;
} t_cmd;


typedef struct s_shell
{
    char        *input;
	char		**args;
	t_list		*tokens;
    t_cmd       *cmd_table;
    char        ***my_env;
} t_shell;

// Builtins
void	ft_cd(t_shell *shell, int i);
void	ft_pwd(t_shell *shell, int i);
void	ft_echo(t_shell *shell, int i);
void	ft_env(t_shell *shell, int i);
void	ft_export(t_shell *shell, int i, char *pflag);
void	ft_unset(t_shell *shell, int i);


// Garbage collector
void	*ft_malloc(size_t size);
void	clear_garbage(void);
t_list	**garbage_collector(void);
void	ft_free_array(char **array);
void	clear_garbage_no_unlink();

//singletons
int 	*n_doc(void);
char    ***ft_myenv(void);
int     *fd_stand_out();
int     *fd_stand_in();
int     *exit_status();

// utils
char    *ft_getenv(char *str, int flag);
void    ft_error(int exit_code, char *str);
char	*ft_readline(const char *str, int heredoc);
int		is_reserved_export(char ch);

// lexer and expander
void	ft_lexer(t_shell *shell);
int    	question_mark_handler(char *str, int *index, char **tmp2, int brack_flag);
void	handle_quotes(t_shell *shell, int i, int *quotes);
int	    redirect_no_expand(t_shell *shell, int i);

// parser
int 	ft_parser(t_shell *shell);
int		create_heredoc(char *limiter, int *n_doc);

// executor
void	ft_executor(t_shell *shell);
int		count_cmds(t_shell *shell);

// signals
void    set_signals(const char* flag);
void	sighandle_command(int signal);

// altsplit
char	**ft_altsplit(char *s, char c);
char	find_quotetype(const char *s, int *i, char quote, int *in_arr);
int		find_unquoted(const char *s, char c, size_t start);
int		find_quoted(const char *s, char quote, size_t start, char c);

#endif
