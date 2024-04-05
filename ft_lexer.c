/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:49:55 by mtani             #+#    #+#             */
/*   Updated: 2024/04/05 11:02:06 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_getenv(char *str, int flag)
{
    int     i;
    int     len;
    t_str   *myenv;

    myenv = *ft_myenv();
    len = 0;
    i = -1;
    while (myenv[++i])
    {
        if (flag == 0)
        {
            while (str[len] && str[len] != ' ' && str[len] != '$' && str[len] != '\'' && str[len] != '\"' && str[len] != '|' && str[len] != ';' && str[len] != '>' && str[len] != '<' && str[len] != '&' && str[len] != '(' && str[len] != ')' && str[len] != '`' && str[len] != '\0')
                len++;
        }
        else
        {
            while (str[len] && str[len] != '}')
                len++;
        }
        if (ft_strncmp(myenv[i], str, len) == 0)
            return(ft_strchr(myenv[i], '=') + 1);
    }
    return (NULL);
}

int     fill_input(char *str, int *i, char **tmp2, int flag)
{
    char *tmp;
    char *tmpenv;
    
    tmp = NULL;
    tmpenv = ft_getenv(str + *i + 1, flag);
    if (tmpenv)
    {
        if (*tmp2 == NULL)
        {   
            tmp = ft_substr(str, 0, *i);
            *tmp2 = ft_strjoin(tmp, ft_getenv(str + *i + 1, flag));
        }
        else
            *tmp2 = ft_strjoin(*tmp2, ft_getenv(str + *i + 1, flag));
    }
    return (1);
}

void    expand_wo_brackets(char *str, int *i, char **tmp2, int *flag)
{
    *flag = fill_input(str, i, tmp2, 0);
    while (str[*i] && str[*i] != ' ')
    {
        if (str[*i + 1] == '$' || str[*i + 1] == '\'' || str[*i + 1] == '\"' || str[*i + 1] == '|' || str[*i + 1] == ';' || str[*i + 1] == '>' || str[*i + 1] == '<' || str[*i + 1] == '&' || str[*i + 1] == '(' || str[*i + 1] == ')' || str[*i + 1] == '`' || str[*i + 1] == '\0')
        {
            (*i)++;
            break ;
        }
        (*i)++;
    }
}

void     handle_brackets(char *str, int *index, int *flag, char **tmp2)
{
    int i;
    int j;

    i = *index;
    j = 0;
    while (str[i] && str[i] != '}')
    {
        i++;
        j++;
    }
    if (!str[i])
    {
        ft_exit(1, ft_strjoin(str + *index, " : syntax error\n"));
        return ;
    }
    i = *index + 1;
    *flag = fill_input(str, &i, tmp2, 1);
    while (str[*index] && str[*index] != '}')
        (*index)++;
    (*index)++;
}

void    expander(t_shell *shell)
{
    int i;
    int flag;
    int squotes;
	int dquotes;
    char *tmp2;


    flag = 0;
    squotes = 0;
	dquotes = 0;
    i = 0;
    tmp2 = NULL;
    while (shell->input[i])
    {
        if (shell->input[i] == '\'' && squotes == 0)
            squotes = 1;
        else if (shell->input[i] == '\'' && squotes == 1)
            squotes = 0;
		if (shell->input[i] == '\"' && dquotes == 0)
			dquotes = 1;
		else if (shell->input[i] == '\"' && dquotes == 1)
			dquotes = 0;
        if (shell->input[i] == '$' && (squotes == 0 || dquotes == 1) && shell->input[i + 1] != '\0' && shell->input[i + 1] != ' ')
        {
            if (shell->input[i + 1] == '{')
                handle_brackets(shell->input, &i, &flag, &tmp2);
            else
                expand_wo_brackets(shell->input, &i, &tmp2, &flag);
        }
        else
        {
            tmp2 = ft_strjoin(tmp2, ft_substr(shell->input, i, 1));
            i++;
        }
    }
    if (flag)
        shell->input = tmp2;
}

void	ft_lexer(t_shell *shell)
{
    // char    **mtx;
	int i;

	i = 0;
    expander(shell);
    // mtx = ft_split(shell->input, '|');
}