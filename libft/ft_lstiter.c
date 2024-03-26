/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:05:12 by mtani             #+#    #+#             */
/*   Updated: 2023/10/18 13:03:51 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	tmp = lst;
	while (tmp != NULL)
	{
		f(tmp->content);
		tmp = tmp->next;
	}
}

/*void custom_print(void *content) {
    printf("Result: %s\n", (char *)content);
}

int main() 
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
	ft_lstiter(node1, &custom_print);
    free(node1);
    free(node2);
    free(node3);
    return 0;
}*/
