/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:21:47 by mtani             #+#    #+#             */
/*   Updated: 2024/03/28 20:00:03 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_shell *shell)
{
	if (shell->args[1] == NULL || ft_strncmp(shell->args[1], "~", 1) == 0)
	{
		if (chdir(ft_getenv("HOME", 0)) != 0)
			perror(RED "minishell$ " WHITE);
	}
	else if (shell->args[2] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
	}
	else
	{
		if (chdir(shell->args[1]) != 0)
			perror(RED "minishell$ " WHITE);
	}
}