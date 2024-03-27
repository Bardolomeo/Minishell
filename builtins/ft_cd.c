/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:21:47 by mtani             #+#    #+#             */
/*   Updated: 2024/03/27 18:26:01 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_shell *shell)
{
	if (shell->args[1] == NULL)
	{
		if (chdir(ft_getenv("HOME")) != 0)
			perror(RED "minishell$ " WHITE);
	}
	else
	{
		if (chdir(shell->args[1]) != 0)
			perror(RED "minishell$ " WHITE);
	}
}