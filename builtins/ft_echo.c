/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:42 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 16:02:08 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *shell, int i)
{
	int	j;
	int	n_flag;

	j = 1;
	n_flag = 0;
	if (shell->cmd_table[i].cmd.cmd_wargs[1]
		&& !ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[1], "-n", 3))
	{
		n_flag = 1;
		j++;
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
	*exit_status() = 0;
}
