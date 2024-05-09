/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_single.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:32:13 by gsapio            #+#    #+#             */
/*   Updated: 2024/05/09 16:50:37 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	**garbage_collector(void)
{
	static t_list	*garb_static = NULL;

	return (&garb_static);
}

char	***ft_myenv(void)
{
	static char	**env = NULL;

	return (&env);
}

int	*n_doc(void)
{
	static int	n_doc = 0;

	return (&n_doc);
}

int	*fd_stand_in(void)
{
	static int	fd_stand_in = 0;

	return (&fd_stand_in);
}

int	*fd_stand_out(void)
{
	static int	fd_stand_out = 0;

	return (&fd_stand_out);
}
