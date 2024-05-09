/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:21:47 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 16:01:41 by gsapio           ###   ########.fr       */
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
	}
	else
	{
		if (chdir(shell->cmd_table[i].cmd.cmd_wargs[1]) != 0)
			perror(RED "minishell$ " WHITE);
	}
}
