/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:08:20 by mtani             #+#    #+#             */
/*   Updated: 2024/04/18 17:27:18 by mtani            ###   ########.fr       */
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
int	create_heredoc(char *limiter, char *line, int *n_doc)
{
	int		fd;
	char	*fname;

	fname = ft_strjoin("./tmp/heredoc", ft_itoa(*n_doc));
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	(*n_doc)++;
	line = ft_readline(">");
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = ft_readline(">");
	}
	close(fd);
	return (0);
}

int		count_cmds(t_shell *shell)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (shell->args && shell->args[i])
	{
		if (ft_strncmp(shell->args[i], "|", 1) == 0)
			count++;
		i++;
	}
	return (count + 1);
}

void	print_singlecommands(char **singlecommands)
{
	int	i;

	i = 0;
	while (singlecommands[i])
	{
		printf("singlecommands[%d]: %s\n", i, singlecommands[i]);
		i++;
	}
}

void	make_cmd_table(t_shell *shell)
{
	char	**singlecommands;
	int		cmd_count;
	int 	i;

	i = 0;
	singlecommands = NULL;
	cmd_count = count_cmds(shell);
	if (shell->input)
		singlecommands = ft_split(shell->input, '|');
	while (i < cmd_count)
	{
		if (singlecommands)
		{
			singlecommands[i] = ft_strtrim(singlecommands[i], " ");
			shell->cmd_table[i].cmd.cmd_wargs = ft_altsplit(singlecommands[i], ' ');
		}
		i++;
	}
}

void	redirect_heredoc(t_shell *shell, int j, int *i)
{
	char		*limiter;
	char		*line;
	int			k;
	int			tmp;
	int			quote;

	quote = 0;
	line = NULL;
	limiter = ft_malloc(sizeof(char) * 100);
	tmp = *i;
	while (tmp < *i + 2)
		shell->input[tmp++] = ' ';
	while (shell->input[tmp] && shell->input[tmp] == ' ')
		tmp++;
	k = 0;
	while (shell->input[tmp] && (shell->input[tmp] != ' ' || quote == 1))
	{
		if (shell->input[tmp] == '>' || shell->input[tmp] == '<') // TODO: implementare errore
			break;
		if (k == 0 && (shell->input[tmp] == '"' || shell->input[tmp] == '\''))
		{
			shell->input[tmp] = ' ';
			tmp++;
			quote = 1;
			continue;
		}
		if ((shell->input[tmp + 1] == ' ' || shell->input[tmp + 1] == '\0')
			&& (shell->input[tmp] == '"' || shell->input[tmp] == '\''))
			{
				shell->input[tmp] = ' ';
				break;
			}
		limiter[k] = shell->input[tmp];
		shell->input[tmp] = ' ';
		tmp++;
		k++;
	}
	limiter[k] = '\0';
	if (create_heredoc(limiter, line, n_doc()) == 1)
		return ;
	line = ft_strjoin("./tmp/heredoc", ft_itoa(*n_doc() - 1));
	k = 0;
	while (line[k])
	{
		shell->cmd_table[j].io[0][k] = line[k];
		k++;
	}
	shell->cmd_table[j].io[0][k] = '\0';
	*i = tmp;
}

int	redirect_append(t_shell *shell, int j, int *i)
{
	int		fd;
	int		k;
	int		tmp;

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
	int fd;

	shell->input[*i] = ' ';
	(*i)++;								// poi apriamo il file in sola lettura e controlliamo se esiste
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
	int fd;

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

void	initialize_cmd_table(t_shell *shell, int cmd_count)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < cmd_count)
	{
		shell->cmd_table[i].cmd.cmd_wargs = NULL;
		shell->cmd_table[i].io[0][0] = '\0';
		shell->cmd_table[i].io[1][0] = '\0';
		shell->cmd_table[i].io[2][0] = '\0';
		i++;
	}
}

void	set_redirects(t_shell *shell)
{
	int		cmd_count;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd_count = count_cmds(shell);
	shell->cmd_table = NULL;
	shell->cmd_table = ft_malloc(sizeof(t_cmd) * (cmd_count + 1));
	initialize_cmd_table(shell, cmd_count);
	while (shell->input && shell->input[i])
	{
		if (shell->input[i] == '<' && shell->input[i + 1] != '<')
		{
			if (!redirect_input(shell, j, &i))
				return ;
		}
		else if (shell->input[i] == '<' && shell->input[i + 1] == '<')
			redirect_heredoc(shell, j, &i);
		else if (shell->input[i] == '>' && shell->input[i + 1] == '>')
		{
			if (!redirect_append(shell, j, &i))
				return ;
		}
		else if (shell->input[i] == '>' && shell->input[i + 1] != '>')
		{
			if (!redirect_output(shell, &i, j))
				return ;
		}
		if (shell->input[i] && shell->input[i] == '|')
			j++;
		if (shell->input[i])
			i++;
	}
}

void	print_cmd_table(t_shell *shell)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (shell->cmd_table[i].cmd.cmd_wargs)
	{
		j = 0;
		while (shell->cmd_table[i].cmd.cmd_wargs[j])
		{
			printf("cmd_table[%d].cmd.cmd_wargs[%d]: %s\n", i, j, shell->cmd_table[i].cmd.cmd_wargs[j]);
			j++;
		}
		i++;
	}
}

void	ft_parser(t_shell *shell)
{
	set_redirects(shell);
	make_cmd_table(shell);
	//print_cmd_table(shell);
	// printf("cmd_table[0].io[0]: %s\n", shell->cmd_table[0].io[0]);
	// printf("cmd_table[0].io[1]: %s\n", shell->cmd_table[0].io[1]);
	// printf("cmd_table[1].io[1]: %s\n", shell->cmd_table[1].io[1]);
	// printf("cmd_table[1].io[0]: %s\n", shell->cmd_table[1].io[0]);
}
