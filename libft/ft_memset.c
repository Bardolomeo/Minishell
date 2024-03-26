/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 12:52:53 by mtani             #+#    #+#             */
/*   Updated: 2023/10/18 14:52:57 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdlib.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		*(tmp + i) = (unsigned char)c;
		i++;
	}
	return (s);
}

/*int main() {
    char arr[10];

    ft_memset(arr, '5', sizeof(arr));
	for (size_t i = 0; i < sizeof(arr); i++) 
	{
        printf("%c ", arr[i]);
    }
    printf("\n");
}*/
