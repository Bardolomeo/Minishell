/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:54:23 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 15:55:14 by mtani            ###   ########.fr       */
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

int	check_builtins(t_shell *shell, int i, char *pflag)
{
	if (!shell->cmd_table[i].cmd.cmd_wargs[0])
		return (1);
	if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0], "pwd", 4) == 0)
		ft_pwd(shell, i);
	else if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0], "cd", 3) == 0)
		ft_cd(shell, i);
	else if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0], "echo", 5) == 0)
		ft_echo(shell, i);
	else if (ft_strncmp(shell->cmd_table[i].cmd.cmd_wargs[0],
			"export", 7) == 0)
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

char	*get_valid_path(t_shell *shell, int i)
{
	t_gpv_vars	vars;

	vars.j = 0;
	vars.k = -1;
	vars.env = *shell->my_env;
	if (shell->cmd_table[i].cmd.cmd_wargs[0][0] == '/'
		|| shell->cmd_table[i].cmd.cmd_wargs[0][0] == '.')
		return (shell->cmd_table[i].cmd.cmd_wargs[0]);
	while (vars.env[vars.j] != NULL)
	{
		if (ft_strncmp(vars.env[vars.j], "PATH=", 5) == 0)
		{
			vars.paths = ft_split(vars.env[vars.j] + 5, ':');
			while (vars.paths[++vars.k] != NULL)
			{
				vars.path = ft_strjoin(vars.paths[vars.k], "/");
				vars.path = ft_strjoin(vars.path,
						shell->cmd_table[i].cmd.cmd_wargs[0]);
				if (access(vars.path, F_OK) == 0)
					return (vars.path);
			}
		}
		vars.j++;
	}
	return (NULL);
}

int	check_exit_args(t_shell *shell)
{
	int	i;
	int	is_neg;

	i = 0;
	if (!shell->cmd_table->cmd.cmd_wargs[1])
		return (1);
	if (shell->cmd_table->cmd.cmd_wargs[1][0] == '-')
		is_neg = 1;
	if (shell->cmd_table->cmd.cmd_wargs[1][0] == '-')
		i++;
	while (shell->cmd_table->cmd.cmd_wargs[1][i])
	{
		if (!ft_isdigit(shell->cmd_table->cmd.cmd_wargs[1][i]))
			return (0);
		i++;
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
		}
		else
		{
			if (!check_exit_args(shell))
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(shell->cmd_table->cmd.cmd_wargs[1], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				*exit_status() = 2;
				clear_garbage();
				exit(*exit_status());
			}
			if (shell->cmd_table->cmd.cmd_wargs[1])
				*exit_status() = ft_atoi(shell->cmd_table->cmd.cmd_wargs[1]);
			clear_garbage();
			exit(*exit_status());
		}
	}
}

void	init_first_pipe(int *fd, int i)
{
	dup2(fd[i * 2 + 1], 1);
	close(fd[i * 2 + 1]);
}

void	init_last_pipe(int *fd, int i)
{
	dup2(fd[(i - 1) * 2], 0);
	close(fd[(i - 1) * 2]);
}

void	init_mid_pipe(int *fd, int i)
{
	dup2(fd[(i - 1) * 2], 0);
	close(fd[(i - 1) * 2]);
	dup2(fd[i * 2 + 1], 1);
	close(fd[i * 2 + 1]);
}

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

void	execute_child(t_shell *shell, int i, int *fd, int cmd_count)
{
	if (!set_dup2(shell, i, fd, cmd_count))
		return ;
	if (check_builtins(shell, i, "inpipe"))
	{
		clear_garbage();
		exit(errno);
	}
	shell->cmd_table[i].cmd.path = get_valid_path(shell, i);
	if (shell->cmd_table[i].cmd.path == NULL)
	{
		ft_error(127, "Minishell: command not found");
		clear_garbage();
		exit(127);
	}
	execve(shell->cmd_table[i].cmd.path, shell->cmd_table[i].cmd.cmd_wargs,
		*shell->my_env);
	ft_error(errno, NULL);
	clear_garbage();
	exit(errno);
}

void	execute_parent(int cmd_count, int i, int *fd)
{
	if (cmd_count > 1)
	{
		if (i == 0)
			close(fd[1]);
		else if (i == cmd_count - 1)
			close(fd[(i - 1) * 2]);
		else
		{
			close(fd[(i - 1) * 2]);
			close(fd[i * 2 + 1]);
		}
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

void	ft_executor(t_shell *shell)
{
	int	cmd_count;
	int	status;
	int	*fd;
	int	i;

	i = -1;
	status = 0;
	fd = NULL;
	cmd_count = count_cmds(shell);
	convert_special(shell, cmd_count);
	check_exit(shell);
	if (!check_single_command(cmd_count, &fd, shell))
		return ;
	while (++i < cmd_count)
	{
		set_signals("command");
		shell->cmd_table[i].pid = fork();
		if (shell->cmd_table[i].pid == 0)
			execute_child(shell, i, fd, cmd_count);
		else
			execute_parent(cmd_count, i, fd);
	}
	while (i > 0 && wait4(shell->cmd_table[i - 1].pid, &status, WUNTRACED,
			NULL) > 0)
		update_exit_status(&i, &status);
	reset_io(shell);
}
