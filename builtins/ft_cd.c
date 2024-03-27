/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:21:47 by mtani             #+#    #+#             */
/*   Updated: 2024/03/27 17:34:18 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_shell *shell)
{
	if (shell->args[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
			perror(RED "minishell$ " WHITE);
	}
	else
	{
		if (chdir(shell->args[1]) != 0)
			perror(RED "minishell$ " WHITE);
	}
}