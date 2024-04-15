/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:08:20 by mtani             #+#    #+#             */
/*   Updated: 2024/04/15 14:48:14 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	create_heredoc(char *limiter, char *line, int *n_doc)
{
	int		fd;
	char	*fname;

	fname = ft_strjoin("./.tmp/heredoc", ft_itoa(*n_doc));
	fd = open(fname, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_error(1, "minishell: no such file or directory");
		return (1);
	}
	(*n_doc)++;
	line = ft_readline(">"); // leggiamo prima riga del file
	while (ft_strncmp(line, limiter, ft_strlen(limiter)) != 0) // finchè la riga non è uguale al limiter
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		line = ft_readline(">"); // leggiamo la riga successiva
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
	while (shell->args[i])
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
	cmd_count = count_cmds(shell);
	singlecommands = ft_split(shell->input, '|');
	while (i < cmd_count)
	{
		shell->cmd_table[i].cmd.cmd_wargs = ft_altsplit(singlecommands[i], ' ');
		//printf("cmd_table[%d].cmd.cmd_wargs: %s\n", i, shell->cmd_table[i].cmd.cmd_wargs[1]);
		i++;
	}
}

void	redirect_heredoc(t_shell *shell, int j, int *i)
{
	char		*limiter;
	char		*line;
	int			k;
	int			tmp;
	
	line = NULL;
	limiter = ft_malloc(sizeof(char) * 100);
	tmp = *i;
	tmp += 2;
	while (shell->input[tmp] && shell->input[tmp] == ' ')
		tmp++;
	k = 0;
	while (shell->input[tmp] && shell->input[tmp] != ' ')
	{
		if (shell->input[tmp] == '>' || shell->input[tmp] == '<') // TODO: implementare errore
			break;
		limiter[k] = shell->input[tmp];
		tmp++;
		k++;
	}
	limiter[k] = '\0';
	if (create_heredoc(limiter, line, n_doc()) == 1)
		return ;
	line = ft_strjoin("./.tmp/heredoc", ft_itoa(*n_doc() - 1));
	k = 0;
	while (line[k])
	{
		shell->cmd_table[j].io[0][k] = line[k];
		k++;
	}
	shell->cmd_table[j].io[0][k] = '\0';
	*i = tmp;
}

void	redirect_append(t_shell *shell, int j, int *i)
{
	int		fd;
	int		k;
	int		tmp;

	tmp = *i + 2;
	while (shell->input[tmp] && shell->input[tmp] == ' ')
		tmp++;
	k = 0;
	while (shell->input[tmp] && shell->input[tmp] != ' ')
	{
		shell->cmd_table[j].io[1][k] = shell->input[tmp];
		tmp++;
		k++;
	}
	shell->cmd_table[j].io[1][k] = '\0';
	fd = open(shell->cmd_table[j].io[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		ft_error(1, "minishell: no such file or directory");
	else
		close(fd);
	*i = tmp;
}

void	set_redirects(t_shell *shell)
{
	int		cmd_count;
	int		i;
	int		j;
	int		k;
	int		fd;

	i = 0;
	j = 0;
	k = 0;
	cmd_count = count_cmds(shell);
	shell->cmd_table = ft_malloc(sizeof(t_cmd) * (cmd_count + 1));
	while (shell->input[i])
	{
		if (shell->input[i] == '<' && shell->input[i + 1] == '<')
			redirect_heredoc(shell, j, &i);
		else if (shell->input[i] == '>' && shell->input[i + 1] == '>')
			redirect_append(shell, j, &i);
		else if (shell->input[i] == '<' && shell->input[i + 1] != '<')   // se troviamo un redirect di input, saltiamo l'indice di uno per saltare il <
		{															// poi saltiamo gli spazi e copiamo il nome del file in cmd_table[j].io[0]																
			i++;												// poi apriamo il file in sola lettura e controlliamo se esiste
			while (shell->input[i] && shell->input[i] == ' ')
				i++;
			while (shell->input[i] && shell->input[i] != ' ')
			{
				shell->cmd_table[j].io[0][k] = shell->input[i];
				i++;
				k++;
			}
			shell->cmd_table[j].io[0][k] = '\0';
			fd = open(shell->cmd_table[j].io[0], O_RDONLY);
			if (fd < 0)
				ft_error(1, "minishell: no such file or directory");
			else
				close(fd);
			k = 0;
		}
		else if (shell->input[i] == '>' && shell->input[i + 1] != '>') // se troviamo un redirect di output, saltiamo l'indice di uno per saltare il >
		{												// poi saltiamo gli spazi e copiamo il nome del file in cmd_table[j].io[1]
			i++;										// poi apriamo il file in scrittura e controlliamo se esiste
			while (shell->input[i] && shell->input[i] == ' ')
				i++;
			while (shell->input[i] && shell->input[i] != ' ')
			{
				shell->cmd_table[j].io[1][k] = shell->input[i];
				i++;
				k++;
			}
			shell->cmd_table[j].io[1][k] = '\0';
			fd = open(shell->cmd_table[j].io[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0)
				ft_error(1, "minishell: no such file or directory");
			else
				close(fd);
			k = 0;
		}
		if (shell->input[i] && shell->input[i] == '|') // se troviamo un pipe, incrementiamo j e passiamo al prossimo comando
			j++;
		i++;
	}
}

void	ft_parser(t_shell *shell)
{
	set_redirects(shell);
	make_cmd_table(shell);
	// printf("cmd_table[0].io[0]: %s\n", shell->cmd_table[0].io[0]);
	// printf("cmd_table[0].io[1]: %s\n", shell->cmd_table[0].io[1]);
	// printf("cmd_table[1].io[1]: %s\n", shell->cmd_table[1].io[1]);
	// printf("cmd_table[1].io[0]: %s\n", shell->cmd_table[1].io[0]);
}