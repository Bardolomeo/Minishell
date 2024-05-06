/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:24:42 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/06 13:30:06 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sighandle_interactive(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		*exit_status() = 130;
	}
}

void	sighandle_command(int signal)
{
	if (signal == SIGINT)
	{
		g_signal = SIGINT;
		write(1, "\n", 1);
	}
	else if (signal == SIGQUIT)
	{
		g_signal = SIGQUIT;
		write(1, "Quit (core dumped)\n", 20);
	}
}

void	sighandle_heredoc(int signal)
{
	if (signal == SIGINT)
	{
		clear_garbage();
		write(1, "\n", 1);
		exit(0);
	}
}

void	set_signals(const char *flag)
{
	if (ft_strncmp(flag, "interactive", ft_strlen(flag) + 1) == 0)
	{
		signal(SIGINT, sighandle_interactive);
		signal(SIGQUIT, SIG_IGN);
	}
	if (ft_strncmp(flag, "command", ft_strlen(flag) + 1) == 0)
	{
		signal(SIGINT, sighandle_command);
		signal(SIGQUIT, sighandle_command);
	}
	if (ft_strncmp(flag, "heredoc", ft_strlen(flag) + 1) == 0)
	{
		signal(SIGINT, sighandle_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (ft_strncmp(flag, "ignore", ft_strlen(flag) + 1) == 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}
