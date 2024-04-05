/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:45:04 by gsapio            #+#    #+#             */
/*   Updated: 2024/04/05 13:20:48 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	clear_garbage()
{
	t_list	*node;
	t_list	*tmp;

	node = *garbage_collector();
	while (node)
	{
		tmp = node->next;
		free(node->content);
		free(node);
		node = tmp;
	}
	*garbage_collector() = NULL;
	rl_clear_history();
}
