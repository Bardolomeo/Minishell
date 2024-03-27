/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:49:55 by mtani             #+#    #+#             */
/*   Updated: 2024/03/27 18:07:35 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_getenv(t_shell *shell, char *name)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 0;
    while (shell->my_env[i])
    {
        if (ft_strncmp(shell->my_env[i], name, ft_strlen(name)) == 0)
        {
            tmp = ft_strchr(shell->my_env[i], '=');
            return (tmp + 1);
        }
        i++;
    }
    return (NULL);
}

void    expander(t_shell *shell)
{
    int i;
    int j;
    char *tmp;
    char *tmp2;

    i = 0;
    j = 0;
    while (shell->input[i])
    {
        if (shell->input[i] == '$')
        {
            tmp = ft_substr(shell->input, 0, i);
            tmp2 = ft_strjoin(tmp, ft_getenv(shell, shell->input + i + 1));
            free(tmp);
            free(shell->input);
            shell->input = tmp2;
        }
        i++;
    }
}
void	ft_lexer(t_shell *shell)
{
    int		i;
    int		j;
    char    **mtx;

    i = 0;
    j = 0;
    expander(shell->input);
    mtx = ft_split(shell->input, '|');
}