/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 10:25:52 by mtani             #+#    #+#             */
/*   Updated: 2024/03/27 18:13:49 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell)
{
	int		i;

	i = 0;
	while ((*shell->my_env)[i])
	{
		ft_putendl_fd((*shell->my_env)[i], 1);
		i++;
	}
}