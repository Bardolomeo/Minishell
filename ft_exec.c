/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:38:12 by mtani             #+#    #+#             */
/*   Updated: 2024/04/12 12:03:58 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(shell->args[0], shell->args, *(shell->my_env)) == -1)
		{
			ft_putstr_fd(RED "minishell$ " WHITE, 2);
			perror(shell->args[0]);
			clear_garbage();
			exit(127);
		}
		clear_garbage();
		exit(0);
	}
	else if (pid < 0)
		perror(RED "minishell$ " WHITE);
	else
	{
		wait4(pid, &status, WUNTRACED, NULL);
		if (WIFEXITED(status))
		{
			g_exit_status = WEXITSTATUS(status);
		}
	}
}
