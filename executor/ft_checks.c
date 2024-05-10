/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:27:51 by mtani             #+#    #+#             */
/*   Updated: 2024/05/10 15:51:08 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sign_check(t_shell *shell, int *is_neg, int *i)
{
	if (shell->cmd_table->cmd.cmd_wargs[1][0] == '-')
		*is_neg = 1;
	if (shell->cmd_table->cmd.cmd_wargs[1][0] == '-'
		|| shell->cmd_table->cmd.cmd_wargs[1][0] == '+')
		(*i)++;
}

int	check_exit_args(t_shell *shell)
{
	int	i;
	int	is_neg;

	i = -1;
	is_neg = 0;
	if (!shell->cmd_table->cmd.cmd_wargs[1])
		return (1);
	sign_check(shell, &is_neg, &i);
	while (shell->cmd_table->cmd.cmd_wargs[1][++i])
	{
		if (!ft_isdigit(shell->cmd_table->cmd.cmd_wargs[1][i]))
			return (0);
	}
	if (is_neg)
		i--;
	if (i >= 18)
	{
		if (ft_strncmp(shell->cmd_table->cmd.cmd_wargs[1],
				"9223372036854775807", 20) > 0)
			return (0);
	}
	return (1);
}

void	check_exit(t_shell *shell)
{
	if (shell->cmd_table->cmd.cmd_wargs[0]
		&& ft_strncmp(shell->cmd_table->cmd.cmd_wargs[0], "exit", 4) == 0)
	{
		if (shell->cmd_table->cmd.cmd_wargs[1]
			&& shell->cmd_table->cmd.cmd_wargs[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			*exit_status() = 1;
			clean_exit();
		}
		else
		{
			if (!check_exit_args(shell))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(shell->cmd_table->cmd.cmd_wargs[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				*exit_status() = 2;
				clean_exit();
			}
			if (shell->cmd_table->cmd.cmd_wargs[1])
				*exit_status() = ft_atoi(shell->cmd_table->cmd.cmd_wargs[1]);
			clean_exit();
		}
	}
}

int	check_single_command(int cmd_count, int **fd, t_shell *shell)
{
	if (cmd_count > 1)
	{
		*fd = (int *)ft_malloc(sizeof(int) * ((cmd_count - 1) * 2));
		connect_pipe(*fd, cmd_count);
	}
	else if (cmd_count == 1)
	{
		if (!set_dup2(shell, 0, NULL, cmd_count))
			return (0);
		if (check_builtins(shell, 0, "outpipe"))
			return (reset_io(shell));
	}
	return (1);
}

int	check_builtins(t_shell *shell, int i, char *pflag)
{
	if (!shell->cmd_table[i].cmd.cmd_wargs[0])
		return (1);
	if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0], "cd", 3) == 0)
		ft_cd(shell, i);
	else if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0], "echo", 5) == 0)
		ft_echo(shell, i);
	else if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0], "export", 7) == 0)
		ft_export(shell, i, pflag);
	else if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0], "unset", 6) == 0)
		ft_unset(shell, i);
	else if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0], "env", 4) == 0)
		ft_env(shell, i);
	else
		return (0);
	if (ft_strncmp(pflag, "inpipe", 6) == 0)
		clear_garbage();
	return (1);
}
