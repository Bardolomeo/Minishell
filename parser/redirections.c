/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:54:29 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/08 13:56:11 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	namefile_quotes(t_shell *shell, int *i, int j, int n_io)
{
	int	k;

	shell->input[*i] = ' ';
	(*i)++;
	k = 0;
	while (shell->input[*i] && shell->input[*i] != '\"')
	{
		shell->cmd_table[j].io[n_io][k] = shell->input[*i];
		shell->input[*i] = ' ';
		(*i)++;
		k++;
	}
	shell->cmd_table[j].io[n_io][k] = '\0';
}

void	namefile_no_quotes(t_shell *shell, int *tmp, int j, int n_io)
{
	int	k;

	k = 0;
	while (shell->input[*tmp] && shell->input[*tmp] != ' ')
	{
		shell->cmd_table[j].io[n_io][k] = shell->input[*tmp];
		shell->input[*tmp] = ' ';
		(*tmp)++;
		k++;
	}
	shell->cmd_table[j].io[n_io][k] = '\0';
}

int	redirect_append(t_shell *shell, int j, int *i)
{
	int	fd;
	int	k;
	int	tmp;

	tmp = *i;
	while (tmp < *i + 2)
		shell->input[tmp++] = ' ';
	while (shell->input[tmp] && shell->input[tmp] == ' ')
		tmp++;
	k = 0;
	if (shell->input[tmp] == '\"' || shell->input[tmp] == '\'')
		namefile_quotes(shell, &tmp, j, 2);
	else
		namefile_no_quotes(shell, &tmp, j, 2);
	fd = open(shell->cmd_table[j].io[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
	*i = tmp;
	shell->cmd_table[j].io[1][0] = '\0';
	if (fd >= 0)
		close(fd);
	else
		return (0);
	return (1);
}

int	redirect_input(t_shell *shell, int j, int *i)
{
	int	fd;

	shell->input[*i] = ' ';
	(*i)++;
	while (shell->input[*i] && shell->input[*i] == ' ')
		(*i)++;
	if (shell->input[*i] == '\"' || shell->input[*i] == '\'')
		namefile_quotes(shell, i, j, 0);
	else
		namefile_no_quotes(shell, i, j, 0);
	fd = open(shell->cmd_table[j].io[0], O_RDONLY);
	if (fd >= 0)
		close(fd);
	else
		return (0);
	return (1);
}

int	redirect_output(t_shell *shell, int *i, int j)
{
	int	fd;

	shell->input[*i] = ' ';
	(*i)++;
	while (shell->input[*i] && shell->input[*i] == ' ')
		(*i)++;
	if (shell->input[*i] == '\"' || shell->input[*i] == '\'')
		namefile_quotes(shell, i, j, 1);
	else
		namefile_no_quotes(shell, i, j, 1);
	fd = open(shell->cmd_table[j].io[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	shell->cmd_table[j].io[2][0] = '\0';
	if (fd >= 0)
		close(fd);
	else
		return (0);
	return (1);
}
