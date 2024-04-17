/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:26:52 by gsapio            #+#    #+#             */
/*   Updated: 2024/04/17 13:40:18 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	question_mark_handler(char *str, int *index, char **tmp2, int brack_flag)
{
	char *str_exit_st;

	if (str[*index + 1] == '?' && brack_flag == 0)
	{
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
		else if (is_reserved_export(str[*index + 2]) || str[*index + 2] == ' ' || str[*index + 3] == ' ')
		{
			ft_putstr_fd("minishell ? : bad sostitution\n", 2);
			g_exit_status = 1;
			return (2);
		}
	}
	return (0);
}

void	handle_quotes(t_shell *shell, int i, int *quotes)
{
	if (shell->input[i] == '\'' && quotes[0] == 0 && quotes[1] == 0)
		quotes[0] = 1;
	else if (shell->input[i] == '\'' && quotes[0] == 1)
		quotes[0] = 0;
	if (shell->input[i] == '\"' && quotes[1] == 0 && quotes[0] == 0)
		quotes[1] = 1;
	else if (shell->input[i] == '\"' && quotes[1] == 1)
		quotes[1] = 0;
}

int	redirect_no_expand(t_shell *shell, int i)
{
	if (i > 0)
		i--;
	while (i >= 0 && shell->input[i] == ' ')
		i--;
	if (shell->input[i] == '<' || shell->input[i] == '>')
	{
		if (i - 1 >= 0 && shell->input[i - 1] == '<' && shell->input[i] == '<')
			return (2);
		ft_error(1, "minishell: ambiguos redirect \n");
		return (1);
	}
	return (0);
}
