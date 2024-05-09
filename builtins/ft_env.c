/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:52 by mtani             #+#    #+#             */
/*   Updated: 2024/05/09 16:02:28 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell, int index)
{
	int	i;

	i = 0;
	if (shell->cmd_table[index].cmd.cmd_wargs[1] != NULL)
	{
		ft_putstr_fd("minishell: env: too many arguments\n", 2);
		return ;
	}
	while ((*shell->my_env)[i])
	{
		ft_putendl_fd((*shell->my_env)[i], 1);
		i++;
	}
}
