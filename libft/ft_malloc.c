/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mint <mint@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:58:22 by mtani             #+#    #+#             */
/*   Updated: 2024/03/27 15:39:30 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
