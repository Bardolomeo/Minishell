/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:26:52 by gsapio            #+#    #+#             */
/*   Updated: 2024/04/10 18:38:30 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	question_mark_handler(char *str, int *index, char **tmp2, int brack_flag)
{
	char *str_exit_st;

	if (str[*index + 1] == '?' && brack_flag == 0)
	{
		printf("%s\n", ft_itoa(g_exit_status));
		str_exit_st = ft_itoa(g_exit_status);
		*tmp2 = ft_strjoin(*tmp2, str_exit_st);
		(*index) += 2;
		return (1);
	}
	else if (brack_flag == 1)
	{
		if (str[*index + 2] == '?' && str[*index + 3] == '}')
		{
			str_exit_st = ft_itoa(g_exit_status);
			*tmp2 = ft_strjoin(*tmp2, str_exit_st);
			(*index) += 4;
			return (1);
		}
		else
		{
			ft_exit(1, "minishell: ? : bad sostitution");
		}
	}
	return (0);
}

int	is_reserved(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|' || ch == '=')
		return (1);
	return (0);
}
