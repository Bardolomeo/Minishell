/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:45:59 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/08 13:59:43 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_heredoc_parent(int pid, int *status, int fd)
{
	int	ex_status;

	set_signals("ignore");
	wait4(pid, status, WUNTRACED, NULL);
	set_signals("command");
	if (WIFEXITED(*status))
	{
		ex_status = WEXITSTATUS(*status);
		close(fd);
		if (ex_status == 0)
		{
			*exit_status() = 130;
			return (0);
		}
		return (1);
	}
	*exit_status() = errno;
	return (0);
}

void	create_heredoc_child(char *limiter, int fd)
{
	char	*line;

	set_signals("heredoc");
	line = ft_readline(">", 1);
	if (line == NULL)
		heredoc_signal_exit(fd);
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = ft_readline(">", 1);
		if (line == NULL)
			heredoc_signal_exit(fd);
	}
	close(fd);
	clear_garbage_no_unlink();
	exit(1);
}

int	create_heredoc(char *limiter, int *n_doc)
{
	int		fd;
	char	*fname;
	int		pid;
	int		status;

	fname = ft_strjoin("./tmp/heredoc", ft_itoa(*n_doc));
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	(*n_doc)++;
	pid = fork();
	if (pid == 0)
		create_heredoc_child(limiter, fd);
	else
	{
		return (create_heredoc_parent(pid, &status, fd));
	}
	return (0);
}
