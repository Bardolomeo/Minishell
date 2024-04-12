/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:08:20 by mtani             #+#    #+#             */
/*   Updated: 2024/04/12 17:14:42 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	*i += 2;
	
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
		{
			redirect_heredoc(shell, j, &i);
		}
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
	printf("cmd_table[0].io[0]: %s\n", shell->cmd_table[0].io[0]);
	printf("cmd_table[0].io[1]: %s\n", shell->cmd_table[0].io[1]);
	printf("cmd_table[1].io[1]: %s\n", shell->cmd_table[1].io[1]);
	printf("cmd_table[1].io[0]: %s\n", shell->cmd_table[1].io[0]);
}