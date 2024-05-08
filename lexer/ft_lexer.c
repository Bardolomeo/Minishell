/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 16:49:55 by mtani             #+#    #+#             */
/*   Updated: 2024/05/08 15:12:58 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_env_loop(char *str, int bra_flag, int *len)
{
	if (bra_flag == 0)
	{
		while (str[*len] && str[*len] != ' ' && str[*len] != '$'
			&& !is_reserved_export(str[*len]) && str[*len] != '\0'
			&& str[*len] != '\"' && str[*len] != '\'' && str[*len] != '=')
			(*len)++;
	}
	else
	{
		while (str[*len] && str[*len] != '}')
			(*len)++;
	}
}

char	*ft_getenv(char *str, int bra_flag)
{
	int		i;
	int		len;
	t_str	*myenv;

	myenv = *ft_myenv();
	len = 0;
	i = -1;
	while (myenv[++i] && *str != '\"' && *str != '\''
		&& !is_reserved_export(*str) && *str != '\0' && *str != ' '
		&& *str != '=')
	{
		get_env_loop(str, bra_flag, &len);
		if (ft_strncmp(myenv[i], str, len) == 0 && myenv[i][len] == '=')
			return (ft_strchr(myenv[i], '=') + 1);
	}
	return (NULL);
}

int	fill_input(char *str, int *i, char **tmp2, int bra_flag)
{
	char	*tmp;
	char	*tmpenv;

	tmp = NULL;
	tmpenv = ft_getenv(str + *i + 1, bra_flag);
	if (tmpenv)
	{
		if (*tmp2 == NULL)
		{
			tmp = ft_substr(str, 0, *i);
			*tmp2 = ft_strjoin(tmp, ft_getenv(str + *i + 1, bra_flag));
		}
		else
			*tmp2 = ft_strjoin(*tmp2, ft_getenv(str + *i + 1, bra_flag));
	}
	return (1);
}

int	expand_wo_brackets(char *str, int *i, char **tmp2, int *bra_flag)
{
	int	quest_res;

	quest_res = question_mark_handler(str, i, tmp2, 0);
	if (quest_res == 1)
		return (1);
	if (quest_res == 2)
		return (0);
	*bra_flag = fill_input(str, i, tmp2, 0);
	while (str[*i] && str[*i] != ' ')
	{
		if (str[*i + 1] == '$' || str[*i + 1] == '\'' || str[*i + 1] == '\"'
			|| is_reserved_export(str[*i + 1]) || str[*i + 1] == '\0' || str[*i
				+ 1] == ' ' || str[*i + 1] == '=')
		{
			(*i)++;
			break ;
		}
		(*i)++;
	}
	return (1);
}

int	find_end_bracket(char *str, int *i, int *j, int *index)
{
	while (str[*i] && str[*i] != 125)
	{
		(*i)++;
		(*j)++;
	}
	if (!str[*i])
	{
		ft_error(1, ft_strjoin(str + *index, " : syntax error"));
		return (0);
	}
	return (1);
}

int	handle_brackets(char *str, int *index, int *bra_flag, char **tmp2)
{
	int	i;
	int	j;
	int	quest_res;

	i = *index;
	j = 0;
	if (!find_end_bracket(str, &i, &j, index))
		return (0);
	i = *index + 1;
	quest_res = question_mark_handler(str, index, tmp2, 1);
	if (quest_res == 1)
		return (1);
	if (quest_res == 2)
		return (0);
	*bra_flag = fill_input(str, &i, tmp2, 1);
	while (str[*index] && str[*index] != 125)
		(*index)++;
	(*index)++;
	return (1);
}

int	long_ass_condition(t_shell *shell, int *quotes, int i)
{
	if (shell->input[i] == '$' && (quotes[0] == 0 || quotes[1] == 1)
			&& shell->input[i + 1] != '\0' && shell->input[i + 1] != ' '
			&& shell->input[i + 1] != '$' && shell->input[i + 1] != '\t'
			&& !is_reserved_export(shell->input[i + 1]) && shell->input[i
			+ 1] != '\"' && shell->input[i + 1] != '\'')
		return (1);
	return (0);
}

void	expander(t_shell *shell)
{
	int		i;
	int		bra_flag;
	int		quotes[2];
	char	*tmp2;

	int f_break ;
	bra_flag = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	f_break = 1;
	i = 0;
	tmp2 = NULL;
	while (shell->input[i])
	{
		handle_quotes(shell, i, quotes);
		if (long_ass_condition(shell, quotes, i))
		{
			if (redirect_no_expand(shell, i) == 1)
			{
				tmp2 = ft_strjoin(tmp2, ft_substr(shell->input, i, 1));
				i++;
				continue ;
			}
			if (shell->input[i + 1] == 123)
				f_break = handle_brackets(shell->input, &i, &bra_flag, &tmp2);
			else
				f_break = expand_wo_brackets(shell->input, &i, &tmp2,
						&bra_flag);
		}
		else
		{
			tmp2 = ft_strjoin(tmp2, ft_substr(shell->input, i, 1));
			i++;
		}
		if (f_break == 0)
		{
			shell->input = NULL;
			return ;
		}
	}
	shell->input = tmp2;
}

void	ft_lexer(t_shell *shell)
{
	expander(shell);
	if (shell->input != NULL)
		shell->args = ft_altsplit(shell->input, ' ');
}
