/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:07:05 by mtani             #+#    #+#             */
/*   Updated: 2023/10/18 14:42:06 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

/*int main() 
{
    t_list *node1 = (t_list *)malloc(sizeof(t_list));
    t_list *node2 = (t_list *)malloc(sizeof(t_list));
    t_list *node3 = (t_list *)malloc(sizeof(t_list));

    node1->content = "Hello";
    node1->next = node2;
    node2->content = "you";
    node2->next = node3;
    node3->content = "there";
    node3->next = NULL;
    int size = ft_lstsize(node1);
	printf("Size: %d\n", size);
	free(node1);
    free(node2);
    free(node3);
    return (0);
}*/
