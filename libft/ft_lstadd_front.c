/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 15:50:22 by mtani             #+#    #+#             */
/*   Updated: 2023/10/18 12:12:06 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "ft_lstnew.c"
//#include "ft_lstlast.c"
//#include <stdio.h>
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst == NULL || new == NULL)
		return ;
	new->next = lst[0];
	lst[0] = new;
}

/*int main()
{
    t_list *list = NULL;
	t_list *temp = NULL;
	char	str1[] = "Hello";
	char	str2[] = " you ";
	char	str3[] = "there";
	void	*ptr1 = str1;
	void	*ptr2 = str2;
	void	*ptr3 = str3;
    ft_lstadd_front(&list, ft_lstnew(ptr1));
    ft_lstadd_front(&list, ft_lstnew(ptr2));
    ft_lstadd_front(&list, ft_lstnew(ptr3));
    printf("Linked List: ");
	while (list)
    {
        printf("%s -> ", list->content);
        list = list->next;
    }
    printf("NULL\n");
    while (list)
    {
        temp = list;
        list = list->next;
        free(temp);
    }
    return 0;
}*/
