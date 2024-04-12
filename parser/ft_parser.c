/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:08:20 by mtani             #+#    #+#             */
/*   Updated: 2024/04/12 13:15:39 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (count);
}

void	ft_parser(t_shell *shell)
{
	make_cmd_table(shell);
}