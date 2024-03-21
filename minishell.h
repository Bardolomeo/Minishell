/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:23:06 by gsapio            #+#    #+#             */
/*   Updated: 2024/03/21 13:42:12 by gsapio           ###   ########.fr       */
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

typedef struct s_simcmd
{
	char *path;
	char **cmd;
} t_simcmd;

typedef struct s_cmd
{
	t_simcmd cmd;
	char *redirection;
	char *f_name;

} t_cmd;

typedef struct s_cmdline
{
    t_cmd *cmd;
    //optional cmd_separator
} t_cmdline;

#endif
