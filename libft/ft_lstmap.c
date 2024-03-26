/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:11:40 by mtani             #+#    #+#             */
/*   Updated: 2023/10/18 17:15:15 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*node;
	t_list	*tmp;
	void	*result;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	tmp = lst;
	node = NULL;
	list = NULL;
	while (tmp != NULL)
	{
		result = f(tmp->content);
		node = ft_lstnew(result);
		if (node == NULL)
		{
			del(result);
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, node);
		tmp = tmp->next;
	}
	return (list);
}
