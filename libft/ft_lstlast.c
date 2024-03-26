/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:29:29 by mtani             #+#    #+#             */
/*   Updated: 2023/10/18 14:18:11 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (lst == NULL)
		return (NULL);
	tmp = lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
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
    t_list *last_node = ft_lstlast(node1);
    if (last_node != NULL) {
        printf("Last: %s\n", (char *)last_node->content);
    } else {
        printf("Empty.\n");
    }
    free(node1);
    free(node2);
    free(node3);
    return 0;
}*/
