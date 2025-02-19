/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:26:52 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/08 17:13:49 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	question_mark_handler(char *str, int *index, char **tmp2, int brack_flag)
{
	if (str[*index + 1] == '?' && brack_flag == 0)
	{
		*tmp2 = ft_strjoin(*tmp2, ft_itoa(*exit_status()));
		(*index) += 2;
		return (1);
	}
	else if (brack_flag == 1)
	{
		if (str[*index + 2] == '?' && str[*index + 3] == 125)
		{
			*tmp2 = ft_strjoin(*tmp2, ft_itoa(*exit_status()));
			(*index) += 4;
			return (1);
		}
		else if (is_reserved_export(str[*index + 2]) || str[*index + 2] == ' '
			|| str[*index + 3] == ' ')
		{
			ft_error(1, "Minishell: ?: bad sostitution");
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
	if (i > 0 && (shell->input[i] == '\"' || shell->input[i] == '\''))
		i--;
	while (i >= 0 && shell->input[i] == ' ')
		i--;
	if (i > 0 && shell->input[i] == '<' && shell->input[i - 1] == '<')
		return (1);
	return (0);
}
