/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:06 by gsapio            #+#    #+#             */
/*   Updated: 2024/04/12 14:25:38 by gsapio           ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <pthread.h>
# include <sys/resource.h>


# define RED "\001\x1b[1;31m\002"
# define WHITE "\001\x1b[1;0m\002"
extern int g_exit_status;

typedef char *t_str;

typedef struct s_simcmd
{
    char	*cmd_wargs;
	char    *path;
} t_simcmd;

typedef struct s_cmd
{
	t_simcmd    cmd;
    int         fd[2];
    pid_t       pid;
} t_cmd;

// typedef struct s_cmdline
// {
//     t_cmd       *cmd_table;
//     //optional cmd_separator
// } t_cmdline;

typedef struct s_shell
{
    char        *input;
	char		**args;
	t_list		*tokens;
    t_cmd       *cmd_table;
    char        ***my_env;
} t_shell;

// Builtins
void	ft_cd(t_shell *shell);
void	ft_pwd(t_shell *shell);
void	ft_echo(t_shell *shell);
void	ft_env(t_shell *shell);
void	ft_export(t_shell *shell);
void	ft_unset(t_shell *shell);
void	ft_exec(t_shell *shell);

// Garbage collector
void	*ft_malloc(size_t size);
void	clear_garbage(void);
t_list	**garbage_collector(void);
char    ***ft_myenv(void);
void	ft_free_array(char **array);

// utils
char    *ft_getenv(char *str, int flag);
void    ft_exit(int exit_code, char *str);
char	*ft_readline(const char *str);

// lexer and expnader
void	ft_lexer(t_shell *shell);
int    question_mark_handler(char *str, int *index, char **tmp2, int brack_flag);
void	handle_quotes(t_shell *shell, int i, int *quotes);
int	    is_reserved_export(char ch);

// altsplit
char	**ft_altsplit(char *s, char c);
char	find_quotetype(const char *s, size_t i, char quote);
int		find_unquoted(const char *s, char c, size_t start);
int		find_quoted(const char *s, char quote, size_t start);

#endif
