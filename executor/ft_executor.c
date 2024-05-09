/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:54:23 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 16:33:48 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	reset_io(t_shell *shell)
{
	if (shell->cmd_table[0].io[1][0] != '\0')
		dup2(*fd_stand_out(), 1);
	if (shell->cmd_table[0].io[2][0] != '\0')
		dup2(*fd_stand_out(), 1);
	if (shell->cmd_table[0].io[0][0] != '\0')
		dup2(*fd_stand_in(), 0);
	return (0);
}

void	convert_special(t_shell *shell, int n_cmd)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < n_cmd)
	{
		j = 0;
		while (shell->cmd_table[i].cmd.cmd_wargs[j])
		{
			k = 0;
			while (shell->cmd_table[i].cmd.cmd_wargs[j][k])
			{
				if (shell->cmd_table[i].cmd.cmd_wargs[j][k] == -23)
					shell->cmd_table[i].cmd.cmd_wargs[j][k] = '<';
				if (shell->cmd_table[i].cmd.cmd_wargs[j][k] == -22)
					shell->cmd_table[i].cmd.cmd_wargs[j][k] = '>';
				if (shell->cmd_table[i].cmd.cmd_wargs[j][k] == -21)
					shell->cmd_table[i].cmd.cmd_wargs[j][k] = '|';
				k++;
			}
			j++;
		}
		i++;
	}
}

void	connect_pipe(int *fd, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		pipe(fd + i * 2);
		i++;
	}
}

void	update_exit_status(int *i, int *status)
{
	(*i)--;
	if (WIFEXITED(*status))
	{
		*exit_status() = WEXITSTATUS(*status);
	}
	if (g_signal == SIGINT)
		*exit_status() = 130;
	else if (g_signal == SIGQUIT)
		*exit_status() = 131;
}

void	ft_executor(t_shell *shell)
{
	t_exec_vars	vars;

	vars.i = -1;
	vars.status = 0;
	vars.fd = NULL;
	vars.cmd_count = count_cmds(shell);
	convert_special(shell, vars.cmd_count);
	check_exit(shell);
	if (!check_single_command(vars.cmd_count, &vars.fd, shell))
		return ;
	while (++vars.i < vars.cmd_count)
	{
		set_signals("command");
		shell->cmd_table[vars.i].pid = fork();
		if (shell->cmd_table[vars.i].pid == 0)
			execute_child(shell, vars.i, vars.fd, vars.cmd_count);
		else
			execute_parent(vars.cmd_count, vars.i, vars.fd);
	}
	while (vars.i > 0 && wait4(shell->cmd_table[vars.i - 1].pid, &vars.status,
			WUNTRACED, NULL) > 0)
		update_exit_status(&vars.i, &vars.status);
	reset_io(shell);
}
