/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:45:04 by gsapio            #+#    #+#             */
/*   Updated: 2024/03/26 12:01:06 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *ft_malloc(size_t size)
{
	t_list	*node;
	void	*ptr;

	ptr = malloc(size);
	if (!(ptr))
		return (NULL);
	node = ft_lstnew(ptr);
	ft_lstadd_front(garbage_collector(), node);
	return (ptr);
}

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

}

t_list **garbage_collector()
{
	static t_list *garb_static = NULL;

	return (&garb_static);
}
