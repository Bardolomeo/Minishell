/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:42 by mtani             #+#    #+#             */
/*   Updated: 2024/04/11 15:33:45 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *shell)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	if (shell->args[1] && !ft_strncmp(shell->args[1], "-n", 2))
	{
		n_flag = 1;
		i++;
	}
	while (shell->args[i])
	{
		ft_putstr_fd(shell->args[i], 1);
		if (shell->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
	g_exit_status = 0;
}
