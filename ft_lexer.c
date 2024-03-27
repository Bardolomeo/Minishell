/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:49:55 by mtani             #+#    #+#             */
/*   Updated: 2024/03/27 18:49:39 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_getenv(char *str)
{
    int     i;
    int     len;
    t_str   *myenv;

    myenv = *ft_myenv();
    i = -1;
    while (myenv[++i])
    {
        len = ft_strlen(myenv[i]) - ft_strlen(ft_strchr(myenv[i], '='));        
        if (ft_strncmp(myenv[i], str, len) == 0)
            return(ft_strchr(myenv[i], '=') + 1);
    }
    return (NULL);
    
}

void    expander(t_shell *shell)
{
    int i;
    char *tmp;
    char *tmp2;

    i = 0;
    while (shell->input[i])
    {
        if (shell->input[i] == '$')
        {
            tmp = ft_substr(shell->input, 0, i);
            tmp2 = ft_strjoin(tmp, ft_getenv(shell->input + i + 1));
            shell->input = tmp2;
        }
        i++;
    }
}

void	ft_lexer(t_shell *shell)
{
    // char    **mtx;

    expander(shell);
    // mtx = ft_split(shell->input, '|');
}