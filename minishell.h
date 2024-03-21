/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:06 by gsapio            #+#    #+#             */
/*   Updated: 2024/03/21 17:02:51 by gsapio           ###   ########.fr       */
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
    t_cmd       *cmd_table;
    char        **my_env;
} t_shell;

typedef struct s_garb
{
    void  *ptr;
    struct s_garb *next;
} t_garb;

#endif
