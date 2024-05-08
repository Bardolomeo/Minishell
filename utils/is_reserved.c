/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reserved.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:11:13 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/08 13:58:25 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_reserved_export(char ch)
{
	if (ch == '>' || ch == '<' || ch == '|'
		|| ch == '(' || ch == ')' || ch == '`')
		return (1);
	return (0);
}

void	initialize_cmd_table(t_shell *shell, int cmd_count)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd_count)
	{
		shell->cmd_table[i].cmd.cmd_wargs = NULL;
		shell->cmd_table[i].io[0][0] = '\0';
		shell->cmd_table[i].io[1][0] = '\0';
		shell->cmd_table[i].io[2][0] = '\0';
		i++;
	}
}
