/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:26:52 by gsapio            #+#    #+#             */
/*   Updated: 2024/04/06 16:00:42 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	question_mark_handler(char *str, int *index, char **tmp2, int brack_flag)
{
	char *str_exit_st;

	if (str[*index + 1] == '?' && brack_flag == 0)
	{
		str_exit_st = ft_itoa(g_exit_status);
		*tmp2 = ft_strjoin(*tmp2, str_exit_st);
		(*index) += 2;
	}
	else if (str[*index + 1] == '?' && brack_flag == 1)
	{
		if (str[*index + 2] == '}')
		{
			*tmp2 = ft_strjoin(*tmp2, ft_itoa(g_exit_status));
			(*index) += 2;
		}
	}
}

int	is_reserved(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|')
		return (1);
	return (0);
}
