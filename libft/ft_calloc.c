/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <mtani@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:24:10 by mtani             #+#    #+#             */
/*   Updated: 2024/03/27 16:06:01 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <string.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include "ft_bzero.c"
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*tmp;
	long long	result;

	if (nmemb == 0 || size == 0)
		return (ft_malloc(0));
	result = (long long)nmemb * (long long)size;
	if (result > 4294967295)
		return (NULL);
	tmp = (void *)ft_malloc(nmemb * size);
	if (tmp == NULL)
		return (NULL);
	ft_bzero(tmp, size * nmemb);
	return (tmp);
}

/*int main() 
{
	int size = 8539;
 
 	void *d1 = ft_calloc(size, sizeof(int));
 	void *d2 = calloc(size, sizeof(int));
 	if (memcmp(d1, d2, size * sizeof(int)))
 		printf("TEST FAILED");
 	free(d1);
 	free(d2);
 	printf("TEST SUCCESS");	
}*/
