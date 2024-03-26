/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 16:41:52 by mtani             #+#    #+#             */
/*   Updated: 2023/10/18 13:07:39 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (lst == NULL)
		return ;
	del(lst->content);
	free(lst);
	lst = NULL;
}

/*void delete_content(void *content) {
    free(content);
}

int main() {
    t_list *node1 = (t_list *)malloc(sizeof(t_list));
    t_list *node2 = (t_list *)malloc(sizeof(t_list));
    t_list *node3 = (t_list *)malloc(sizeof(t_list));
    node1->content = strdup("Hello");
    node1->next = node2;
    node2->content = strdup("you");
    node2->next = node3;
    node3->content = strdup("there");
    node3->next = NULL;
    t_list *current = node1;
    while (current != NULL)
	{
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
	ft_lstdelone(node1, &delete_content);
	current = node2;
    while (current != NULL)
	{
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
    free(node2);
    free(node3);
    return 0;
}*/
