/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:08:20 by mtani             #+#    #+#             */
/*   Updated: 2024/05/08 14:01:18 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(t_shell *shell)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (shell->args && shell->args[i])
	{
		if (ft_strncmp(shell->args[i], "|", 1) == 0)
			if (shell->args[i + 1] != NULL)
				count++;
		i++;
	}
	return (count + 1);
}

void	make_cmd_table(t_shell *shell)
{
	char	**singlecommands;
	int		cmd_count;
	int		i;

	i = 0;
	singlecommands = NULL;
	cmd_count = count_cmds(shell);
	if (shell->input)
		singlecommands = ft_split(shell->input, '|');
	while (i < cmd_count)
	{
		if (singlecommands)
		{
			if (singlecommands[i])
			{
				singlecommands[i] = ft_strtrim(singlecommands[i], " ");
				shell->cmd_table[i].cmd.cmd_wargs = ft_altsplit(
						singlecommands[i], ' ');
			}
		}
		i++;
	}
}

int	set_redirects_loop(t_shell *shell, int *i, int j)
{
	if (shell->input[*i] == '<' && shell->input[*i + 1] != '<')
	{
		if (!redirect_input(shell, j, i))
			return (0);
	}
	else if (shell->input[*i] == '<' && shell->input[*i + 1] == '<')
	{
		if (!redirect_heredoc(shell, j, i))
			return (0);
	}
	else if (shell->input[*i] == '>' && shell->input[*i + 1] == '>')
	{
		if (!redirect_append(shell, j, i))
			return (0);
	}
	else if (shell->input[*i] == '>' && shell->input[*i + 1] != '>')
	{
		if (!redirect_output(shell, i, j))
			return (0);
	}
	return (1);
}

int	set_redirects(t_shell *shell)
{
	int	cmd_count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	cmd_count = count_cmds(shell);
	shell->cmd_table = NULL;
	shell->cmd_table = ft_malloc(sizeof(t_cmd) * (cmd_count + 1));
	initialize_cmd_table(shell, cmd_count);
	while (shell->input && shell->input[i])
	{
		if (!set_redirects_loop(shell, &i, j))
			return (0);
		if (shell->input[i] && shell->input[i] == '|')
			j++;
		if (shell->input[i])
			i++;
	}
	return (1);
}

int	ft_parser(t_shell *shell)
{
	if (!set_redirects(shell))
	{
		return (0);
	}
	make_cmd_table(shell);
	return (1);
}
