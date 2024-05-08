/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_brackets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:55:46 by mtani             #+#    #+#             */
/*   Updated: 2024/05/08 17:12:25 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	init_expander(t_exp_vars *vars)
{
	vars->bra_flag = 0;
	vars->quotes[0] = 0;
	vars->quotes[1] = 0;
	vars->f_break = 1;
	vars->i = 0;
	vars->tmp2 = NULL;
}
