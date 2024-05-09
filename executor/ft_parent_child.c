/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parent_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:33:53 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 16:34:01 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
