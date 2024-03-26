/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:39:15 by mtani             #+#    #+#             */
/*   Updated: 2023/10/18 12:27:01 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_lstadd_back.c"
//#include "ft_lstnew.c"
//#include "ft_lstlast.c"
//#include <stdio.h>
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current_node;
	t_list	*next_node;

	if (!lst || !*lst || !del)
		return ;
	current_node = *lst;
	next_node = *lst;
	while (current_node != NULL)
	{
		next_node = next_node->next;
		del(current_node->content);
		free(current_node);
		current_node = next_node;
	}
	*lst = NULL;
}

/*void del_content(void *content)
{
    free(content);
}

int main()
{
    t_list *list = NULL;
	t_list *temp = NULL;
	void (*function)(void *) = &del_content;
	char	str1[] = "Hello";
	char	str2[] = " you ";
	char	str3[] = "there";
	void	*ptr1 = str1;
	void	*ptr2 = str2;
	void	*ptr3 = str3;
    ft_lstadd_back(&list, ft_lstnew(ptr1));
    ft_lstadd_back(&list, ft_lstnew(ptr2));
    ft_lstadd_back(&list, ft_lstnew(ptr3));
    printf("Linked List: ");
	while (list)
    {
        printf("%s -> ", list->content);
        list = list->next;
    }
    printf("NULL\n");
   	ft_lstclear(&list, function);
	if (list == NULL)
		printf("Empty list");
	else
	{
		while (list)
		{
			printf("%s -> ", list->content);
			list = list->next;
		}
	}
    return 0;
}*/
