/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:21:47 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 17:40:41 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_shell *shell, int i)
{
	if (shell->cmd_table[i].cmd.cmd_wargs[1] == NULL
		|| ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[1], "~", 1) == 0)
	{
		if (chdir(ft_getenv("HOME", 0)) != 0)
			perror(RED "minishell$ " WHITE);
	}
	else if (shell->cmd_table[i].cmd.cmd_wargs[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		*exit_status() = 1;
	}
	else
	{
		if (chdir(shell->cmd_table[i].cmd.cmd_wargs[1]) != 0)
		{
			*exit_status() = 1;
			perror(RED "minishell$ " WHITE);
		}
	}
}
