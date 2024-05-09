/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:24:59 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 16:25:33 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	dup2_input(t_shell *shell, int i, int cmd_count, int *fd)
{
	int	fd_redir_in;

	if (shell->cmd_table[i].io[0][0] != '\0')
	{
		fd_redir_in = open(shell->cmd_table[i].io[0], O_RDONLY);
		if (fd_redir_in < 0)
		{
			ft_error(errno, NULL);
			if (cmd_count > 1)
			{
				clear_garbage();
				exit(errno);
			}
			return (0);
		}
		dup2(fd_redir_in, 0);
		close(fd_redir_in);
		if (i == 0 && cmd_count > 1)
			close(fd[0]);
		else if (cmd_count > 1)
			close(fd[(i - 1) * 2]);
	}
	return (1);
}

int	dup2_output(t_shell *shell, int i, int cmd_count, int *fd)
{
	int	fd_redir_out;

	if (shell->cmd_table[i].io[1][0] != '\0')
	{
		fd_redir_out = open(shell->cmd_table[i].io[1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd_redir_out < 0)
		{
			ft_error(errno, NULL);
			if (cmd_count > 1)
			{
				clear_garbage();
				exit(errno);
			}
			return (0);
		}
		dup2(fd_redir_out, 1);
		close(fd_redir_out);
		if (i == cmd_count - 1 && cmd_count > 1)
			close(fd[(i - 1) * 2]);
		else if (cmd_count > 1)
			close(fd[i * 2 + 1]);
	}
	return (1);
}

int	dup2_append(t_shell *shell, int i, int cmd_count, int *fd)
{
	int	fd_redir_out;

	if (shell->cmd_table[i].io[2][0] != '\0')
	{
		fd_redir_out = open(shell->cmd_table[i].io[2],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd_redir_out < 0)
		{
			ft_error(errno, NULL);
			if (cmd_count > 1)
			{
				clear_garbage();
				exit(errno);
			}
			return (0);
		}
		dup2(fd_redir_out, 1);
		close(fd_redir_out);
		if (i == cmd_count - 1 && cmd_count > 1)
			close(fd[(i - 1) * 2]);
		else if (cmd_count > 1)
			close(fd[i * 2 + 1]);
	}
	return (1);
}

int	redir_dup2(t_shell *shell, int i, int cmd_count, int *fd)
{
	*fd_stand_in() = dup(0);
	*fd_stand_out() = dup(1);
	if (!dup2_input(shell, i, cmd_count, fd))
		return (0);
	if (!dup2_output(shell, i, cmd_count, fd))
		return (0);
	if (!dup2_append(shell, i, cmd_count, fd))
		return (0);
	return (1);
}

int	set_dup2(t_shell *shell, int i, int *fd, int cmd_count)
{
	if (cmd_count == 1)
	{
		if (!redir_dup2(shell, i, cmd_count, fd))
			return (0);
		return (1);
	}
	if (i == 0)
		init_first_pipe(fd, i);
	else if (i == cmd_count - 1)
		init_last_pipe(fd, i);
	else
		init_mid_pipe(fd, i);
	if (!redir_dup2(shell, i, cmd_count, fd))
		return (0);
	return (1);
}
