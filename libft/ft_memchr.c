/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtani <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:30:04 by mtani             #+#    #+#             */
/*   Updated: 2023/10/16 16:58:38 by mtani            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;
	unsigned char	tmp_c;

	tmp = (unsigned char *)s;
	tmp_c = (unsigned char)c;
	i = 0;
	if (n <= 0)
		return (NULL);
	while (i < n)
	{
		if ((unsigned char)tmp[i] == (unsigned char)tmp_c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

/*int main() 
{
	
    void *result = ft_memchr("bbabcdef", 0, 0);
	void *result2 = memchr("bbabcdef", 0, 0);
	printf("%s\n", (char *)result);
	printf("%s\n", (char *)result2);
	
	int tab[7] = {-49, 49, 1, -1, 0, -2, 2};

	printf("%s", (char *)ft_memchr(tab, -1, 7));
	printf("%s", (char *)memchr(tab, -1, 7));
}*/
