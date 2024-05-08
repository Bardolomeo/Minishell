/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:39:18 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/08 14:00:06 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_signal_exit(int fd)
{
	close(fd);
	clear_garbage_no_unlink();
	exit(1);
}

int	heredoc_input_setter(t_shell *shell, char *limiter, int j, int k)
{
	char	*line;

	limiter[k] = '\0';
	if (limiter[0] == 0)
	{
		printf("Minishell: syntax error near `<`\n");
		return (0);
	}
	if (!create_heredoc(limiter, n_doc()))
	{
		return (0);
	}
	line = ft_strjoin("./tmp/heredoc", ft_itoa(*n_doc() - 1));
	k = 0;
	while (line[k])
	{
		shell->cmd_table[j].io[0][k] = line[k];
		k++;
	}
	shell->cmd_table[j].io[0][k] = '\0';
	return (1);
}

int	red_doc_loop_no_quotes(t_shell *shell, int *tmp, char *quotes)
{
	if ((shell->input[*tmp] == '"' || shell->input[*tmp] == '\''))
	{
		if (*quotes == 0)
		{
			*quotes = shell->input[*tmp];
			shell->input[*tmp] = ' ';
			(*tmp)++;
			return (1);
		}
		else if (*quotes == shell->input[*tmp])
		{
			*quotes = 0;
			shell->input[*tmp] = ' ';
			return (0);
		}
	}
	if ((shell->input[*tmp + 1] == ' ' || shell->input[*tmp + 1] == '\0')
		&& (*quotes == 0))
	{
		shell->input[*tmp] = ' ';
		return (0);
	}
	return (1);
}

int	redirect_heredoc_loop(t_shell *shell, int *tmp, int *k, char *limiter)
{
	char	quote;

	quote = 0;
	while (shell->input[*tmp] && (shell->input[*tmp] != ' ' || quote != 0))
	{
		if (shell->input[*tmp] == '>' || shell->input[*tmp] == '<'
			|| shell->input[*tmp] == '|')
		{
			printf("Minishell: syntax error near `%c`\n", shell->input[*tmp]);
			return (0);
		}
		if (!red_doc_loop_no_quotes(shell, tmp, &quote))
			break ;
		limiter[*k] = shell->input[*tmp];
		shell->input[*tmp] = ' ';
		(*k)++;
		(*tmp)++;
	}
	return (1);
}

int	redirect_heredoc(t_shell *shell, int j, int *i)
{
	char	*limiter;
	char	*line;
	int		k;
	int		tmp;

	line = NULL;
	limiter = ft_malloc(sizeof(char) * 100);
	tmp = *i;
	while (tmp < *i + 2)
		shell->input[tmp++] = ' ';
	while (shell->input[tmp] && shell->input[tmp] == ' ')
		tmp++;
	k = 0;
	if (!redirect_heredoc_loop(shell, &tmp, &k, limiter))
		return (0);
	if (!heredoc_input_setter(shell, limiter, j, k))
		return (0);
	*i = tmp;
	return (1);
}
