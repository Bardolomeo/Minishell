/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:42 by mtani             #+#    #+#             */
/*   Updated: 2024/04/15 10:32:14 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *shell, int i)
{
	int		j;
	int		n_flag;

	j = 1;
	n_flag = 0;
	if (shell->cmd_table[i].cmd.cmd_wargs[1] && !ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[1], "-n", 2))
	{
		n_flag = 1;
		i++;
	}
	while (shell->cmd_table[i].cmd.cmd_wargs[j])
	{
		ft_putstr_fd(shell->cmd_table[i].cmd.cmd_wargs[j], 1);
		if (shell->cmd_table[i].cmd.cmd_wargs[j + 1])
			ft_putchar_fd(' ', 1);
		j++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	g_exit_status = 0;
}
