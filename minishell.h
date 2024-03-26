/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:06 by gsapio            #+#    #+#             */
/*   Updated: 2024/03/26 12:01:32 by mtani            ###   ########.fr       */
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

# define RED "\001\x1b[1;31m\002"
# define WHITE "\001\x1b[1;0m\002"

typedef char *t_str;

typedef struct s_simcmd
{
    t_str  *cmd_wargs;
	char    *path;
} t_simcmd;

typedef struct s_cmd
{
	t_simcmd    cmd;
    int         fd[2];

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
    t_cmd       *cmd_table;
    char        **my_env;
} t_shell;

// Builtins

void	ft_cd(t_shell *shell);
void	ft_pwd(void);
void	ft_echo(t_shell *shell);
void	ft_env(t_shell *shell);
void	ft_export(t_shell *shell);
void	ft_unset(t_shell *shell);
void	ft_exec(t_shell *shell);

// Garbage collector

void	*ft_malloc(size_t size);
void	clear_garbage(void);
t_list	**garbage_collector(void);
void	ft_free_array(char **array);

#endif