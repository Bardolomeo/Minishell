/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsapio <gsapio@student.42firenze.it >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:45:04 by gsapio            #+#    #+#             */
/*   Updated: 2024/03/21 17:17:19 by gsapio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void *ft_malloc(size_t size)
{
	t_garb	*node;
	void	*ptr;

	ptr = malloc(size);
	if (!(ptr))
		return (NULL);
	node = ft_lstnew(ptr);
	ft_lstadd_front(garbage_collector(), node);
	return (ptr);
}

t_garb **garbage_collector()
{
	static t_garb *garb_static = NULL;

	return (&garb_static);
}
